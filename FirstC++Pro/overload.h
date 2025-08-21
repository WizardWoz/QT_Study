#ifndef __OVERLOAD_H__
#define __OVERLOAD_H__
#include <iostream>

using namespace std;

/*
  ���Ա����������
*/
class Data
{
public:
	void print(int i) {
		cout << "����Ϊ��" << i << endl;
	}
	void print(double d) {
		cout << "������Ϊ��" << d << endl;
	}
	void print(const char* str) {
		cout << "�ַ���Ϊ��" << str << endl;
	}

private:

};

/*
  �������==����
  �������֡�������ͬ����ͬһ����
*/
class Person
{
public:
	string name;
	int age;
	// ����==����������ڱȽ�����Person�����Ƿ���ȣ�ʵ����������Ƚ����֡������Ƿ����
	bool operator==(const Person& other) const {
		return (name == other.name && age == other.age);
	}
private:

};

/*
  �������+����
*/
class Point
{
public:
	int x, y;
	// ����+�����������ʵ������Point��������
	//const Point& other����������һ�� Point ����ĳ������ã����ⲻ��Ҫ�Ŀ�����const����ʾ�ó�Ա���������޸ĵ�ǰ��������ݳ�Ա��
	Point operator+(const Point& other) const;
private:

};

#endif // !__OVERLOAD_H__
