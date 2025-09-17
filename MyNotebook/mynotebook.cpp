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
  1.ʹ��QObject::connect()�����ź���ۣ������Զ���ۺ������ұ���ʹ����Ĭ�ϲۺ�����ͬ�ĺ�����
  ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));

  2.ʹ��C++11 Lambda���ʽ������ֱ�������ӵ�ʹ������������ʹ�������࣬��ʱ�źű���ʹ�ú�������
  ����QObject::connect(sender,&Sender::signal,[=](){ Lambda������ });

  3.ʹ�ú���ָ�룬QT5�����룬����ȫ�ҿ�����IDE�Ĵ��벹ȫ�ʹ����飻
  ����QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);

  4.ʹ��UI�ļ��Զ����ӣ�ʹ��QT Designerʱ��ͨ������Լ���Զ����ӣ���UI�ļ�����ʱ����on_<objectName>_<signal_name>������Ĭ�ϲۺ������Զ����ӵ���Ӧ�ź�
  ����QT Designer��������ťΪpushButton��Ȼ���ڴ����ж���on_pushButton_clicked()
*/
/*
  1.QT�����л��ڴ��ڵ�Ӧ�ó���ײ���������¼�����Ŀ����ʵ�ֻص���ֻ�����������Ч�ʲ�����ߣ���QT�ڲ��ṩ���¼�������ƣ�
  �������� ����->�ɷ�->����->�ַ�->���� �ĸ��׶Ρ�QT�����¼�����Ĭ�ϵĴ�����������������������ں��ʽ׶���д�¼��������������Զ����ź���ۣ�
  
  2.�¼���ϵͳ��QT�����ڲ�ͬ�����·��������û����¡��ƶ���꣬�û����̣����ߴ��ڹرա���С�仯��������ʾ�ȶ��ᷢ����Ӧ�¼���
  һЩ�¼��ڶ��û�����������Ӧʱ����������ꡢ�����¼�����һЩ�¼�������ϵͳ�Զ����������ʱ���¼�

  3.ÿһ��QTӦ�ó����Ӧһ��Ψһ��QApplicationӦ�ó�����󣬵��øö����exec()�����������ڲ����¼����Ϳ�ʼ�ˣ����򽫽����¼�ѭ��������Ӧ�ó���

  4.(1)���赱ǰ������һ���¼�
  (2)QTʹ��Ӧ�ó���������notify()�������¼��ɷ���ָ������ bool QApplication::notify(QObject* receiver,QEvent* e)
  (3)�¼����������ɷ������н��й��ˣ�Ĭ�ϲ����κβ������¼����й��� bool QObject::eventFilter(QObject* watched,QEvent* e)
  (4)�¼����͵�ָ�����ں󣬴��ڵ��¼��ַ������յ����¼����зַ� bool QWidget::event(QEvent* e)
  (5)�����¼������������¼������� void QWidget::mousePressEvent(QMouseEvent* e)
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

    //ʹ��QShortcut������Ŵ���С��ݼ�����
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

    //ʹ�÷�ʽ1����QComboBox���ź���ۺ���
    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(oncurrentIndexChanged(int)));
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MyNotebook::onCursorPositionChanged);

    //Ϊ�Զ��尴�������ź���ۺ���
    /*connect(ui->mybtn, &MyButton::clicked, [=]() {
        qDebug() << "MyButton is clicked.";
    });*/

    

    /*
      1.ʹ��QObject::connect()�����ź���ۣ�����õķ�ʽ
      ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
    */
    //QObject::connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(on_btnClose_clickedMyself()));
    QObject::connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clickedMyself()));
    /*
      2.ʹ��C++11 Lambda���ʽ������ֱ�������ӵ�ʹ������������ʹ��������
      ����QObject::connect(sender,&Sender::signal,[=](){ Lambda������ });
    */
    //QObject::connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(on_btnSave_clicked()));
    QObject::connect(ui->btnClose, &QPushButton::clicked, [=]() {
        //ui->textEdit->clear();
        //�ر�������ǰ��������ʾ��
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
        //��qDebug()ȡ��std::cout���������Ϣ
        qDebug() << "btnClose��ť�����¡�";
        //this->close();  //�رյ�ǰ����
    });
    /*
      3.ʹ�ú���ָ�룬QT5�����룬����ȫ�ҿ�����IDE�Ĵ��벹ȫ�ʹ����飻
      ����QObject::connect(sender,&Sender::signal,receiver,&Receiver::slot);
      on_xxx_clicked()����QPushButton�����źŶ�Ӧ��Ĭ�ϲۺ��������Զ���Ļ���д��������������on_btnOpen_clickedMyself
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

void MyNotebook::on_btnSave_clickedMyself()
{
    if (!file.isOpen())
    {
        //���ļ����浽ָ��·��
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            "J:\\QT Codes\\MyNotebook\\untitled.txt", tr("Text Files (*.txt *.doc)"));
        qDebug() << "ѡ����ļ�·��Ϊ��" << fileName;
        //��qDebug()ȡ��std::cout���������Ϣ
        qDebug() << "btnSave��ť�����¡�";
        //1.���ļ�
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "�ļ���ʧ�ܣ�";
            return;
        }
        this->setWindowTitle("MyNotebook--" + fileName); //���ô��ڱ���Ϊ������ļ���
    }
    //2.д���ļ�
    //(1)ʹ��file.write()д���ļ�����
    //file.write("Hello, this is example2 file.����С�ԡ�\n"); //д������û����
    //(2)ʹ��QTextStreamд���ļ�����
    QTextStream out(&file);
    //out.setEncoding(QStringConverter::Encoding::Utf8); //���ñ����ʽ��������������
    QString str = ui->comboBox->currentText();
    auto encoding = QStringConverter::encodingForName(str.toUtf8());
    //������QT5��д��
    //const char* c_str = str.toStdString().c_str();
    //����������ת��ΪQStringConverter::Encodingö��ֵ
    //auto encoding = QStringConverter::encodingForName();
    out.setEncoding(*encoding); //����ѡ��ı����ʽ��ȡ�ļ����ݣ�������������
    QString context = ui->textEdit->toPlainText();
    out << context;

    //3.�ر��ļ�
    //file.close();
}

void MyNotebook::on_btnOpen_clickedMyself()
{
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "btnOpen��ť�����¡�";
}

/*
  4.ʹ��UI�ļ��Զ����ӣ�ʹ��QT Designer���ú�QPushButton������ʵ��������������on_<objectName>_<signal_name>�ۺ�����
  ��UI�ļ�����ʱ����on_<objectName>_<signal_name>������Ĭ�ϲۺ������Զ����ӵ���Ӧ�ź�
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
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
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

void MyNotebook::zoomIn()
{
    //1.���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //2.��õ�ǰ�����С
    int fontSize = font.pointSize();
    if (fontSize == -1)
    {
        return;
    }
    //3.�ı��С�������������С
    int newFontSize = fontSize + 1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}

void MyNotebook::zoomOut()
{
    //1.���TextEdit�ĵ�ǰ������Ϣ
    QFont font = ui->textEdit->font();
    //2.��õ�ǰ�����С
    int fontSize = font.pointSize();
    if (fontSize == -1)
    {
        return;
    }
    //3.�ı��С�������������С
    int newFontSize = fontSize - 1;
    font.setPointSize(newFontSize);
    ui->textEdit->setFont(font);
}

void MyNotebook::onCursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    //qDebug() << " " << cursor.blockNumber() + 1 << cursor.columnNumber() + 1;
	QString blockNum = QString::number(cursor.blockNumber() + 1);   //�к�
	QString colNum = QString::number(cursor.columnNumber() + 1);   //�к�
	const QString labelMsg = "Row: " + blockNum + " Col: " + colNum + " ";
    ui->labelPosition->setText(labelMsg);
    //���õ�ǰ�и���
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection ext;
    //1.��ȡ��ǰ��
    ext.cursor = ui->textEdit->textCursor();
    QBrush qBrush(Qt::lightGray);
    //2.������ɫ
    ext.format.setBackground(qBrush);
    //���ö����ԣ�������ʾ
    ext.format.setProperty(QTextFormat::FullWidthSelection, true);
    //3.���ã���ext���뵽ext��������
    extraSelections.append(ext);
    ui->textEdit->setExtraSelections(extraSelections);
}

void MyNotebook::mySlot(int val)
{
    //��qDebug()ȡ��std::cout���������Ϣ
    qDebug() << "�Զ���ۺ���mySlot�����ã�����ֵΪ��" << val;
}