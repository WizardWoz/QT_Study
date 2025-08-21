#include "bank.h"

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

void BankAccount::printAccountInfo() {
	string str = "账户名：" + name + "，账户地址：" + addr + "，账户年龄：" + to_string(age) + "，账户余额：" + to_string(balance);
	cout << str << endl;
}