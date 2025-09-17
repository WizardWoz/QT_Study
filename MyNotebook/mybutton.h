#pragma once

/*
  ʹ���Զ���MyButton��ķ�����
  1.��QT Widget Designer�����һ��Widget��Ȼ��������ΪMyButton��
  2.ֱ�ӴӴ������
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
	void mousePressEvent(QMouseEvent*) override;	//��д��갴���¼�
	void leaveEvent(QEvent*) override;	//��д�����봰���¼�
	void enterEvent(QEnterEvent*) override;		//��д�������¼�
	void paintEvent(QPaintEvent*) override;		//��д��ͼ�¼�

private:
	QPixmap pic;

signals:
	void clicked();	//�Զ���clicked�ź�
};

