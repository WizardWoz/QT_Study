#include "serialportassistant.h"
#include "ui_serialportassistant.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>

SerialPortAssistant::SerialPortAssistant(QWidget* parent)
	: QWidget(parent), ui(new Ui::SerialPortAssistantClass)
{
	ui->setupUi(this);
	this->setLayout(ui->gridLayout_Global);
	writeCntTotal = 0;
	readCntTotal = 0;
	serialPortStatus = false;
	ui->btnSendContent->setEnabled(false);
	ui->checkBox_sendInTime->setEnabled(false);
	serialPort = new QSerialPort(this);	//为整个窗口添加串口对象
	sendTimer = new QTimer(this);	//为整个窗口添加定时器对象

	connect(serialPort, &QSerialPort::readyRead, this, &SerialPortAssistant::on_serialData_readyToRead);
	connect(sendTimer, &QTimer::timeout, [=]() {
		on_btnSendContent_clicked();
	});

	ui->comboBox_baudRate->setCurrentIndex(6);
	ui->comboBox_dataBit->setCurrentIndex(3);
	ui->btnSendContent->setEnabled(false);

	QList<QSerialPortInfo> serialList = QSerialPortInfo::availablePorts();
	//C++迭代器遍历，将可用的串口号添加到下拉框中
	for (QSerialPortInfo serialInfo : serialList)
	{
		qDebug() << serialInfo.portName();
		ui->comboBox_serialNum->addItem(serialInfo.portName());
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
	writeCnt = serialPort->write(sendData);

	if (writeCnt == -1)
	{
		qDebug() << "发送失败!";
		ui->label_sendStatus->setText("Send Error!");
	}
	else
	{
		writeCntTotal += writeCnt;
		qDebug() << "发送成功!" << text;
		ui->textEdit_Record->append(text);
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
	  为什么选择COM1串口只能看到发送数据，而看不到接收.数据？
	  是因为COM1串口通常是计算机的内置串口，很多计算机并没有实际连接到任何外部设备，所以即使你发送数据，也没有设备来回应或发送数据回来
	  况且COM1串口TX与RX引脚还未短接，所以无法实现数据的回环；而COM4串口插入了USB转TTL模块，模块的TX与RX引脚短接，所以可以实现数据的回环
	*/
}

void SerialPortAssistant::on_serialData_readyToRead()
{
	QByteArray data = serialPort->readAll();
	//根据发送端使用的编码解码
	QString revMessage = QString::fromUtf8(data);
	if (revMessage != nullptr)
	{
		qDebug() << "Received Message:" << revMessage;
		ui->textEdit_Rev->append(revMessage);
		readCntTotal += revMessage.length();
		ui->label_revCnt->setNum(readCntTotal);
		ui->label_revCnt->setText("Received: " + QString::number(readCntTotal));
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
		sendTimer->stop();
	}

}