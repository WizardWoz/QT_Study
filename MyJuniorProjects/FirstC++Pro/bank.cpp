#include "bank.h"

BankAccount::BankAccount() {
	cout << "BankAccount无参构造函数中this指针的值为：" << this << endl;
	name = "未命名账户";
	addr = "未命名地址";
	age = 0;
	balance = 0.0;
	data = nullptr;
}

BankAccount::BankAccount(int size) {
	cout << "BankAccount有参构造函数中this指针的值为：" << this << endl;
	name = "未命名账户";
	addr = "未命名地址";
	age = 0;
	balance = 0.0;
	data = new int[size]; //动态分配内存
}

BankAccount::~BankAccount() {
	cout << "BankAccount析构函数中this指针的值为：" << this << endl;
	delete[] data; //释放动态分配的内存
}

void BankAccount::registerAccount(string newName, string newAddr, int newAge, double newBalance) {
	name = newName;
	addr = newAddr;
	age = newAge;
	balance = newBalance;
}

void BankAccount::withdraw(double amount) {
	if (amount > balance)
	{
		cerr << "取款不成功，取款金额大于账户余额" << endl;
	}
	else if (amount <= 0)
	{
		std::cerr << "取款不成功，取款金额必须为正数" << std::endl;
	}
	else
	{
		balance -= amount;
	}
}

void BankAccount::deposit(double amount) {
	if (amount > 0)
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

BankAccount& BankAccount::setAge(int newAge) {
	this->age = newAge; //使用this指针访问成员变量
	return *this; //返回当前对象的引用，以便链式调用
}

void BankAccount::printAccountInfo() {
	string str = "账户名：" + name + "，账户地址：" + addr + "，账户年龄：" + to_string(age) + "，账户余额：" + to_string(balance);
	cout << str << endl;
}