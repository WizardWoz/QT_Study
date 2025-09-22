#include "serialportassistant.h"

SerialPortAssistant::SerialPortAssistant(QWidget *parent)
	: QWidget(parent), ui(new Ui::SerialPortAssistantClass)
{
    ui->setupUi(this);
	this->setLayout(ui->gridLayout_Global);
}

SerialPortAssistant::~SerialPortAssistant()
{
    delete ui;
}