#pragma once

#include <QtWidgets/QWidget>
#include <QSerialPort>
#include <QTimer>
#include "ui_serialportassistant.h"

class SerialPortAssistant : public QWidget
{
    Q_OBJECT

public:
    SerialPortAssistant(QWidget *parent = nullptr);
    ~SerialPortAssistant();

private slots:
    void on_btnCloseOrOpenSerial_clicked();
	void on_btnSendContent_clicked();
    void on_serialData_readyToRead();
	void on_checkBox_sendInTime_clicked(bool checked);

private:
    Ui::SerialPortAssistantClass* ui;
    QSerialPort* serialPort;
	int writeCntTotal;
	int readCntTotal;
    QString sendBackup;
	bool serialPortStatus; //串口状态
	QTimer* sendTimer;   //QT自带的定时器类：定时发送数据
};

