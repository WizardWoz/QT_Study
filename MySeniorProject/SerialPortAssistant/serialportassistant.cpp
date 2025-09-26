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
	serialPort = new QSerialPort(this);

	ui->comboBox_baudRate->setCurrentIndex(6);
	ui->comboBox_dataBit->setCurrentIndex(3);


	QList<QSerialPortInfo> serialList = QSerialPortInfo::availablePorts();
	//C++����������
	for (QSerialPortInfo serialInfo : serialList)
	{
		qDebug() << serialInfo.portName();
		ui->comboBox_serialNum->addItem(serialInfo.portName());
	}
}

SerialPortAssistant::~SerialPortAssistant()
{
    delete ui;
}

void SerialPortAssistant::on_btnCloseOrOpenSerial_clicked()
{
	//1.ѡ��˿ں�
	serialPort->setPortName(ui->comboBox_serialNum->currentText());
	//2.���ò�����
	serialPort->setBaudRate(ui->comboBox_baudRate->currentText().toInt());
	//3.��������λ
	serialPort->setDataBits(QSerialPort::DataBits(ui->comboBox_dataBit->currentText().toInt()));
	//4.����У��λ
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
	//5.����ֹͣλ
	serialPort->setStopBits(QSerialPort::StopBits(ui->comboBox_stopBit->currentText().toInt()));
	//6.����
	if (ui->comboBox_flowCon->currentText()=="None")
	{
		serialPort->setFlowControl(QSerialPort::NoFlowControl);
	}
	//7.�򿪴���
	if (serialPort->open(QIODevice::ReadWrite))
	{
		qDebug() << "Serial Open Success!";
	}
	
}