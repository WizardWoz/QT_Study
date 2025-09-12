#pragma once
#include <iostream>
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

#include <QtWidgets/QWidget>
#include "ui_mynotebook.h"

class MyNotebook : public QWidget   //MyNotebook继承自QWidget
{
    //Q_OBJECT：是QT框架中一个非常重要的宏，用于启动QT对象的元对象系统；当你在QT中定义一个类时，如果这个类继承自QObject或其子类，并且想使用QT的信号与槽机制、
    //国际化、属性系统或其他QT元对象系统提供的功能，就必须在类定义中包含Q_OBJECT宏；该宏允许QT的元对象编译器（moc）识别并处理该类并生成额外代码
    //简单来说：Q_OBJECT宏为QT类提供了额外的元数据，使得类能够完全利用QT框架的功能
    Q_OBJECT

public:
    MyNotebook(QWidget *parent = nullptr);
    ~MyNotebook();

/*
  槽函数是特殊的私有成员函数，使用 private slots: 来修饰
*/
private slots:
    void on_btnOpen_clicked();
    void on_btnClose_clickedMyself();

private:
    Ui::MyNotebookClass *ui;
};

