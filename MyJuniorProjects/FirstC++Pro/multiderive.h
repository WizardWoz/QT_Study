#pragma once
#include <iostream>

using namespace std;

// ��Base������������ǰ
class Base
{
public:
    //Base�����е�data��Ա������Derived���д���ClassA��ClassB�е����ݸ������������μ̳�����
    int data;
    Base(int);
};

/*
  ��̳�(virtual inheritance)�����ڽ�����μ̳����⣬ȷ����������ֻ��һ�ݻ���ĸ���
*/

class ClassA : virtual public Base
{
public:
    void displayA();
    //ClassA��ClassB�ж���testFunc()������������Derived�����ֱ�ӵ���testFunc()�ᱨ�����Դ���
    void testFunc();

    ClassA(int);
private:

};

class ClassB : virtual public Base
{
public:
    void displayB();
    //ClassA��ClassB�ж���testFunc()������������Derived�����ֱ�ӵ���testFunc()�ᱨ�����Դ���
    void testFunc();

    ClassB(int);
private:

};

/*
  ���μ̳����⣺�����������̳���ͬһ�����ߵĻ��࣬���ܵ����������д������ݻ��ั��������ͨ����̳������
  ���ؼ̳��ṩ�˺ܴ������ԣ�������ʹ�ûᵼ�¶����Ժ�ά�����ѣ�ĳЩ���Ӧʹ�������ϻ��ߴ�����
*/

class Derived : public ClassA, public ClassB
{
public:
    Derived(int);
    void display();
private:

};