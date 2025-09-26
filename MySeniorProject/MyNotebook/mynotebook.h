#pragma once
#include <iostream>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QList>
#include <QGuiApplication>
#include "mybutton.h"

/*
  ui命名空间：QT框架中 namespace ui{class widget;} 是一种常见用法，通常出现在使用QT Designer设计GUI时自动生成的代码中；
  class widget是一个前向声明，声明一个名为widget的类，允许在.cpp源文件中引用由QT Designer创建的UI界面而不需要在头文件中包含完整的UI类定义；
  这种分离的方法有助于减少编译依赖性，并保持代码的清晰和组织；
  源文件中会创建一个Ui::QWidget类型的对象来访问和操作UI组件
*/
/*
  QT_BEGIN_NAMESPACE：QT框架中用于支持命名空间的宏定义，指定接下来的代码位于QT的命名空间。QT使用这些宏来确保其中中的类和函数不会与其它库中的同名类或函数冲突；
  通常与QT_END_NAMESPACE配对使用，标志着命名空间的结束。
*/

/*
  QT框架的QList类：内部实现类似数组，但也提供了一些链表的特性，旨在提供一个多数情况下高效又方便的通用列表容器
  1.数组式存储：大多数情况下使用连续的内存块来存储元素，方便按索引访问元素、迭代非常快速
  2.动态调整大小：当元素数量增加时，QList会自动调整其内部存储容量
  3.链表特性：拥有一些类似链表的操作：比如在列表的开始、结束处添加或删除元素
  4.复制时共享内存：隐式共享（写时复制）机制，在复制QList时不会立即复制其内容，而是共享同一块内存，直到其中一个列表被修改
*/
#include "ui_mynotebook.h"

class MyNotebook : public QWidget   //MyNotebook继承自QWidget
{
    //Q_OBJECT：是QT框架中一个非常重要的宏，用于启动QT对象的元对象系统；当你在QT中定义一个类时，如果这个类继承自QObject或其子类，并且想使用QT的信号与槽机制、
    //国际化、属性系统或其他QT元对象系统提供的功能，就必须在类定义中包含Q_OBJECT宏；该宏允许QT的元对象编译器（moc）识别并处理该类并生成额外代码
    //简单来说：Q_OBJECT宏为QT类提供了额外的元数据，使得类能够完全利用QT框架的功能
    Q_OBJECT

public:
    //记事本程序同一时间只处理一个文件，所以把QFile对象作为类的公有成员变量
	QFile file;  //文件对象

    //QComboBox：选择下拉框控件

    MyNotebook(QWidget *parent = nullptr);
    ~MyNotebook();
    void enterEvent(QEnterEvent*) override;     //鼠标移入窗口事件
    void leaveEvent(QEvent*) override;          //鼠标移出窗口事件
    void wheelEvent(QWheelEvent*) override;     //鼠标滚轮滚动事件
    void closeEvent(QCloseEvent*) override;     //窗口关闭事件
    void resizeEvent(QResizeEvent*) override;   //窗口大小改变事件

	bool eventFilter(QObject*, QEvent*); //事件过滤器函数
/*
  自定义信号函数：QT中使用关键字signals声明；只需要声明不需要实现
*/
signals:
    void mySignal(int);

/*
  1.使用QObject::connect()连接信号与槽，是最常用的方式
  例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
*/
/*
  自定义槽函数：槽函数是特殊的私有成员函数，使用 private slots: 来修饰
  可以是任意普通成员函数，可以有返回类型也可以接受参数，但参数类型需要与信号函数的参数类型匹配
*/
private slots:
    void on_btnOpen_clicked();
    void on_btnSave_clickedMyself();
    //void on_btnClose_clickedMyself();
    void on_btnOpen_clickedMyself();
	void onCursorPositionChanged(); //QTextEdit文本编辑框的槽函数
	void oncurrentIndexChanged(int index); //QComboBox选择框的槽函数
    void zoomIn();
    void zoomOut();
    void mySlot(int);

private:
    Ui::MyNotebookClass *ui;
};

