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
	void on_checkBox_hexDisplay_clicked(bool checked);
	void on_btnRevClear_clicked();
	void on_btnRevSave_clicked();
	void time_refresh();

private:
    Ui::SerialPortAssistantClass* ui;
    QSerialPort* serialPort;
	int writeCntTotal;
	int readCntTotal;
    QString sendBackup;
	QString myTime;
	bool serialPortStatus; //串口状态
	QTimer* sendTimer;   //QT自带的定时器类：定时发送数据

	void getSystemTime();
};

