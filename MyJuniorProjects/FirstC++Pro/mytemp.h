#pragma once

/*
  C++ģ�壺������ͨ�õ�����������Դ���ͬ���������ͣ�ʹ���ࡢ�������������ڲ�ͬ���������Ͷ�����Ҫ��д��ͬ�Ĵ���
  ��Ҫ������ģ�壺��ģ��ͺ���ģ��
*/
/*
  ģ�����Ա������ʵ�֣�
  1.ģ��������г�Ա�������������캯��������ͷ�ļ���ʵ��
  2.��Ҫ��.cpp�ļ���ʵ��ģ����ĳ�Ա����������Ҫ�����ʵ�����ʽʵ����
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
	T data; // ģ�����͵ĳ�Ա����
};

/*
  ����ģ�壺�����дͨ�õĺ��������Դ���ͬ����������
*/
template <typename T>
T add(T x, T y)
{
	return x + y;
}