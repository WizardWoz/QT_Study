#include "mynotebook.h"
#include "ui_mynotebook.h"

/*
  信号与槽：
  1.信号Signal：由对象在特定事件发生时发出的消息；例如QPushButton有一个clicked信号，当用户点击按键时发出
  2.槽Slot：用来响应信号的方法，可以是任意函数；当关联的信号发出时该槽函数被调用
  3.连接信号与槽：使用QObject::connect()方法将信号连接到槽；当信号发出时，关联的槽函数会自动执行
*/
/*
  按键QPushButton设置信号与槽
  1.使用QObject::connect()连接信号与槽，是最常用的方式
  例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));

  2.使用C++11 Lambda表达式。可以直接在连接点使用匿名函数，使代码更简洁
  例：QObject::connect(sender,&Sender::signal,[=](){ Lambda函数体 });

  3.使用函数指针，QT5中引入，更安全且可利用IDE的代码补全和错误检查；
  例：QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);

  4.使用UI文件自动连接，使用QT Designer时可通过命名约定自动连接；当UI文件加载时，以on_<objectName>_<signal_name>命名的槽会自动连接到相应信号
  例：QT Designer中命名按钮为pushButton，然后在代码中定义on_pushButton_clicked()
*/

MyNotebook::MyNotebook(QWidget *parent)
    : QWidget(parent),ui(new Ui::MyNotebookClass)   //有参构造函数使用初始化参数列表
{
    //设置QTDesigner里面的UI关联到widget类的私有变量ui里面
    ui->setupUi(this);
    //当窗口大小发生变化，里面的布局不会随之变化；需要通过this->setLayout()进行显式说明，让窗口变化时，布局及其子控件随之调整
    this->setLayout(ui->verticalLayout);
    //使用代码设置UI的widgetBottom控件成为水平布局
    ui->widgetBottom->setLayout(ui->horizontalLayout);

    //在构造函数中连接信号与槽
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(on_btnClose_clickedMyself()));
}

MyNotebook::~MyNotebook()
{
    delete ui;
}

void MyNotebook::on_btnClose_clickedMyself()
{

}

/*
  1.使用QObject::connect()连接信号与槽，是最常用的方式
  例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
*/
void MyNotebook::on_btnOpen_clicked()
{
    std::cout << "btnOpen按钮被按下。" << std::endl;
}