#pragma once
#include <iostream>

using namespace std;

// 将Base类完整定义提前
class Base
{
public:
    //Base基类中的data成员变量在Derived类中存在ClassA和ClassB中的两份副本，导致菱形继承问题
    int data;
    Base(int);
};

/*
  虚继承(virtual inheritance)：用于解决菱形继承问题，确保派生类中只有一份基类的副本
*/

class ClassA : virtual public Base
{
public:
    void displayA();
    //ClassA和ClassB中都有testFunc()函数，派生类Derived中如果直接调用testFunc()会报二义性错误
    void testFunc();

    ClassA(int);
private:

};

class ClassB : virtual public Base
{
public:
    void displayB();
    //ClassA和ClassB中都有testFunc()函数，派生类Derived中如果直接调用testFunc()会报二义性错误
    void testFunc();

    ClassB(int);
private:

};

/*
  菱形继承问题：如果两个基类继承自同一个更高的基类，可能导致派生类中存在两份基类副本，可以通过虚继承来解决
  多重继承提供了很大的灵活性，但过度使用会导致二义性和维护困难；某些情况应使用类的组合或者纯虚类
*/

class Derived : public ClassA, public ClassB
{
public:
    Derived(int);
    void display();
private:

};