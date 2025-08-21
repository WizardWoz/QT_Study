#ifndef __BANK_H__
#define __BANK_H__
#include <iostream>
#include <string>

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
	void registerAccount(string newName, string newAddr, int age, double balance); //注册账户
	void withdraw(double amount);	//取款
	void deposit(double amount);	//存款
	double getBalance();	//获取余额
	void printAccountInfo();
};

#endif // !__BANK_H__