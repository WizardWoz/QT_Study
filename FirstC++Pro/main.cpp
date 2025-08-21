#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "car.h"
#include "cir.h"

using namespace std;

/*
  银行的账户是一个类，包含存款人的个人信息和额度，视作private修饰的私有变量；具体的存款人视作一个对象，不能私自修改账户信息，需要公有的操作流程，
  也就是public修饰的公有函数去操作private修饰的私有变量
*/
class BankAccount
{
private:
	string name;    //账户名
	string addr;	//账户地址
	int age;	   //账户年龄
	double balance; //账户余额
public:
	void registerAccount(string newName,string newAddr,int age,double balance); //注册账户
	void withdraw(double amount);	//取款
	void deposit(double amount);	//存款
	double getBalance();	//获取余额
	void printAccountInfo();
};

void BankAccount::registerAccount(string newName, string newAddr, int newAge, double newBalance) {
	name = newName;
	addr = newAddr;
	age = newAge;
	balance = newBalance;
}

void BankAccount::withdraw(double amount) {
	if (amount>balance)
	{
		cerr << "取款不成功，取款金额大于账户余额" << endl;
	}
	else if (amount<=0)
	{
		std::cerr << "取款不成功，取款金额必须为正数" << std::endl;
	}
	else
	{
		balance -= amount;
	}
}

void BankAccount::deposit(double amount) {
	if (amount>0)
	{
		balance += amount;
	}
	else
	{
		cerr << "存款不成功，存款金额必须为正数" << endl;
	}
}

double BankAccount::getBalance() {
	return balance;
}

void BankAccount::printAccountInfo() {
	string str = "账户名：" + name + "，账户地址：" + addr + "，账户年龄：" + to_string(age) + "，账户余额：" + to_string(balance);
	cout << str << endl;
}

bool compare(int a, int b) {
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
	Car* AudiA6 = new Car();	//new动态分配内存给Car车辆实例
	AudiA6->color = "White";
	AudiA6->brand = "Audi";
	AudiA6->type = "Sedan";
	AudiA6->wheel.brand = "Michelin"; //设置轮胎品牌
	AudiA6->wheel.year = "2022"; //设置轮胎年份
	AudiA6->engine = new Engine; //new动态分配内存给引擎
	AudiA6->engine->brand = "Audi Engine"; //设置引擎品牌
	AudiA6->engine->year = "2022"; //设置引擎年份
	AudiA6->year = 2022;
	//面向过程版本
	//AudiA6->printCarInfo = PrintCarInfo;
	//AudiA6->printCarInfo(AudiA6->color, AudiA6->brand, AudiA6->type, AudiA6->year);
	//面向对象版本
	AudiA6->realPrintCarInfo();
	delete AudiA6;

	BankAccount account;
	account.registerAccount("Alice", "123 Main St", 30, 1000.0);
	account.printAccountInfo();
	account.deposit(500.0);
	account.printAccountInfo();
	account.withdraw(200.0);
	account.printAccountInfo();
	cout << "单独获取账户余额：" << account.getBalance() << endl;
    return 0;
}