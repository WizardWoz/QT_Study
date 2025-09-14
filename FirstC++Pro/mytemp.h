#pragma once

/*
  C++模板：允许创建通用的类或函数，可以处理不同的数据类型；使得类、函数可以适用于不同的数据类型而不需要编写相同的代码
  主要有两种模板：类模板和函数模板
*/
/*
  模板类成员函数的实现：
  1.模板类的所有成员函数（包括构造函数）都在头文件中实现
  2.若要在.cpp文件中实现模板类的成员函数，则需要进行适当的显式实例化
*/
template <typename T>
class PrintData
{
public:
	PrintData();
	~PrintData();
	void printEveryThing();
	void setEveryThing(T);
private:
	T data; // 模板类型的成员变量
};

/*
  函数模板：允许编写通用的函数，可以处理不同的数据类型
*/
template <typename T>
T add(T x, T y)
{
	return x + y;
}