#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{
	pic.load(":/Icons/save.png");	//Ĭ�ϼ��س�ʼͼƬ
	setFixedSize(pic.size());		//���þ��������С��ͼƬ��ͬ
	update();	//����QT��ܻص�paintEvent�¼�
}

MyButton::~MyButton()
{
	
}

void MyButton::mousePressEvent(QMouseEvent* event)
{
	pic.load(":/Icons/save.png");
	update();
	emit clicked();	//����clicked�ź�
}

void MyButton::leaveEvent(QEvent* event)
{
	pic.load(":/Icons/����.png");
	update();
}

void MyButton::enterEvent(QEnterEvent* event)
{
	pic.load(":/Icons/save.png");
	update();
}

void MyButton::paintEvent(QPaintEvent* event)
{
	//QPainter�滭ʦ����
	QPainter painter(this);
	//��rect()����ʵ�ֵľ��������ϻ���picͼ��
	painter.drawPixmap(rect(), pic);
}

//void MyButton::clicked()
//{
//
//}

