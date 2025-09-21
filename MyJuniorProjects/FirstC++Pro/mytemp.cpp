#include <iostream>
#include <string>
#include "mytemp.h"

/*
  模板类成员函数的实现：
  1.模板类的所有成员函数（包括构造函数）都在头文件中实现
  2.若要在.cpp文件中实现模板类的成员函数，则需要进行适当的显式实例化
*/
template class PrintData<int>; //显式实例化PrintData类模板，指定T为int类型
template class PrintData<double>; //显式实例化PrintData类模板，指定T为double类型
template class PrintData<std::string>; //显式实例化PrintData类模板，指定T为std::string类型

//因为类模板并不是一个真正的类，所以类成员函数定义之前需要加上template<typename T>
template <typename T>
PrintData<T>::PrintData()
{

}

template<typename T>
PrintData<T>::~PrintData()
{

}

template<typename T>
void PrintData<T>::printEveryThing()
{
	std::cout << "The data is: " << data << std::endl;
}

template<typename T>
void PrintData<T>::setEveryThing(T data)
{
	this->data = data;
}