#include "mycombobox.h"
#include <QMouseEvent>

MyComboBox::MyComboBox(QWidget *parent)
	: QComboBox(parent)
{
	
}

MyComboBox::~MyComboBox()
{}

void MyComboBox::mousePressEvent(QMouseEvent * event)
{
	//发出一个信号
	if (event->button() == Qt::LeftButton)
	{
		emit refresh();
	}
	QComboBox::mousePressEvent(event);
}

