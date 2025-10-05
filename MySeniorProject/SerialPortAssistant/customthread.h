#pragma once

#include <QWidget>
#include <QThread>

class CustomThread : public QThread
{
	Q_OBJECT

protected:
	void run() override;

public:
	CustomThread(QWidget *parent);
	~CustomThread();

signals:
	void threadTimeout();
};

