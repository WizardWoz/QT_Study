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
		cerr << "ȡ��ɹ���ȡ��������˻����" << endl;
	}
	else if (amount <= 0)
	{
		std::cerr << "ȡ��ɹ���ȡ�������Ϊ����" << std::endl;
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
		cerr << "���ɹ�����������Ϊ����" << endl;
	}
}

double BankAccount::getBalance() {
	return balance;
}

void BankAccount::printAccountInfo() {
	string str = "�˻�����" + name + "���˻���ַ��" + addr + "���˻����䣺" + to_string(age) + "���˻���" + to_string(balance);
	cout << str << endl;
}