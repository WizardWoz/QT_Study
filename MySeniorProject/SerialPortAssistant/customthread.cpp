#include "customthread.h"

/*
  一旦线程的 start() 方法被调用，线程就会启动并执行 run() 方法中的代码。
*/
void CustomThread::run()
{
	// 线程执行的代码
	while (true)
	{
		msleep(1000);
		emit threadTimeout();
	}
}

CustomThread::CustomThread(QWidget *parent)
	: QThread(parent)
{

}

CustomThread::~CustomThread()
{

}

