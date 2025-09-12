#include "mynotebook.h"
#include "ui_mynotebook.h"

/*
  �ź���ۣ�
  1.�ź�Signal���ɶ������ض��¼�����ʱ��������Ϣ������QPushButton��һ��clicked�źţ����û��������ʱ����
  2.��Slot��������Ӧ�źŵķ��������������⺯�������������źŷ���ʱ�òۺ���������
  3.�����ź���ۣ�ʹ��QObject::connect()�������ź����ӵ��ۣ����źŷ���ʱ�������Ĳۺ������Զ�ִ��
*/
/*
  ����QPushButton�����ź����
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
    ui->setupUi(this);
    //�����ڴ�С�����仯������Ĳ��ֲ�����֮�仯����Ҫͨ��this->setLayout()������ʽ˵�����ô��ڱ仯ʱ�����ּ����ӿؼ���֮����
    this->setLayout(ui->verticalLayout);
    //ʹ�ô�������UI��widgetBottom�ؼ���Ϊˮƽ����
    ui->widgetBottom->setLayout(ui->horizontalLayout);

    //�ڹ��캯���������ź����
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
  1.ʹ��QObject::connect()�����ź���ۣ�����õķ�ʽ
  ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
*/
void MyNotebook::on_btnOpen_clicked()
{
    std::cout << "btnOpen��ť�����¡�" << std::endl;
}