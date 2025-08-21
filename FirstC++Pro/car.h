#ifndef __CAR_H__
#define __CAR_H__
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

//QT�о������������ϣ�Component������һ�ֳ��������ģʽ�����ڱ�ʾһ�������������ʵ����ɣ���ʾ��ӵ�С���ϵ
class Wheel
{
public:
	string brand;    //��̥Ʒ��
	string year;     //��̥���
	void wheelPrintInfo();
};

class Engine
{
public:
	string brand;    //����Ʒ��
	string year;     //�������
	void enginePrintInfo();
};

// ͨ��C���Խṹ������C++���ࣺC++�µ�������
class Car
{
public:
	string color;    //������ɫ
	string brand;    //����Ʒ��
	string type;     //��������
	int year;       //�������
	Wheel wheel;    //��̥����
	Engine* engine; //�������ָ�룬ʹ��ָ����Զ�̬�����ڴ棬���⿽������
	//��ʵҲ�ǳ�Ա���������������ĳ�Ա����
	void (*printCarInfo)(string color, string brand, string type, int year);     //����ָ�룬ָ�������ܺ���
	void (*carRun)(char* type);       //����ָ�룬ָ������ʻ����
	void (*carStop)(char* type);      //����ָ�룬ָ����ֹͣ����
	//������Ա��������Ա��������ֱ�ӷ�����ĳ�Ա����
	void realPrintCarInfo();
};

#endif