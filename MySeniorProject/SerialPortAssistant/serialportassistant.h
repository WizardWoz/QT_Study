#pragma once

#include <QtWidgets/QWidget>
#include <QSerialPort>
#include "ui_serialportassistant.h"

class SerialPortAssistant : public QWidget
{
    Q_OBJECT

public:
    SerialPortAssistant(QWidget *parent = nullptr);
    ~SerialPortAssistant();

private slots:
    void on_btnCloseOrOpenSerial_clicked();

private:
    Ui::SerialPortAssistantClass* ui;
    QSerialPort* serialPort;
};

