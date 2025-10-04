#include "serialportassistant.h"
#include "ui_serialportassistant.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
#include "mycombobox.h"

SerialPortAssistant::SerialPortAssistant(QWidget* parent)
	: QWidget(parent), ui(new Ui::SerialPortAssistantClass)
{
	ui->setupUi(this);
	this->setLayout(ui->gridLayout_Global);
	//控制参数初始化
	writeCntTotal = 0;
	readCntTotal = 0;
	serialPortStatus = false;
	//控件状态初始化
	ui->btnSendContent->setEnabled(false);
	ui->checkBox_sendInTime->setEnabled(false);
	ui->checkBox_sendNewLine->setEnabled(false);
	ui->checkBox_hexSend->setEnabled(false);
	ui->checkBox_formatInput->setEnabled(false);

	serialPort = new QSerialPort(this);	//为整个窗口添加串口对象

	QTimer* getSystemTimeTimer = new QTimer(this);
	connect(getSystemTimeTimer, SIGNAL(timeout()), this, SLOT(time_refresh()));
	time_refresh();
	getSystemTimeTimer->start(1000);
	sendTimer = new QTimer(this);	//为整个窗口添加定时器对象

	connect(serialPort, &QSerialPort::readyRead, this, &SerialPortAssistant::on_serialData_readyToRead);
	connect(sendTimer, &QTimer::timeout, [=]() {
		on_btnSendContent_clicked();
	});

	//连接自定义的下拉框类
	connect(ui->comboBox_serialNum, &MyComboBox::refresh, this, &SerialPortAssistant::refreshSerialName);

	ui->comboBox_baudRate->setCurrentIndex(6);
	ui->comboBox_dataBit->setCurrentIndex(3);
	ui->btnSendContent->setEnabled(false);

	refreshSerialName();
	
	ui->label_sendStatus->setText(ui->comboBox_serialNum->itemText(0) + " Not Open");

	QList<QPushButton*> buttons;
	for (int i = 1; i <= 9; i++)
	{
		QString btnName = QString("pushButton_%1").arg(i);
		//findChild只能找到直接子控件，不能找到孙子控件；无需使用ui->centralwidget->
		QPushButton* btn = findChild<QPushButton*>(btnName);
		if (btn)
		{
			btn->setProperty("buttonId", i); // 设置自定义属性
			buttons.append(btn);
			connect(btn, SIGNAL(clicked()), this, SLOT(on_command_button_clicked()));
		}
	}
}

SerialPortAssistant::~SerialPortAssistant()
{
	delete ui;
	delete serialPort;
}

void SerialPortAssistant::on_btnSendContent_clicked()
{
	int writeCnt = 0;
	//QT6版本开始的发送中文字符串方法
	QString text = ui->lineEdit_sendContent->text();
	QByteArray sendData = text.toUtf8();
	//const char* sendData = ui->lineEdit_sendContent->text().toStdString().c_str();
	//如果是发送HEX 16进制数据
	if (ui->checkBox_hexSend->isChecked())
	{
		QString temp = ui->lineEdit_sendContent->text();
		//判断是否为偶数位
		QByteArray tempArray = temp.toUtf8();
		if (tempArray.size() % 2 != 0)
		{
			ui->label_sendStatus->setText("Error Input!");
			return;
		}
		//判断是否符合16进制的格式
		for (char c : tempArray)
		{
			if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))
			{
				ui->label_sendStatus->setText("Error Input!");
				return;
			}
		}
		if (ui->checkBox_sendNewLine->isChecked())
		{
			tempArray.append("\r\n");
		}
		//转换为16进制格式。用户输入1变成1；拒绝变成字符1
		QByteArray arraySend = QByteArray::fromHex(tempArray);
		writeCnt = serialPort->write(arraySend);
	}
	//如果不是发送HEX 16进制数据
	else
	{
		//判断是否发送新行
		if (ui->checkBox_sendNewLine->isChecked())
		{
			QByteArray arraySendData(sendData, strlen(sendData));
			arraySendData.append("\r\n");
			writeCnt = serialPort->write(arraySendData);
		}
		else
		{
			writeCnt = serialPort->write(sendData);
		}
	}

	if (writeCnt == -1)
	{
		qDebug() << "发送失败!";
		ui->label_sendStatus->setText("Send Error!");
	}
	else
	{
		writeCntTotal += writeCnt;
		qDebug() << "发送成功！" << text << "；发送字节数：" << writeCnt;
		//ui->textEdit_Record->append(text);
		ui->label_sendStatus->setText("Send OK!");
		//ui->label_sendCnt->setNum(writeCntTotal);
		ui->label_sendCnt->setText("Sent: " + QString::number(writeCntTotal));
		if (strcmp(text.toStdString().c_str(), sendBackup.toStdString().c_str())!=0)
		{	
			ui->textEdit_Record->append(text);
			sendBackup = text;
		}
	}
	/*
	  为什么选择COM1串口只能看到发送数据，而看不到接收数据？
	  是因为COM1串口通常是计算机的内置串口，很多计算机并没有实际连接到任何外部设备，所以即使你发送数据，也没有设备来回应或发送数据回来
	  况且COM1串口TX与RX引脚还未短接，所以无法实现数据的回环；而COM4串口插入了USB转TTL模块，模块的TX与RX引脚短接，所以可以实现数据的回环
	*/
}

void SerialPortAssistant::on_serialData_readyToRead()
{
	QByteArray data = serialPort->readAll();
	//根据发送端使用的编码解码
	QString revMessage = QString::fromUtf8(data);
	qDebug() << "revCnt：" << data.size() << "Received Message:" << revMessage;
	if (revMessage != nullptr)
	{
		if (ui->checkBox_autoChangeLine->isChecked())
		{
			revMessage.append("\r\n");
		}
		//如果接收区是HEX 16进制显示模式
		if (ui->checkBox_hexDisplay->isChecked())
		{
			QByteArray tempHexString = revMessage.toUtf8().toHex().toUpper();
			//原来控件上旧的内容
			QString tempStringHex = ui->textEdit_Rev->toPlainText();//勾选了读出来就是HEX
			tempHexString = tempStringHex.toUtf8() + tempHexString;	//把读出的旧的HEX和新收到的数据转成HEX再拼接
			//重新显示在控件上
			ui->textEdit_Rev->setText(QString::fromUtf8(tempHexString));
		}
		//如果接收区不是HEX 16进制显示模式
		else
		{
			//如果接收时间的复选框被勾选，则在接收区的接受字符串之前添加时间
			if (ui->checkBox_revTime->checkState() == Qt::Checked)
			{
				QString new_revContent = '[' + myTime + ']' + revMessage;
				ui->textEdit_Rev->insertPlainText(new_revContent);
			}
			else if (ui->checkBox_revTime->checkState() == Qt::Unchecked)
			{
				ui->textEdit_Rev->insertPlainText(revMessage);
			}
		}
		readCntTotal += data.size();
		ui->label_revCnt->setText("Received: " + QString::number(readCntTotal));
	}

}

void SerialPortAssistant::on_btnHidePanel_clicked(bool checked)
{
	if (checked)
	{
		qDebug() << checked << "值";
		ui->btnHidePanel->setText("显示面板");
		//ui->groupBox_Texts->setVisible(false);
		ui->groupBox_Texts->hide();
	}
	else
	{
		qDebug() << checked << "值";
		ui->btnHidePanel->setText("隐藏面板");
		//ui->groupBox_Texts->setVisible(true);
		ui->groupBox_Texts->show();
	}
}

void SerialPortAssistant::on_btnHideHistory_clicked(bool checked)
{
	if (checked)
	{
		qDebug() << checked << "值";
		ui->btnHideHistory->setText("显示历史");
		//ui->groupBox_Record->setVisible(false);
		ui->groupBox_Record->hide();
	}
	else
	{
		qDebug() << checked << "值";
		ui->btnHideHistory->setText("隐藏历史");
		//ui->groupBox_Record->setVisible(true);
		ui->groupBox_Record->show();
	}
}


void SerialPortAssistant::on_checkBox_sendInTime_clicked(bool checked)
{
	qDebug() << "Check Box Send In Time." << checked;
	if(checked)
	{
		//on_btnSendContent_clicked();
		ui->lineEdit_timeEpoch->setEnabled(false);
		ui->lineEdit_sendContent->setEnabled(false);
		sendTimer->start(ui->lineEdit_timeEpoch->text().toInt()); //1000ms
	}
	else
	{
		sendTimer->stop();
		ui->lineEdit_timeEpoch->setEnabled(true);
		ui->lineEdit_sendContent->setEnabled(true);
	}
}

void SerialPortAssistant::on_checkBox_hexDisplay_clicked(bool checked)
{
	qDebug() << "Check Box Hex Display." << checked;
	if (checked)
	{
		//1.读取textEdit_Rev中的内容
		QString temp = ui->textEdit_Rev->toPlainText();
		//2.将内容转换为Hex十六进制
		QByteArray qtemp = temp.toUtf8();
		qtemp = qtemp.toHex();
		//3.将转换后的内容重新显示在textEdit_Rev中
		QString lastShow;
		temp = QString::fromUtf8(qtemp);
		for (int i = 0; i < temp.size(); i+=2)
		{
			lastShow += temp.mid(i, 2) + " ";
		}
		ui->textEdit_Rev->setText(lastShow.toUpper());
	}
	else
	{
		//1.读取textEdit_Rev中的内容
		QString tempHexString = ui->textEdit_Rev->toPlainText();
		//2.将内容转换为普通字符串
		QByteArray tempHexQByteArray = tempHexString.toUtf8();
		QByteArray tempQByteString = QByteArray::fromHex(tempHexQByteArray);
		//3.将转换后的内容重新显示在textEdit_Rev中
		ui->textEdit_Rev->setText(QString::fromUtf8(tempQByteString));
	}
}

void SerialPortAssistant::on_btnRevClear_clicked()
{
	ui->textEdit_Rev->setText("");
}

void SerialPortAssistant::on_btnRevSave_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("保存接收数据"), "接收数据.txt", tr("文本文件(*.txt);;所有文件(*.*)"));
	if (fileName!=nullptr)
	{
		QFile file(fileName);
		if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
		{
			qDebug() << "文件打开失败!";
			return;
		}
		QTextStream out(&file);
		out << ui->textEdit_Rev->toPlainText();
		file.close();
	}
}

void SerialPortAssistant::on_command_button_clicked()
{
	QPushButton* btn = qobject_cast<QPushButton*>(sender());
	if (btn)
	{
		int num = btn->property("buttonId").toInt();
		qDebug() << "Button " << num << " clicked!";
		QString lineEditName = QString("lineEdit_%1").arg(num);
		QLineEdit* lineEdit = findChild<QLineEdit*>(lineEditName);
		if (lineEdit)
		{
			ui->lineEdit_sendContent->setText(lineEdit->text());
		}

		QString checkBoxName = QString("checkBox_%1").arg(num);
		QCheckBox* checkBox = findChild<QCheckBox*>(checkBoxName);
		if (checkBox)
		{
			ui->checkBox_hexSend->setChecked(checkBox->isChecked());
		}
		on_btnSendContent_clicked();
	}
}

void SerialPortAssistant::time_refresh()
{
	getSystemTime();
	ui->label_currentTime->setText(myTime);
}

void SerialPortAssistant::refreshSerialName()
{
	//每次刷新前，先清空下拉框中的内容
	ui->comboBox_serialNum->clear();
	//检测系统可用串口，并更新到comboBox_serialNum下拉框中供用户选择
	QList<QSerialPortInfo> serialList = QSerialPortInfo::availablePorts();
	//C++迭代器遍历，将可用的串口号添加到下拉框中
	for (QSerialPortInfo serialInfo : serialList)
	{
		qDebug() << serialInfo.portName();
		ui->comboBox_serialNum->addItem(serialInfo.portName());
	}
	ui->label_sendStatus->setText("COM Refreshed!");
}

void SerialPortAssistant::getSystemTime()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	//QDate date = currentTime.date();
	//int year = date.year();
	//int month = date.month();
	//int day = date.day();
	//QTime time = currentTime.time();
	//int hour = time.hour();
	//int minute = time.minute();
	//int second = time.second();
	//myTime = QString("%1-%2-%3 %4:%5:%6").arg(year).arg(month).arg(day).arg(hour).arg(minute).arg(second);
	myTime = currentTime.toString("yyyy-MM-dd hh:mm:ss");
}

void SerialPortAssistant::on_btnCloseOrOpenSerial_clicked()
{
	//串口未被打开
	if (serialPortStatus == false)
	{
		//1.选择端口号
		serialPort->setPortName(ui->comboBox_serialNum->currentText());
		//2.配置波特率
		serialPort->setBaudRate(ui->comboBox_baudRate->currentText().toInt());
		//3.配置数据位
		serialPort->setDataBits(QSerialPort::DataBits(ui->comboBox_dataBit->currentText().toInt()));
		//4.配置校验位
		/*enum Parity {
			NoParity = 0,
			EvenParity = 2,
			OddParity = 3,
			SpaceParity = 4,
			MarkParity = 5
		};*/
		switch (ui->comboBox_checkBit->currentIndex())
		{
		case 0:
			serialPort->setParity(QSerialPort::NoParity);
			break;
		case 1:
			serialPort->setParity(QSerialPort::EvenParity);
			break;
		case 2:
			serialPort->setParity(QSerialPort::MarkParity);
			break;
		case 3:
			serialPort->setParity(QSerialPort::OddParity);
			break;
		case 4:
			serialPort->setParity(QSerialPort::SpaceParity);
			break;
		default:
			break;
		}
		//5.配置停止位
		serialPort->setStopBits(QSerialPort::StopBits(ui->comboBox_stopBit->currentText().toInt()));
		//6.流控
		if (ui->comboBox_flowCon->currentText() == "None")
		{
			serialPort->setFlowControl(QSerialPort::NoFlowControl);
		}
		//7.打开串口
		if (serialPort->open(QIODevice::ReadWrite))
		{
			qDebug() << "Serial Open Success!";
			ui->comboBox_dataBit->setEnabled(false);
			ui->comboBox_flowCon->setEnabled(false);
			ui->comboBox_checkBit->setEnabled(false);
			ui->comboBox_stopBit->setEnabled(false);
			ui->comboBox_baudRate->setEnabled(false);
			ui->comboBox_serialNum->setEnabled(false);
			ui->btnCloseOrOpenSerial->setText("关闭串口");
			ui->btnSendContent->setEnabled(true);
			ui->checkBox_sendInTime->setEnabled(true);
			ui->checkBox_sendNewLine->setEnabled(true);
			ui->checkBox_hexSend->setEnabled(true);
			ui->checkBox_formatInput->setEnabled(true);
			ui->label_sendStatus->setText(ui->comboBox_serialNum->currentText() + " is Opened!");
			serialPortStatus = true;
		}
		else
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("打开串口错误");
			msgBox.setText("串口打开失败，请检查串口是否被占用或连接正确!");
			msgBox.exec();
		}
	}

	//串口已被打开
	else
	{
		//关闭串口后，设置各个控件的使能，恢复可配置状态
		serialPort->close();
		ui->btnCloseOrOpenSerial->setText("打开串口");
		ui->comboBox_dataBit->setEnabled(true);
		ui->comboBox_flowCon->setEnabled(true);
		ui->comboBox_checkBit->setEnabled(true);
		ui->comboBox_stopBit->setEnabled(true);
		ui->comboBox_baudRate->setEnabled(true);
		ui->comboBox_serialNum->setEnabled(true);
		serialPortStatus = false;
		ui->btnSendContent->setEnabled(false);
		ui->checkBox_sendInTime->setEnabled(false);
		ui->checkBox_sendInTime->setCheckState(Qt::Unchecked);
		ui->checkBox_sendNewLine->setEnabled(false);
		ui->checkBox_hexSend->setEnabled(false);
		ui->checkBox_formatInput->setEnabled(false);
		ui->label_sendStatus->setText(ui->comboBox_serialNum->currentText() + " is Closed!");
		sendTimer->stop();
	}

}