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
  1.使用QObject::connect()连接信号与槽，必须自定义槽函数，且必须使用与默认槽函数不同的函数名
  例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));

  2.使用C++11 Lambda表达式。可以直接在连接点使用匿名函数，使代码更简洁，此时信号必须使用函数引用
  例：QObject::connect(sender,&Sender::signal,[=](){ Lambda函数体 });

  3.使用函数指针，QT5中引入，更安全且可利用IDE的代码补全和错误检查；
  例：QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);

  4.使用UI文件自动连接，使用QT Designer时可通过命名约定自动连接；当UI文件加载时，以on_<objectName>_<signal_name>命名的默认槽函数会自动连接到相应信号
  例：QT Designer中命名按钮为pushButton，然后在代码中定义on_pushButton_clicked()
*/
/*
  1.QT中所有基于窗口的应用程序底层均借助了事件处理，目的是实现回调（只有这样程序的效率才是最高）；QT内部提供了事件处理机制，
  过程如下 产生->派发->过滤->分发->处理 四个阶段。QT对于事件都有默认的处理动作；如果有特殊需求则在合适阶段重写事件处理动作（例如自定义信号与槽）
  
  2.事件由系统或QT本身在不同场景下发出；当用户按下、移动鼠标，敲击键盘；或者窗口关闭、大小变化、隐藏显示等都会发出相应事件。
  一些事件在对用户操作作出响应时发出，如鼠标、键盘事件；另一些事件则是由系统自动发出，如计时器事件

  3.每一个QT应用程序对应一个唯一的QApplication应用程序对象，调用该对象的exec()函数，则框架内部的事件检测就开始了，程序将进入事件循环来监听应用程序

  4.(1)假设当前产生了一个事件
  (2)QT使用应用程序对象调用notify()函数将事件派发到指定窗口 bool QApplication::notify(QObject* receiver,QEvent* e)
  (3)事件过滤器在派发过程中进行过滤，默认不对任何产生的事件进行过滤 bool QObject::eventFilter(QObject* watched,QEvent* e)
  (4)事件发送到指定窗口后，窗口的事件分发器对收到的事件进行分发 bool QWidget::event(QEvent* e)
  (5)最终事件处理函数接收事件并处理 void QWidget::mousePressEvent(QMouseEvent* e)
*/

MyNotebook::MyNotebook(QWidget *parent)
    : QWidget(parent),ui(new Ui::MyNotebookClass)   //有参构造函数使用初始化参数列表
{
    //设置QTDesigner里面的UI关联到widget类的私有变量ui里面
	//QT Widget Designer中进行操作之后，按Ctrl+B生成新的ui_mynotebook.h文件，便于在其它的.h、.cpp文件中引用
    ui->setupUi(this);
    /*
      自定义事件，安装事件过滤器
    */
    ui->textEdit->viewport()->installEventFilter(this);  //为textEdit文本编辑框安装事件过滤器
    //当窗口大小发生变化，里面的布局不会随之变化；需要通过this->setLayout()进行显式说明，让窗口变化时，布局及其子控件随之调整
    this->setLayout(ui->verticalLayout);
    //使用代码设置UI的widgetBottom控件成为水平布局
    ui->widgetBottom->setLayout(ui->horizontalLayout);

    //使用QShortcut类引入放大、缩小快捷键功能
    QShortcut* shortcutOpen = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
    QShortcut* shortcutSave = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this);
    QShortcut* shortcutZoomIn = new QShortcut(QKeySequence(tr("Ctrl+Shift+=", "File|Save")), this);
    QShortcut* shortcutZoomOut = new QShortcut(QKeySequence(tr("Ctrl+Shift+-", "File|Save")), this);
    QObject::connect(shortcutOpen, &QShortcut::activated, [=]() {
        on_btnOpen_clicked();
    });
    connect(shortcutSave, &QShortcut::activated, [=]() {
        on_btnSave_clickedMyself();
    });
    connect(shortcutZoomIn, &QShortcut::activated, [=]() {
        zoomIn();
    });
    connect(shortcutZoomOut, &QShortcut::activated, [=]() {
        zoomOut();
    });

    //使用方式1连接QComboBox的信号与槽函数
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(oncurrentIndexChanged(int)));
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MyNotebook::onCursorPositionChanged);

    //为自定义按键连接信号与槽函数
    /*connect(ui->mybtn, &MyButton::clicked, [=]() {
        qDebug() << "MyButton is clicked.";
    });*/

    

    /*
      1.使用QObject::connect()连接信号与槽，是最常用的方式
      例：QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
    */
    //QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(on_btnClose_clickedMyself()));
    QObject::connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clickedMyself()));
    /*
      2.使用C++11 Lambda表达式。可以直接在连接点使用匿名函数，使代码更简洁
      例：QObject::connect(sender,&Sender::signal,[=](){ Lambda函数体 });
    */
    //QObject::connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));
    QObject::connect(ui->btnClose, &QPushButton::clicked, [=]() {
        //ui->textEdit->clear();
        //关闭主界面前，出现提示框
        QMessageBox msgBox;
        /*msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);*/
        int ret = QMessageBox::warning(this, tr("MyNotebook"), tr("The document has been modified.\nDo you want to save your changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
        switch (ret)
        {
        case QMessageBox::Save:
            qDebug() << "QMessageBox::Save";
            on_btnSave_clickedMyself();
            break;
        case QMessageBox::Discard:
            qDebug() << "QMessageBox::Discard";
            ui->textEdit->clear();
            if (file.isOpen())
            {
                file.close();
                this->setWindowTitle("MyNotebook");
            }
            break;
        case QMessageBox::Cancel:
            qDebug() << "QMessageBox::Cancel";
            break;
        default:
            break;
        }
        //用qDebug()取代std::cout输出调试信息
        qDebug() << "btnClose按钮被按下。";
        //this->close();  //关闭当前窗口
    });
    /*
      3.使用函数指针，QT5中引入，更安全且可利用IDE的代码补全和错误检查；
      例：QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);
      on_xxx_clicked()：是QPushButton按下信号对应的默认槽函数名；自定义的话可写成其它名称例如on_btnOpen_clickedMyself
    */
    QObject::connect(ui->btnOpen, &QPushButton::clicked, this, &MyNotebook::on_btnOpen_clickedMyself);

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

void MyNotebook::enterEvent(QEnterEvent* event)
{
    qDebug() << "mouse in.";
}

void MyNotebook::leaveEvent(QEvent* event)
{
    qDebug() << "mouse out.";
}

void MyNotebook::wheelEvent(QWheelEvent* event)
{
    qDebug() << event->angleDelta();
}

void MyNotebook::closeEvent(QCloseEvent* event)
{
    int ret = QMessageBox::warning(this, tr("MyNotebook"), tr("Close the window.\nDo you want to close the window?"),
        QMessageBox::Ok | QMessageBox::No);
    switch (ret)
    {
    case QMessageBox::Ok:
        event->accept();
        break;
    case QMessageBox::No:
        event->ignore();
        break;
    default:
        break;
    }
}

void MyNotebook::resizeEvent(QResizeEvent* event)
{
    qDebug() << "oldSize:" << event->oldSize() << "newSize:" << event->size();
}

bool MyNotebook::eventFilter(QObject* watched, QEvent* event)
{
    /*if (event->type() == QEvent::MouseButtonDblClick)
    {
        qDebug() << "mouse button event filtered.";
    }
	QKeyEvent* keyEvent = (QKeyEvent*)event;
    if (keyEvent->key() == Qt::Key_Control)
    {
		qDebug() << "Ctrl key event filtered.";
    }*/

    //放大后，把光标停留在文本中间某个位置，按住ctrl + 滚轮，会优先执行文本的上下滚动而不是放大或缩小
    if (event->type() == QEvent::Wheel)
    {
		qDebug() << "wheel event filtered.";
        //C++动态类型转换
		QWheelEvent* wheelEvent = dynamic_cast<QWheelEvent*>(event);
        if (QGuiApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            qDebug() << "Ctrl+Wheel event filtered.";
            if (wheelEvent->angleDelta().y() > 0)
            {
                zoomIn();
            }
            else if (wheelEvent->angleDelta().y() < 0)
            {
                zoomOut();
			}
			return true; //事件过滤器处理该事件，不再向下传递
        }
        return false;
    }
    
}

void MyNotebook::on_btnSave_clickedMyself()
{
    if (!file.isOpen())
    {
        //将文件保存到指定路径
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            "J:\\QT Codes\\MyNotebook\\untitled.txt", tr("Text Files (*.txt *.doc)"));
        qDebug() << "选择的文件路径为：" << fileName;
        //用qDebug()取代std::cout输出调试信息
        qDebug() << "btnSave按钮被按下。";
        //1.打开文件
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "文件打开失败！";
            return;
        }
        this->setWindowTitle("MyNotebook--" + fileName); //设置窗口标题为保存的文件名
    }
    //2.写入文件
    //(1)使用file.write()写入文件内容
    //file.write("Hello, this is example2 file.我是小赵。\n"); //写入中文没问题
    //(2)使用QTextStream写入文件内容
    QTextStream out(&file);
    //out.setEncoding(QStringConverter::Encoding::Utf8); //设置编码格式，避免中文乱码
    QString str = ui->comboBox->currentText();
    auto encoding = QStringConverter::encodingForName(str.toUtf8());
    //以下是QT5的写法
    //const char* c_str = str.toStdString().c_str();
    //将编码名称转换为QStringConverter::Encoding枚举值
    //auto encoding = QStringConverter::encodingForName();
    out.setEncoding(*encoding); //根据选择的编码格式读取文件内容，避免中文乱码
    QString context = ui->textEdit->toPlainText();
    out << context;

    //3.关闭文件
    //file.close();
}

void MyNotebook::on_btnOpen_clickedMyself()
{
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "btnOpen按钮被按下。";
}

/*
  4.使用UI文件自动连接，使用QT Designer设置好QPushButton，在类实现中声明并定义on_<objectName>_<signal_name>槽函数；
  当UI文件加载时，以on_<objectName>_<signal_name>命名的默认槽函数会自动连接到相应信号
  例：QT Designer中命名按钮为pushButton，然后在代码中定义on_pushButton_clicked()
*/
void MyNotebook::on_btnOpen_clicked()
{
    //QFileDialog类：文件选择框
    QFileDialog qFileDialog;
    //QFileDialog::getOpenFileName()：静态函数，弹出一个文件选择对话框，允许用户选择一个文件并返回该文件的路径
    //(1)打开单个文件的文件选择框
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), 
     "J:\\QT Codes\\MyNotebook", tr("Text Files (*.txt)"));

    //(2)打开多个文件的文件选择框
    //qFileDialog.setWindowTitle("Open File"); //设置对话框标题
    //qFileDialog.setDirectory("J:\\QT Codes\\MyNotebook"); //设置默认打开路径
    ////qFileDialog.setFileMode(QFileDialog::ExistingFile); //设置只能选择一个已存在的文件
    //qFileDialog.setFileMode(QFileDialog::ExistingFiles);  //设置可以选择多个已存在的文件
    //qFileDialog.exec(); //以模态方式显示对话框，阻塞后续代码执行，直到用户关闭对话框
    //QStringList fileNames = qFileDialog.selectedFiles(); //返回用户选择的文件列表
    //for (QString str : fileNames)
    //{
    //    qDebug() << str;
    //}
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "btnOpen按钮被按下。";
    //1.打开文件
	ui->textEdit->clear(); //每次打开文件前，先清空文本编辑框
	file.setFileName(fileName);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "文件打开失败！";
        return;
    }
	this->setWindowTitle("MyNotebook--" + fileName); //设置窗口标题为打开的文件名
    int size = file.size();
    //2.读取文件
    //char context[size];   //变长数组VLA，不是C++标准，某些编译器不支持
    //char* context = new char[size + 1]; //动态分配内存
    //(1)使用file.read()读取文件内容到context数组
    /*if(file.read(context,size)==-1)
    {
        qDebug() << "文件读取失败！";
        return;
    }
    qDebug() << "文件内容为：" << context;*/
    //delete context;

    //(2)使用QTextStream读取文件内容到QString
    QTextStream in(&file);
    //in.setEncoding(QStringConverter::Encoding::Utf8); //设置编码格式，避免中文乱码
    
    //ui->comboBox->currentText()：是一个QString类型变量，需要将其转化成char*
    QString str = ui->comboBox->currentText();
    auto encoding = QStringConverter::encodingForName(str.toUtf8());
	//以下是QT5的写法
    //const char* c_str = str.toStdString().c_str();
	//将编码名称转换为QStringConverter::Encoding枚举值
    //auto encoding = QStringConverter::encodingForName();
	in.setEncoding(*encoding); //根据选择的编码格式读取文件内容，避免中文乱码
    //file.seek(0);
    while (!in.atEnd())
    {
        QString context2 = in.readLine();
        qDebug() << context2;
        qDebug() << "--------";
		//QTextEdit控件显示读取的内容
		//ui->textEdit->setText(context2);    //只能设置单行，每次设置都会覆盖掉之前的内容
		ui->textEdit->append(context2);     //可以追加多行内容

		//注意：此时文件读指针已到达文件末尾，再次读取会读不到内容，所以需要将读指针重新设置为文件开头

    }
    //3.关闭文件
    //file.close();
}

void MyNotebook::oncurrentIndexChanged(int index)
{
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "QComboBox选择框的槽函数被调用，当前选择的索引值为：" << index;
    qDebug() << "当前选择的文本内容为：" << ui->comboBox->currentText();
	ui->textEdit->clear(); //每次更改编码格式前，先清空文本编辑框
    if (file.isOpen())
    {
		QTextStream in(&file);
		auto encoding = QStringConverter::encodingForName(ui->comboBox->currentText().toUtf8());
		in.setEncoding(*encoding); //根据选择的编码格式读取文件内容，避免中文乱码
        //注意：此时文件读指针已到达文件末尾，再次读取会读不到内容，所以需要将读指针重新设置为文件开头
        file.seek(0);
        //重新再读文件
        while (!in.atEnd())
        {
            QString context2 = in.readLine();
            //QTextEdit控件显示读取的内容
            //ui->textEdit->setText(context2);    //只能设置单行，每次设置都会覆盖掉之前的内容
            ui->textEdit->append(context2);     //可以追加多行内容
        }
    }
}

void MyNotebook::zoomIn()
{
    //1.获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //2.获得当前字体大小
    int fontSize = font.pointSize();
    if (fontSize == -1)
    {
        return;
    }
    //3.改变大小，并设置字体大小
    int newFontSize = fontSize + 1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}

void MyNotebook::zoomOut()
{
    //1.获得TextEdit的当前字体信息
    QFont font = ui->textEdit->font();
    //2.获得当前字体大小
    int fontSize = font.pointSize();
    if (fontSize == -1)
    {
        return;
    }
    //3.改变大小，并设置字体大小
    int newFontSize = fontSize - 1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}

void MyNotebook::onCursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    //qDebug() << " " << cursor.blockNumber() + 1 << cursor.columnNumber() + 1;
	QString blockNum = QString::number(cursor.blockNumber() + 1);   //行号
	QString colNum = QString::number(cursor.columnNumber() + 1);   //列号
	const QString labelMsg = "Row: " + blockNum + " Col: " + colNum + " ";
    ui->labelPosition->setText(labelMsg);
    //设置当前行高亮
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection ext;
    //1.获取当前行
    ext.cursor = ui->textEdit->textCursor();
    QBrush qBrush(Qt::lightGray);
    //2.设置颜色
    ext.format.setBackground(qBrush);
    //配置段属性，整行显示
    ext.format.setProperty(QTextFormat::FullWidthSelection, true);
    //3.设置，把ext加入到ext的容器中
    extraSelections.append(ext);
    ui->textEdit->setExtraSelections(extraSelections);
}

void MyNotebook::mySlot(int val)
{
    //用qDebug()取代std::cout输出调试信息
    qDebug() << "自定义槽函数mySlot被调用，参数值为：" << val;
}