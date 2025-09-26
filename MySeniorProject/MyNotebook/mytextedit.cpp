#include "mytextedit.h"
#include <QDebug>
#include <QWheelEvent>

MyTextEdit::MyTextEdit(QWidget *parent)
	: QTextEdit(parent)
{
	
}

MyTextEdit::~MyTextEdit()
{
	
}

void MyTextEdit::wheelEvent(QWheelEvent* event)
{
	qDebug() << event->angleDelta();
	if (ctrlKeyPressed == 1)
	{
		if (event->angleDelta().y() > 0)
		{
			zoomIn();
		}
		else if (event->angleDelta().y() < 0)
		{
			zoomOut();
		}
		event->accept();
	}
	else
	{
		QTextEdit::wheelEvent(event);
	}
}

void MyTextEdit::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Control)
	{
		qDebug() << "Ctrl pressed.";
		ctrlKeyPressed = 1;
	}
	QTextEdit::keyPressEvent(event);
}

void MyTextEdit::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Control)
	{
		qDebug() << "Ctrl released.";
		ctrlKeyPressed = 0;
	}
	QTextEdit::keyReleaseEvent(event);
}

