#include "mynotebook.h"
#include "ui_mynotebook.h"

/*
  �ź���ۣ�
  1.�ź�Signal���ɶ������ض��¼�����ʱ��������Ϣ������QPushButton��һ��clicked�źţ����û��������ʱ����
  2.��Slot��������Ӧ�źŵķ��������������⺯�������������źŷ���ʱ�òۺ���������
  3.�����ź���ۣ�ʹ��QObject::connect()�������ź����ӵ��ۣ����źŷ���ʱ�������Ĳۺ������Զ�ִ��
*/
/*
  ����QPushButton�����ź����֮������ӣ�
  1.ʹ��QObject::connect()�����ź���ۣ�����õķ�ʽ
  ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));

  2.ʹ��C++11 Lambda���ʽ������ֱ�������ӵ�ʹ������������ʹ��������
  ����QObject::connect(sender,&Sender::signal,[=](){ Lambda������ });

  3.ʹ�ú���ָ�룬QT5�����룬����ȫ�ҿ�����IDE�Ĵ��벹ȫ�ʹ����飻
  ����QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);

  4.ʹ��UI�ļ��Զ����ӣ�ʹ��QT Designerʱ��ͨ������Լ���Զ����ӣ���UI�ļ�����ʱ����on_<objectName>_<signal_name>�����Ĳۻ��Զ����ӵ���Ӧ�ź�
  ����QT Designer��������ťΪpushButton��Ȼ���ڴ����ж���on_pushButton_clicked()
*/

MyNotebook::MyNotebook(QWidget *parent)
    : QWidget(parent),ui(new Ui::MyNotebookClass)   //�вι��캯��ʹ�ó�ʼ�������б�
{
    //����QTDesigner�����UI������widget���˽�б���ui����
	//QT Widget Designer�н��в���֮�󣬰�Ctrl+B�����µ�ui_mynotebook.h�ļ���������������.h��.cpp�ļ�������
    ui->setupUi(this);
    //�����ڴ�С�����仯������Ĳ��ֲ�����֮�仯����Ҫͨ��this->setLayout()������ʽ˵�����ô��ڱ仯ʱ�����ּ����ӿؼ���֮����
    this->setLayout(ui->verticalLayout);
    //ʹ�ô�������UI��widgetBottom�ؼ���Ϊˮƽ����
    ui->widgetBottom->setLayout(ui->horizontalLayout);

    //ʹ�÷�ʽ1����QComboBox���ź���ۺ���
	connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(oncurrentIndexChanged(int)));
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MyNotebook::onCursorPositionChanged);

    /*
      1.ʹ��QObject::connect()�����ź���ۣ�����õķ�ʽ
      ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
    */
    QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(on_btnClose_clickedMyself()));

    /*
      2.ʹ��C++11 Lambda���ʽ������ֱ�������ӵ�ʹ������������ʹ��������
      ����QObject::connect(sender,&Sender::signal,[=](){ Lambda������ });
    */
    QObject::connect(ui->btnSave, &QPushButton::clicked, [=] {
        //���ļ����浽ָ��·��
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            "J:\\QT Codes\\MyNotebook\\untitled.txt", tr("Text Files (*.txt *.doc)"));
		qDebug() << "ѡ����ļ�·��Ϊ��" << fileName;
        //��qDebug()ȡ��std::cout���������Ϣ
        qDebug() << "btnSave��ť�����¡�";
        //1.���ļ�
        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "�ļ���ʧ�ܣ�";
            return;
        }
        this->setWindowTitle("MyNotebook--" + fileName); //���ô��ڱ���Ϊ������ļ���

        //2.д���ļ�
        //(1)ʹ��file.write()д���ļ�����
        //file.write("Hello, this is example2 file.����С�ԡ�\n"); //д������û����
        //(2)ʹ��QTextStreamд���ļ�����
        QTextStream out(&file);
        out.setEncoding(QStringConverter::Encoding::Utf8); //���ñ����ʽ��������������
        QString context = ui->textEdit->toPlainText();
        out << context;

        //3.�ر��ļ�
        //file.close();
    });

    /*
      3.ʹ�ú���ָ�룬QT5�����룬����ȫ�ҿ�����IDE�Ĵ��벹ȫ�ʹ����飻
      ����QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);
      on_btnOpen_clicked()����QPushButton�����źŶ�Ӧ��Ĭ�ϲۺ��������Զ���Ļ���д����������
    */
    QObject::connect(ui->btnOpen, &QPushButton::clicked, this, &MyNotebook::on_btnOpen_clickedMyself);

    /*
      �Զ����ź���۵�����
    */
    QObject::connect(this, SIGNAL(mySignal(int)), this, SLOT(mySlot(int)));
    emit mySignal(100);  //�����ź�
}

MyNotebook::~MyNotebook()
{
    delete ui;
}

void MyNotebook::on_btnClose_clickedMyself()
{
    if (file.isOpen())
    {
        file.close();
        ui->textEdit->clear();
        this->setWindowTitle("MyNotebook");
    }
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "btnClose��ť�����¡�";
    //this->close();  //�رյ�ǰ����
}

void MyNotebook::on_btnOpen_clickedMyself()
{
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "btnOpen��ť�����¡�";
}

/*
  4.ʹ��UI�ļ��Զ����ӣ�ʹ��QT Designer���ú�QPushButton������ʵ��������������on_<objectName>_<signal_name>�ۺ�����
  ��UI�ļ�����ʱ����on_<objectName>_<signal_name>�����Ĳۻ��Զ����ӵ���Ӧ�ź�
  ����QT Designer��������ťΪpushButton��Ȼ���ڴ����ж���on_pushButton_clicked()
*/
void MyNotebook::on_btnOpen_clicked()
{
    //QFileDialog�ࣺ�ļ�ѡ���
    QFileDialog qFileDialog;
    //QFileDialog::getOpenFileName()����̬����������һ���ļ�ѡ��Ի��������û�ѡ��һ���ļ������ظ��ļ���·��
    //(1)�򿪵����ļ����ļ�ѡ���
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), 
     "J:\\QT Codes\\MyNotebook", tr("Text Files (*.txt)"));

    //(2)�򿪶���ļ����ļ�ѡ���
    //qFileDialog.setWindowTitle("Open File"); //���öԻ������
    //qFileDialog.setDirectory("J:\\QT Codes\\MyNotebook"); //����Ĭ�ϴ�·��
    ////qFileDialog.setFileMode(QFileDialog::ExistingFile); //����ֻ��ѡ��һ���Ѵ��ڵ��ļ�
    //qFileDialog.setFileMode(QFileDialog::ExistingFiles);  //���ÿ���ѡ�����Ѵ��ڵ��ļ�
    //qFileDialog.exec(); //��ģ̬��ʽ��ʾ�Ի���������������ִ�У�ֱ���û��رնԻ���
    //QStringList fileNames = qFileDialog.selectedFiles(); //�����û�ѡ����ļ��б�
    //for (QString str : fileNames)
    //{
    //    qDebug() << str;
    //}
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "btnOpen��ť�����¡�";
    //1.���ļ�
	ui->textEdit->clear(); //ÿ�δ��ļ�ǰ��������ı��༭��
	file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "�ļ���ʧ�ܣ�";
        return;
    }
	this->setWindowTitle("MyNotebook--" + fileName); //���ô��ڱ���Ϊ�򿪵��ļ���
    int size = file.size();
    //2.��ȡ�ļ�
    //char context[size];   //�䳤����VLA������C++��׼��ĳЩ��������֧��
    //char* context = new char[size + 1]; //��̬�����ڴ�
    //(1)ʹ��file.read()��ȡ�ļ����ݵ�context����
    /*if(file.read(context,size)==-1)
    {
        qDebug() << "�ļ���ȡʧ�ܣ�";
        return;
    }
    qDebug() << "�ļ�����Ϊ��" << context;*/
    //delete context;

    //(2)ʹ��QTextStream��ȡ�ļ����ݵ�QString
    QTextStream in(&file);
    //in.setEncoding(QStringConverter::Encoding::Utf8); //���ñ����ʽ��������������
    
    //ui->comboBox->currentText()����һ��QString���ͱ�������Ҫ����ת����char*
    QString str = ui->comboBox->currentText();
    auto encoding = QStringConverter::encodingForName(str.toUtf8());
	//������QT5��д��
    //const char* c_str = str.toStdString().c_str();
	//����������ת��ΪQStringConverter::Encodingö��ֵ
    //auto encoding = QStringConverter::encodingForName();
	in.setEncoding(*encoding); //����ѡ��ı����ʽ��ȡ�ļ����ݣ�������������
    //file.seek(0);
    while (!in.atEnd())
    {
        QString context2 = in.readLine();
        qDebug() << context2;
        qDebug() << "--------";
		//QTextEdit�ؼ���ʾ��ȡ������
		//ui->textEdit->setText(context2);    //ֻ�����õ��У�ÿ�����ö��Ḳ�ǵ�֮ǰ������
		ui->textEdit->append(context2);     //����׷�Ӷ�������

		//ע�⣺��ʱ�ļ���ָ���ѵ����ļ�ĩβ���ٴζ�ȡ����������ݣ�������Ҫ����ָ����������Ϊ�ļ���ͷ

    }
    //3.�ر��ļ�
    //file.close();
}

void MyNotebook::oncurrentIndexChanged(int index)
{
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "QComboBoxѡ���Ĳۺ��������ã���ǰѡ�������ֵΪ��" << index;
    qDebug() << "��ǰѡ����ı�����Ϊ��" << ui->comboBox->currentText();
	ui->textEdit->clear(); //ÿ�θ��ı����ʽǰ��������ı��༭��
    if (file.isOpen())
    {
		QTextStream in(&file);
		auto encoding = QStringConverter::encodingForName(ui->comboBox->currentText().toUtf8());
		in.setEncoding(*encoding); //����ѡ��ı����ʽ��ȡ�ļ����ݣ�������������
        //ע�⣺��ʱ�ļ���ָ���ѵ����ļ�ĩβ���ٴζ�ȡ����������ݣ�������Ҫ����ָ����������Ϊ�ļ���ͷ
        file.seek(0);
        //�����ٶ��ļ�
        while (!in.atEnd())
        {
            QString context2 = in.readLine();
            //QTextEdit�ؼ���ʾ��ȡ������
            //ui->textEdit->setText(context2);    //ֻ�����õ��У�ÿ�����ö��Ḳ�ǵ�֮ǰ������
            ui->textEdit->append(context2);     //����׷�Ӷ�������
        }
    }
}

void MyNotebook::onCursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    //qDebug() << " " << cursor.blockNumber() + 1 << cursor.columnNumber() + 1;
	QString blockNum = QString::number(cursor.blockNumber() + 1);   //�к�
	QString colNum = QString::number(cursor.columnNumber() + 1);   //�к�
	const QString labelMsg = "Row: " + blockNum + " Col: " + colNum + " ";
    ui->labelPosition->setText(labelMsg);
}

void MyNotebook::mySlot(int val)
{
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "�Զ���ۺ���mySlot�����ã�����ֵΪ��" << val;
}