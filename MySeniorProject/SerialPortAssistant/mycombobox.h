#pragma once

#include <QComboBox>

class MyComboBox  : public QComboBox
{
	Q_OBJECT

public:
	MyComboBox(QWidget *parent);
	~MyComboBox();

protected:
	void mousePressEvent(QMouseEvent *event) override;

signals:
	void refresh();  // 自定义信号
};

