#include "mybutton.h"

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{
	pic.load(":/Icons/save.png");	//默认加载初始图片
	setFixedSize(pic.size());		//设置矩形区域大小与图片相同
	update();	//触发QT框架回调paintEvent事件
}

MyButton::~MyButton()
{
	
}

void MyButton::mousePressEvent(QMouseEvent* event)
{
	pic.load(":/Icons/save.png");
	update();
	emit clicked();	//发射clicked信号
}

void MyButton::leaveEvent(QEvent* event)
{
	pic.load(":/Icons/保存.png");
	update();
}

void MyButton::enterEvent(QEnterEvent* event)
{
	pic.load(":/Icons/save.png");
	update();
}

void MyButton::paintEvent(QPaintEvent* event)
{
	//QPainter绘画师对象
	QPainter painter(this);
	//在rect()函数实现的矩形区域上绘制pic图像
	painter.drawPixmap(rect(), pic);
}

//void MyButton::clicked()
//{
//
//}

