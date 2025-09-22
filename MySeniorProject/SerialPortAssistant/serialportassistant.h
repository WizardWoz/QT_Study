#pragma once

#include <QtWidgets/QWidget>
#include "ui_serialportassistant.h"

class SerialPortAssistant : public QWidget
{
    Q_OBJECT

public:
    SerialPortAssistant(QWidget *parent = nullptr);
    ~SerialPortAssistant();

private:
    Ui::SerialPortAssistantClass* ui;
};

