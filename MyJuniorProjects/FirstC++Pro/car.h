#ifndef __CAR_H__
#define __CAR_H__
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

//QT中经常采用类的组合（Component）；是一种常见的设计模式，用于表示一个类由其他类的实例组成，表示“拥有”关系

class Wheel
{
public:
	string brand;    //轮胎品牌
	string year;     //轮胎年份
	void wheelPrintInfo();
};

class Engine
{
public:
	string brand;    //引擎品牌
	string year;     //引擎年份
	void enginePrintInfo();
};

// 通过C语言结构体引入C++的类：C++下的汽车类
// 车辆类，包含轮胎和引擎对象
class Car
{
public:
	string color;    //车辆颜色
	string brand;    //车辆品牌
	string type;     //车辆类型
	int year;       //车辆年份
	Wheel wheel;    //轮胎对象
	Engine* engine; //引擎对象指针，使用指针可以动态分配内存，避免拷贝开销

	//构造函数
	Car(); //构造函数声明，初始化成员变量和函数指针
	Car(string); //构造函数重载，允许直接设置品牌
	Car(string brand, int year); //构造函数重载，允许直接设置品牌和年份
	//其实也是成员变量，并非真正的成员函数
	void (*printCarInfo)(string color, string brand, string type, int year);     //函数指针，指向车辆介绍函数
	void (*carRun)(char* type);       //函数指针，指向车辆行驶函数
	void (*carStop)(char* type);      //函数指针，指向车辆停止函数
	//声明成员函数；成员函数可以直接访问类的成员变量
	void realPrintCarInfo();
};

/*
  C++的继承：默认是私有继承private
  基类成员类型			public继承			protected继承			private继承
  public				public				protected				private
  protected				protected			protected				private
  private				不可访问				不可访问					不可访问
  一句话总结：选最小的权限
*/

class Roadster : public Car
{
public:
	void openTopped();  //函数指针，指向敞篷车开顶函数
	void pDrifting();  //函数指针，指向敞篷车漂移函数
private:
	bool stateOfTop;	// 敞篷车顶状态，true表示开顶，false表示闭顶
};


#endif