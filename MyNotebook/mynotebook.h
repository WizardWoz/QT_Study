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
#include "mybutton.h"

/*
  ui�����ռ䣺QT����� namespace ui{class widget;} ��һ�ֳ����÷���ͨ��������ʹ��QT Designer���GUIʱ�Զ����ɵĴ����У�
  class widget��һ��ǰ������������һ����Ϊwidget���࣬������.cppԴ�ļ���������QT Designer������UI���������Ҫ��ͷ�ļ��а���������UI�ඨ�壻
  ���ַ���ķ��������ڼ��ٱ��������ԣ������ִ������������֯��
  Դ�ļ��лᴴ��һ��Ui::QWidget���͵Ķ��������ʺͲ���UI���
*/
/*
  QT_BEGIN_NAMESPACE��QT���������֧�������ռ�ĺ궨�壬ָ���������Ĵ���λ��QT�������ռ䡣QTʹ����Щ����ȷ�������е���ͺ����������������е�ͬ���������ͻ��
  ͨ����QT_END_NAMESPACE���ʹ�ã���־�������ռ�Ľ�����
*/

/*
  QT��ܵ�QList�ࣺ�ڲ�ʵ���������飬��Ҳ�ṩ��һЩ��������ԣ�ּ���ṩһ����������¸�Ч�ַ����ͨ���б�����
  1.����ʽ�洢������������ʹ���������ڴ�����洢Ԫ�أ����㰴��������Ԫ�ء������ǳ�����
  2.��̬������С����Ԫ����������ʱ��QList���Զ��������ڲ��洢����
  3.�������ԣ�ӵ��һЩ��������Ĳ������������б�Ŀ�ʼ����������ӻ�ɾ��Ԫ��
  4.����ʱ�����ڴ棺��ʽ����дʱ���ƣ����ƣ��ڸ���QListʱ�����������������ݣ����ǹ���ͬһ���ڴ棬ֱ������һ���б��޸�
*/
#include "ui_mynotebook.h"

class MyNotebook : public QWidget   //MyNotebook�̳���QWidget
{
    //Q_OBJECT����QT�����һ���ǳ���Ҫ�ĺ꣬��������QT�����Ԫ����ϵͳ��������QT�ж���һ����ʱ����������̳���QObject�������࣬������ʹ��QT���ź���ۻ��ơ�
    //���ʻ�������ϵͳ������QTԪ����ϵͳ�ṩ�Ĺ��ܣ��ͱ������ඨ���а���Q_OBJECT�ꣻ�ú�����QT��Ԫ�����������moc��ʶ�𲢴�����ಢ���ɶ������
    //����˵��Q_OBJECT��ΪQT���ṩ�˶����Ԫ���ݣ�ʹ�����ܹ���ȫ����QT��ܵĹ���
    Q_OBJECT

public:
    //���±�����ͬһʱ��ֻ����һ���ļ������԰�QFile������Ϊ��Ĺ��г�Ա����
	QFile file;  //�ļ�����

    //QComboBox��ѡ��������ؼ�

    MyNotebook(QWidget *parent = nullptr);
    ~MyNotebook();
    void enterEvent(QEnterEvent*) override;     //������봰���¼�
    void leaveEvent(QEvent*) override;          //����Ƴ������¼�
    void wheelEvent(QWheelEvent*) override;     //�����ֹ����¼�
    void closeEvent(QCloseEvent*) override;     //���ڹر��¼�
    void resizeEvent(QResizeEvent*) override;   //���ڴ�С�ı��¼�
/*
  �Զ����źź�����QT��ʹ�ùؼ���signals������ֻ��Ҫ��������Ҫʵ��
*/
signals:
    void mySignal(int);

/*
  1.ʹ��QObject::connect()�����ź���ۣ�����õķ�ʽ
  ����QObject::connect(sender,SIGNAL(signal()),receiver,SLOT(slot()));
*/
/*
  �Զ���ۺ������ۺ����������˽�г�Ա������ʹ�� private slots: ������
  ������������ͨ��Ա�����������з�������Ҳ���Խ��ܲ�����������������Ҫ���źź����Ĳ�������ƥ��
*/
private slots:
    void on_btnOpen_clicked();
    void on_btnSave_clickedMyself();
    //void on_btnClose_clickedMyself();
    void on_btnOpen_clickedMyself();
	void onCursorPositionChanged(); //QTextEdit�ı��༭��Ĳۺ���
	void oncurrentIndexChanged(int index); //QComboBoxѡ���Ĳۺ���
    void zoomIn();
    void zoomOut();
    void mySlot(int);

private:
    Ui::MyNotebookClass *ui;
};

