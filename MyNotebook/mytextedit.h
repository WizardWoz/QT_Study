#pragma once

#include <QTextEdit>

class MyTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	MyTextEdit(QWidget *parent);
	~MyTextEdit();

protected:
	void wheelEvent(QWheelEvent*) override;
	void keyPressEvent(QKeyEvent*) override;
	void keyReleaseEvent(QKeyEvent*) override;

private:
	bool ctrlKeyPressed = false;
};

