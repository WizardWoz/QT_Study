#include "car.h"

void Wheel::wheelPrintInfo() {
	string str = "品牌是：" + brand + "，年份是：" + year;
	cout << "轮胎信息打印：" << str << endl;
}

void Engine::enginePrintInfo() {
	string str = "品牌是：" + brand + "，年份是：" + year;
	cout << "引擎信息打印：" << str << endl;
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

/*
  Car汽车类的无参构造函数
  使用了成员变量初始化列表: engine(nullptr)，初始化成员变量和函数指针；
  直接在对象的构造过程中被复制，而不是先创建成员变量后赋值，提高了性能
*/
Car::Car() {
	cout << "Car类的无参数构造函数被调用。" << endl;
	//构造函数初始化成员变量
	color = "Unknown";
	brand = "Unknown";
	type = "Unknown";
	year = 0;
	engine = nullptr; //引擎指针初始化为nullptr，表示未设置引擎
	printCarInfo = PrintCarInfo; //初始化函数指针
	carRun = carRun; //初始化车辆行驶函数指针
	carStop = carStop; //初始化车辆停止函数指针
}

/*
  Car汽车类的有参构造函数
  使用了成员变量初始化列表: brand(brand), year(year), engine(nullptr)，初始化成员变量和函数指针；
*/
Car::Car(string brand, int year) : brand(brand), year(year), engine(nullptr) {
	cout << "Car类的带参数构造函数被调用。" << endl;
	//构造函数初始化成员变量
	color = "Unknown";
	type = "Unknown";
	printCarInfo = PrintCarInfo; //初始化函数指针
	carRun = carRun; //初始化车辆行驶函数指针
	carStop = carStop; //初始化车辆停止函数指针
}

//实际和成员变量初始化列表: brand(brand), year(year), engine(nullptr)效果一样，
// 所以编译阶段报错：C2084 函数“Car::Car(std::string,int)”已有主体
//Car::Car(string brand, int year) : engine(nullptr) {
//	cout << "Car类的带参数构造函数被调用。" << endl;
//	//构造函数初始化成员变量
//	color = "Unknown";
// C++的this指针指向当前对象实例，可以用来访问类的成员变量和成员函数
//	this->brand = brand; //使用this指针访问成员变量
//	type = "Unknown";
//	this->year = year;
//	printCarInfo = PrintCarInfo; //初始化函数指针
//	carRun = carRun; //初始化车辆行驶函数指针
//	carStop = carStop; //初始化车辆停止函数指针
//}

Car::Car(string brand) : engine(nullptr) {
	cout << "Car类的带参数构造函数被调用。" << endl;
	//构造函数初始化成员变量
	color = "Unknown";
	//C++的this指针指向当前对象实例，可以用来访问类的成员变量和成员函数
	this->brand = brand; //使用this指针访问成员变量
	type = "Unknown";
	year = 0;
	printCarInfo = PrintCarInfo; //初始化函数指针
	carRun = carRun; //初始化车辆行驶函数指针
	carStop = carStop; //初始化车辆停止函数指针
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

void Roadster::openTopped() {
	cout << "敞篷车开顶功能被调用。" << endl;
}

void Roadster::pDrifting() {
	cout << "敞篷车漂移功能被调用。" << endl;
}