#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "car.h"
#include "bank.h"
#include "overload.h"
#include "animal.h"
#include "multiderive.h"
#include "cir.h"

using namespace std;

static bool compare(int a, int b) {
	return a > b;
}

/*
  回调函数:通过函数指针调用的函数。将函数的指针（地址）作为参数传递给另一个函数，当这个指针被用来调用其所指向的函数时，我们就称之为回调函数。
  回调函数通常用于实现事件处理响应、异步编程或将函数作为参数传递给其他函数。
*/
int getMax(int a, int b, bool (*cmp)(int, int)) {
	if (cmp(a, b)) {
		return a;
	} else {
		return b;
	}
}

double vals[] = { 10.1,12.6,33.1,24.1,50.0 };

//当函数返回值为一个引用时，函数可以作为表达式左值
double& setvalues(int i) {
	double& ref = vals[i];
	return ref; //返回数组中第i个元素的引用
	//要注意不能引用函数内部的局部变量，因为局部变量的栈空间在函数结束后会自动销毁
	//如果需要返回一个引用，必须确保引用的对象在函数调用结束后仍然存在；例如：全局变量，static变量，或动态分配的内存
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
	double myRadius = 5.0;
	int a,b;
	bool btype=false;	//C99标准以上支持
	//标准输出流输出
	cout << "Hello, World!" << endl;
	cout << "你好，世界！" << "我是补充输出的。" << endl;
	//使用命名空间cir中的函数
	printf("Circle radius: %.2f\n", myRadius);
	printf("Circle length: %.2f\n", cir::getLengthOfCircle(myRadius));
	printf("Circle area: %.2f\n", cir::getAreaOfCircle(myRadius));
	//使用自定义的变量a，b
	cin >> a >> b;
	cout << "You entered: " << a << " and " << b << endl;
	cout << a << " + " << b << " = " << a + b << endl;
	//标准错误流输出
	cerr << "This is an error message." << endl;
	//打印int，unsigned int，long long的取值范围
	std::cout << "The range of int is from " << INT_MIN << " to " << INT_MAX << std::endl;
	std::cout << "The range of unsigned int is from " << 0 << " to " << UINT_MAX << std::endl;
	std::cout << "The range of long long is from " << LLONG_MIN << " to " << LLONG_MAX << std::endl;

	//Lamda表达式：C++11引入的特性，可以作为匿名函数，允许在需要函数的位置内联定义函数，而无需单独定义
	//[capture clause](parameter)->returnType {
	//	//函数体，可使用捕获列表中的变量
	// return expression;	//可选的返回语句
	//}
	//1.捕获列表(capture clause)：用于捕获外部变量，在Lambda表达式中使用。可以按值捕获或按引用捕获。捕获列表可以为空，也可以包含多个变量[var1,var2,var3,...]
	//2.参数列表(parameter)：指定Lambda表达式的参数，可以为空或包含多个参数(param1,param2,param3,...)。参数列表与普通函数类似，可以指定参数类型。
	//3.返回类型(returnType)：指定Lambda表达式的返回类型，可以省略，编译器会根据函数体自动推断返回类型(auto)。如果需要显式指定返回类型，可以使用->符号。
	//4.函数体：Lambda表达式的主体部分，包含实际的代码逻辑。可以包含多条语句，也可以是单个表达式。
	//使用Lambda表达式参数列表
	auto add = [](int x, int y) -> int {
		return x + y;
		};
	cout << "Using Lambda expression to add: " << add(10, 4) << endl;
	//使用Lambda表达式捕获列表
	int x = 5, y = 10;
	int* px = &x;
	int* py = &y;
	auto add_capture1 = [&px, &py]() -> int {	//按指针捕获外部变量
		//x++; //捕获的变量可以在Lambda表达式中使用，但不能修改
		*px += 1; //如果需要修改捕获的变量，可以使用引用或指针捕获
		return *px + *py;
		};
	cout << "Using Lambda expression with captured variables（指针捕获）: " << add_capture1() << endl;
	auto add_capture2 = [&]() -> int {	//按引用捕获所有外部变量
		//x++; //捕获的变量可以在Lambda表达式中使用，但不能修改
		x += 1; //如果需要修改捕获的变量，可以使用引用或指针捕获
		return x + y;
		};
	cout << "Using Lambda expression with captured variables（按引用捕获所有变量）: " << add_capture2() << endl;
	auto add_capture3 = [=]() -> int {	//按值捕获所有外部变量
		//x++; //捕获的变量可以在Lambda表达式中使用，但不能修改
		//x += 1; //如果需要修改捕获的变量，可以使用引用或指针捕获
		return x + y;
		};
	cout << "Using Lambda expression with captured variables（按值捕获所有变量）: " << add_capture3() << endl;

	bool (*p)(int a, int b) = compare; //函数指针指向compare函数
	//使用回调函数获取最大值
	int maxVal = getMax(x, y, p);
	//回调函数中使用Lambda表达式作为匿名函数指针
	int maxValLambda = getMax(x, y, [](int a, int b) { 
		return a > b;
	});
	cout << maxVal << " is the maximum value between " << x << " and " << y << endl;
	cout << maxValLambda << " is the maximum value between " << x << " and " << y << " (using lambda)" << endl;

	// 直接建立struct Car的实例（没问题）
	/*struct Car BMWThreeSeries;
	BMWThreeSeries.color = "Black";
	BMWThreeSeries.brand = "BMW";
	BMWThreeSeries.type = "Sedan";
	BMWThreeSeries.year = 2023;
	BMWThreeSeries.printCarInfo = PrintCarInfo;
	BMWThreeSeries.printCarInfo(BMWThreeSeries.color, BMWThreeSeries.brand, BMWThreeSeries.type, BMWThreeSeries.year);*/
	// 通过malloc动态分配内存建立struct Car的实例（出现问题），所以转换成C++面向对象的类
	Car* AudiA6 = new Car();	//new动态分配内存给Car车辆实例，调用无参构造函数
	AudiA6->color = "White";
	AudiA6->brand = "Audi";
	AudiA6->type = "Sedan";
	AudiA6->wheel.brand = "Michelin"; //设置轮胎品牌
	AudiA6->wheel.year = "2022"; //设置轮胎年份
	AudiA6->engine = new Engine; //new动态分配内存给引擎
	AudiA6->engine->brand = "Audi Engine"; //设置引擎品牌
	AudiA6->engine->year = "2022"; //设置引擎年份
	AudiA6->year = 2022;
	//直接创建一个Car类的实例，调用带参数构造函数
	Car BenzCClass("Benz",2025);
	Car& BMWFiveSeries = *new Car("BMW", 2024); //创建一个BMW五系的实例，使用引用
	Car* TeslaModelS = new Car("Tesla"); //创建一个Tesla Model S的实例，使用指针
	delete TeslaModelS; //释放Tesla Model S的内存
	//面向过程版本
	//AudiA6->printCarInfo = PrintCarInfo;
	//AudiA6->printCarInfo(AudiA6->color, AudiA6->brand, AudiA6->type, AudiA6->year);
	//面向对象版本
	AudiA6->realPrintCarInfo();
	delete AudiA6;

	//new分配单个对象
	Car* car1 = new Car();
	//new分配数组对象
	int* arr = new int[5] {1, 2, 3, 4, 5};
	delete[] arr; //释放数组内存
	delete car1; //释放单个对象内存

	BankAccount account1;
	cout << "main函数中BankAccount account1对象的地址：" << &account1 << endl;
	account1.registerAccount("Alice", "123 Main St", 30, 1000.0);
	account1.printAccountInfo();
	account1.deposit(500.0);
	account1.printAccountInfo();
	account1.withdraw(200.0);
	account1.printAccountInfo();
	cout << "单独获取账户余额：" << account1.getBalance() << endl;
	//实现链式调用
	account1.setAge(32).printAccountInfo(); //设置年龄为32，并打印账户信息
	BankAccount account2; //创建另一个BankAccount对象
	cout << "main函数中BankAccount account2对象的地址：" << &account2 << endl;
	//有参构造函数
	BankAccount* account3 = new BankAccount(10);
	delete account3;
	//当main()函数执行完毕，account1、account2的生命周期结束（即对象的作用域结束），自动调用析构函数

	//引用作为返回值
	cout << "改变前的值：";
	for (int i = 0; i < 5; i++)
	{
		cout << vals[i] << " ";
	}
	cout << endl;
	setvalues(0) = 20.0; //通过引用修改数组中的第一个元素
	setvalues(2) = 25.3; //通过引用修改数组中的第三个元素
	cout << "改变后的值：";
	for (int i = 0; i < 5; i++)
	{
		cout << vals[i] << " ";
	}
	cout << endl;

	cout << "创建Data类的data实例前的numOfInstances值：" << Data::numOfInstances << endl;
	Data* data=new Data;
	cout << "创建Data类的data实例后的numOfInstances值：" << Data::numOfInstances << endl;
	// 调用重载的print函数
	data->print(42);		   // 调用print(int)
	data->print(3.14);         // 调用print(double)
	data->print("Hello");      // 调用print(const char*)
	Data::staticval = 100; // 设置静态成员变量的值
	delete data; // 删除Data类的实例，调用析构函数
	cout << "删除Data类的data实例后的numOfInstances值：" << Data::numOfInstances << endl;
	// 调用静态成员变量
	cout << "Data类的静态成员变量staticval：" << Data::staticval << endl;
	// 调用静态成员函数
	cout << "Data类的静态成员函数getStaticVal()返回值：" << Data::getStaticVal() << endl;
	Data data1;
	Data data2;
	cout << "在全局作用域内创建的data1对象，numOfInstances值：" << Data::numOfInstances << endl;
	{
		Data data3; // 局部变量，作用域结束后会自动调用析构函数
		cout << "在局部作用域内创建的data3对象，numOfInstances值：" << Data::numOfInstances << endl;
	}
	cout << "在全局作用域内创建的data2对象，numOfInstances值：" << Data::numOfInstances << endl;

	Person person1, person2;
	person1.name = "Alice";
	person1.age = 30;
	person2.name = "Alice";
	person2.age = 30;
	// 重载==运算符比较Person对象
	// 注意：需要在Person类中定义operator==函数来实现自定义的比较逻辑;这里假设已经定义了operator==函数，比较name和age是否相等
	// 如果没有定义，则默认按地址比较
	bool ret = person1 == person2;
	cout << "Are person1 and person2 equal? " << (ret ? "Yes" : "No") << endl;

	Point point1, point2, point3;
	point1.x = 10;
	point1.y = 20;
	point2.x = 10;
	point2.y = 20;
	//重载运算符 + 实现两个Point对象的相加
	point3 = point1 + point2;
	cout << "point1 + point2 = (" << point3.x << ", " << point3.y << ")" << endl;

	Roadster myRoadster;
	//myRoadster.color = "Red";	//父类的私有成员不能被子类访问
	myRoadster.brand = "Tesla";	//设置成public公有继承后，子类可以访问父类的公有成员
	myRoadster.openTopped();
	myRoadster.pDrifting();

	Lion lion("Simba", 5, 30);
	lion.makeSound();
	lion.eatFood();
	lion.hunt();
	lion.accessProtectedData(); // 访问Animal类的protected成员
	lion.accessPublicData(); // 访问Animal类的public成员
	lion.accessPrivateData(); // 访问Animal类的private成员，通过Animal类的公有成员函数访问
	Rabbit rabbit("Bunny", 3);
	rabbit.makeSound();
	rabbit.accessProtectedData(); // 访问Animal类的protected成员
	rabbit.accessPublicData(); // 访问Animal类的public成员
	Animal* animalPtr1=new Lion("Simba", 5, 30); //基类指针
	animalPtr1->makeSound(); // 调用派生类的重写函数
	animalPtr1->jump();	// 调用派生类的重写函数
	//基类指针只能指向公有继承的派生类对象，不能指向保护继承或私有继承的派生类对象
	//Animal* animalPtr2 = new Rabbit("Bunny", 3); //报错：“类型强制转换”: 从“Rabbit *”到“Animal *”的转换存在，但无法访问
	//animalPtr2->makeSound(); // 调用派生类的重写函数
	delete animalPtr1; //释放内存，调用派生类的析构函数
	//delete animalPtr2; //释放内存，调用派生类的析构函数
	Animal& animalRef = *new Lion; //基类引用
	animalRef.makeSound(); // 调用派生类的重写函数
	animalRef.jump();

	Derived obj(0);
	obj.displayA();
	obj.displayB();
	obj.display();
    return 0;
}