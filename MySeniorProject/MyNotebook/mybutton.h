#pragma once

/*
  使用自定义MyButton类的方法：
  1.在QT Widget Designer中添加一个Widget，然后将其提升为MyButton类
  2.直接从代码调用
*/

#include <QWidget>
#include <QPainter>

class MyButton : public QWidget
{
	Q_OBJECT

public:
	MyButton(QWidget *parent);
	~MyButton();
	
protected:
	void mousePressEvent(QMouseEvent*) override;	//重写鼠标按下事件
	void leaveEvent(QEvent*) override;	//重写光标进入窗口事件
	void enterEvent(QEnterEvent*) override;		//重写光标进入事件
	void paintEvent(QPaintEvent*) override;		//重写画图事件

private:
	QPixmap pic;

signals:
	void clicked();	//自定义clicked信号
};

