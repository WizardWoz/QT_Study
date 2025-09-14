#include <iostream>
#include <string>
#include "mytemp.h"

/*
  ģ�����Ա������ʵ�֣�
  1.ģ��������г�Ա�������������캯��������ͷ�ļ���ʵ��
  2.��Ҫ��.cpp�ļ���ʵ��ģ����ĳ�Ա����������Ҫ�����ʵ�����ʽʵ����
*/
template class PrintData<int>; //��ʽʵ����PrintData��ģ�壬ָ��TΪint����
template class PrintData<double>; //��ʽʵ����PrintData��ģ�壬ָ��TΪdouble����
template class PrintData<std::string>; //��ʽʵ����PrintData��ģ�壬ָ��TΪstd::string����

//��Ϊ��ģ�岢����һ���������࣬�������Ա��������֮ǰ��Ҫ����template<typename T>
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