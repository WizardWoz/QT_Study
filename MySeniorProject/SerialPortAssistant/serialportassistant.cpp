#include "serialportassistant.h"
#include "ui_serialportassistant.h"
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

SerialPortAssistant::SerialPortAssistant(QWidget *parent)
	: QWidget(parent), ui(new Ui::SerialPortAssistantClass)
{
    ui->setupUi(this);
	this->setLayout(ui->gridLayout_Global);
	writeCntTotal = 0;
	readCntTotal = 0;
	serialPort = new QSerialPort(this);

	connect(serialPort, &QSerialPort::readyRead, this, &SerialPortAssistant::on_serialData_readyToRead);

	ui->comboBox_baudRate->setCurrentIndex(6);
	ui->comboBox_dataBit->setCurrentIndex(3);


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
		ui->label_sendCnt->setNum(writeCntTotal);
		if (!strcmp(text.toStdString().c_str(), sendBackup.toStdString().c_str()))
		{
			ui->textEdit_Record->append(text);
			sendBackup = text;
		}
	}

}

void SerialPortAssistant::on_serialData_readyToRead()
{
	QByteArray data = serialPort->readAll();
	//根据发送端使用的编码解码
	QString revMessage = QString::fromUtf8(data);
	if (revMessage!=nullptr)
	{
		qDebug() << "Received Message:" << revMessage;
		ui->textEdit_Rev->append(revMessage);
		readCntTotal += revMessage.length();
		ui->label_revCnt->setNum(readCntTotal);
	}
	
}

void SerialPortAssistant::on_btnCloseOrOpenSerial_clicked()
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
	if (ui->comboBox_flowCon->currentText()=="None")
	{
		serialPort->setFlowControl(QSerialPort::NoFlowControl);
	}
	//7.打开串口
	if (serialPort->open(QIODevice::ReadWrite))
	{
		qDebug() << "Serial Open Success!";
	}
	
}