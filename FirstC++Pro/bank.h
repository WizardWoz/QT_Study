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
	int* data;
public:
	BankAccount();	//无参构造函数
	BankAccount(int size); //带参数的构造函数，允许指定数组大小
	//析构函数：在对象生命周期结束时，或者使用delete释放时自动调用，执行对象销毁前的清理工作
	//无返回值和参数，不可重载，每个类只能有一个；如果一个类为多态基类，则必须有虚析构函数
	~BankAccount();	//析构函数
	void registerAccount(string newName, string newAddr, int age, double balance); //注册账户
	void withdraw(double amount);	//取款
	void deposit(double amount);	//存款
	double getBalance();	//获取余额
	BankAccount& setAge(int); //设置年龄，返回引用以便链式调用
	void printAccountInfo();
};

#endif // !__BANK_H__