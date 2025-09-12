#pragma once
#include <iostream>
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

#include <QtWidgets/QWidget>
#include "ui_mynotebook.h"

class MyNotebook : public QWidget   //MyNotebook�̳���QWidget
{
    //Q_OBJECT����QT�����һ���ǳ���Ҫ�ĺ꣬��������QT�����Ԫ����ϵͳ��������QT�ж���һ����ʱ����������̳���QObject�������࣬������ʹ��QT���ź���ۻ��ơ�
    //���ʻ�������ϵͳ������QTԪ����ϵͳ�ṩ�Ĺ��ܣ��ͱ������ඨ���а���Q_OBJECT�ꣻ�ú�����QT��Ԫ�����������moc��ʶ�𲢴�����ಢ���ɶ������
    //����˵��Q_OBJECT��ΪQT���ṩ�˶����Ԫ���ݣ�ʹ�����ܹ���ȫ����QT��ܵĹ���
    Q_OBJECT

public:
    MyNotebook(QWidget *parent = nullptr);
    ~MyNotebook();

/*
  �ۺ����������˽�г�Ա������ʹ�� private slots: ������
*/
private slots:
    void on_btnOpen_clicked();
    void on_btnClose_clickedMyself();

private:
    Ui::MyNotebookClass *ui;
};

