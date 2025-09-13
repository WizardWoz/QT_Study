#include "mynotebook.h"
#include "ui_mynotebook.h"

/*
  信号与槽：
  1.信号Signal：由对象在特定事件发生时发出的消息；例如QPushButton有一个clicked信号，当用户点击按键时发出
  2.槽Slot：用来响应信号的方法，可以是任意函数；当关联的信号发出时该槽函数被调用
  3.连接信号与槽：使用QObject::connect()方法将信号连接到槽；当信号发出时，关联的槽函数会自动执行
*/
/*
  按键QPushButton设置信号与槽之间的连接：
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

    /*
      1.使用QObject::connect()连接信号与槽，是最常用的方式
      例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
    */
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(on_btnClose_clickedMyself()));

    /*
      2.使用C++11 Lambda表达式。可以直接在连接点使用匿名函数，使代码更简洁
      例：QObject::connect(sender,&Sender::signal,[=](){ Lambda函数体 });
    */
    QObject::connect(ui->btnSave, &QPushButton::clicked, [=] {
        //将文件保存到指定路径
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            "J:\\QT Codes\\MyNotebook\\untitled.txt", tr("Text Files (*.txt *.doc)"));
		qDebug() << "选择的文件路径为：" << fileName;
        //用qDebug()取代std::cout输出调试信息
        qDebug() << "btnSave按钮被按下。";
        //1.打开文件
        QFile file;
        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "文件打开失败！";
            return;
        }
        
        //2.写入文件
        //(1)使用file.write()写入文件内容
        file.write("Hello, this is example2 file.我是小赵。\n"); //写入中文没问题
        //(2)使用QTextStream写入文件内容
        QTextStream out(&file);
        //out.setEncoding(QStringConverter::Encoding::Utf8); //设置编码格式，避免中文乱码
        out << "QDialog write data to the txt file.";

        //3.关闭文件
        file.close();
    });

    /*
      3.使用函数指针，QT5中引入，更安全且可利用IDE的代码补全和错误检查；
      例：QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);
    */
    //QObject::connect(ui->btnOpen, &QPushButton::clicked, this, &MyNotebook::on_btnOpen_clicked);

    /*
      自定义信号与槽的链接
    */
    QObject::connect(this, SIGNAL(mySignal(int)), this, SLOT(mySlot(int)));
    emit mySignal(100);  //发射信号
}

MyNotebook::~MyNotebook()
{
    delete ui;
}

void MyNotebook::on_btnClose_clickedMyself()
{
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "btnClose按钮被按下。";
    this->close();  //关闭当前窗口
}

/*
  4.使用UI文件自动连接，使用QT Designer设置好QPushButton，在类实现中声明并定义on_<objectName>_<signal_name>槽函数；
  当UI文件加载时，以on_<objectName>_<signal_name>命名的槽会自动连接到相应信号
  例：QT Designer中命名按钮为pushButton，然后在代码中定义on_pushButton_clicked()
*/
void MyNotebook::on_btnOpen_clicked()
{
    //QFileDialog类：文件选择框
    QFileDialog qFileDialog;
    //QFileDialog::getOpenFileName()：静态函数，弹出一个文件选择对话框，允许用户选择一个文件并返回该文件的路径
    //QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), 
    // "J:\\QT Codes\\MyNotebook", tr("Image Files (*.png *.jpg *.bmp)"));
    qFileDialog.setWindowTitle("打开文件"); //设置对话框标题
    qFileDialog.setDirectory("J:\\QT Codes\\MyNotebook"); //设置默认打开路径
    //qFileDialog.setFileMode(QFileDialog::ExistingFile); //设置只能选择一个已存在的文件
    qFileDialog.setFileMode(QFileDialog::ExistingFiles);  //设置可以选择多个已存在的文件
    qFileDialog.exec(); //以模态方式显示对话框，阻塞后续代码执行，直到用户关闭对话框
    QStringList filename = qFileDialog.selectedFiles(); //返回用户选择的文件列表
    for (QString str : filename)
    {
        qDebug() << str;
    }
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "btnOpen按钮被按下。";
    //1.打开文件
    QFile file("J:\\QT Codes\\MyNotebook\\example1.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "文件打开失败！";
        return;
    }
    int size = file.size();
    //2.读取文件
    //char context[size];   //变长数组VLA，不是C++标准，某些编译器不支持
    char* context = new char[size + 1]; //动态分配内存
    //(1)使用file.read()读取文件内容到context数组
    if(file.read(context,size)==-1)
    {
        qDebug() << "文件读取失败！";
        return;
    }
    qDebug() << "文件内容为：" << context;
    //(2)使用QTextStream读取文件内容到QString
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Encoding::Utf8); //设置编码格式，避免中文乱码
    while (!in.atEnd())
    {
        QString context2 = in.readLine();
        qDebug() << context2;
        qDebug() << "--------";
    }
    //3.关闭文件
    file.close();
}

void MyNotebook::mySlot(int val)
{
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "自定义槽函数mySlot被调用，参数值为：" << val;
}