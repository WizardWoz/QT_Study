#ifndef __OVERLOAD_H__
#define __OVERLOAD_H__
#include <iostream>

using namespace std;

/*
  类成员函数的重载
*/
class Data
{
public:
	//静态成员变量是类的所有实例共享的变量，属于类本身而不是某个特定对象；无论创建了多少个实例，静态成员只有一份拷贝
	//需要在类外初始化，通常在类的.cpp实现文件中；可通过类名直接访问，也可通过实例对象访问
	static int staticval;
	static int numOfInstances; // 统计实例数量
	int data;
	Data();
	~Data();
	void print(int i) {
		cout << "整数为：" << i << endl;
	}
	void print(double d) {
		cout << "浮点数为：" << d << endl;
	}
	void print(const char* str) {
		cout << "字符串为：" << str << endl;
	}
	//静态成员函数只能访问静态成员变量和静态成员函数，不能访问非静态成员变量和非静态成员函数
	//静态成员函数不能被重载，因为它们没有this指针，无法区分不同的实例
	//可通过类名直接访问，也可通过实例对象访问
	static int getStaticVal();
private:

};

/*
  类运算符==重载
  假设名字、年龄相同的是同一个人
*/
class Person
{
public:
	string name;
	int age;
	// 重载==运算符，用于比较两个Person对象是否相等；实际上是逐个比较名字、年龄是否相等
	bool operator==(const Person& other) const {
		return (name == other.name && age == other.age);
	}
private:

};

/*
  类运算符+重载
*/
class Point
{
public:
	int x, y;
	// 重载+运算符，用于实现两个Point对象的相加
	//const Point& other：参数是另一个 Point 对象的常量引用，避免不必要的拷贝。const：表示该成员函数不会修改当前对象的数据成员。
	Point operator+(const Point& other) const;
private:

};

#endif // !__OVERLOAD_H__
