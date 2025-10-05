#pragma once

#include <QtWidgets/QWidget>
#include <QSerialPort>
#include <QTimer>
#include <QPushButton>
#include "customthread.h"
#include "ui_serialportassistant.h"

class SerialPortAssistant : public QWidget
{
	//让整个类具备信号与槽的功能
    Q_OBJECT

public:
    SerialPortAssistant(QWidget *parent = nullptr);
    ~SerialPortAssistant();

private slots:
    void on_btnCloseOrOpenSerial_clicked();
	void on_btnSendContent_clicked();
    void on_serialData_readyToRead();
	void on_btnRevClear_clicked();
	void on_btnRevSave_clicked();
	void on_command_button_clicked();
	void on_btnHidePanel_clicked(bool checked);
	void on_btnHideHistory_clicked(bool checked);
	void on_checkBox_sendInTime_clicked(bool checked);
	void on_checkBox_hexDisplay_clicked(bool checked);
	void on_checkBox_send_clicked(bool checked);
	void time_refresh();
	void refreshSerialName();
	void buttons_handler();

private:
    Ui::SerialPortAssistantClass* ui;
    QSerialPort* serialPort;
	int writeCntTotal;
	int readCntTotal;
	int buttonIdx;
    QString sendBackup;
	QString myTime;
	bool serialPortStatus; //串口状态
	QTimer* sendTimer;   //QT自带的定时器类：定时发送数据
	QTimer* buttonsConTimer; //按钮连续发送定时器
	QList<QPushButton*> buttons;
	CustomThread* mythread;

	void getSystemTime();
};

