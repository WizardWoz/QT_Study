#include "car.h"

void Wheel::wheelPrintInfo() {
	string str = "品牌是：" + brand + "，年份是：" + year;
	cout << "轮胎信息打印：" << str << endl;
}

void Engine::enginePrintInfo() {
	string str = "品牌是：" + brand + "，年份是：" + year;
	cout << "引擎信息打印：" << str << endl;
}

//::是作用域解析运算符，用于访问类的成员函数或变量
void Car::realPrintCarInfo() {
	string str = "车的品牌是：" + brand + "，型号是：" + type + "，颜色是：" + color + "，上市年份是：" + to_string(year);
	cout << "成员函数打印：" << str << endl;
	wheel.wheelPrintInfo(); //调用轮胎的成员函数
	if (engine != nullptr) {
		engine->enginePrintInfo(); //调用引擎的成员函数
	}
	else {
		cout << "引擎信息未设置。" << endl;
	}
}

void PrintCarInfo(string color, string brand, string type, int year)
{
	//printf("%s",指针)
	string str = "车的品牌是：" + brand + "，型号是：" + type + "，颜色是：" + color + "，上市年份是：" + to_string(year);
	cout << str << endl;
}

void carRun()
{
	printf("The car is running.\n");
}

void carStop()
{
	printf("The car has stopped.\n");
}