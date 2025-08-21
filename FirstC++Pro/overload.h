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
	void print(int i) {
		cout << "整数为：" << i << endl;
	}
	void print(double d) {
		cout << "浮点数为：" << d << endl;
	}
	void print(const char* str) {
		cout << "字符串为：" << str << endl;
	}

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
