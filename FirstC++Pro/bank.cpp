#include "bank.h"

BankAccount::BankAccount() {
	cout << "BankAccount�޲ι��캯����thisָ���ֵΪ��" << this << endl;
	name = "δ�����˻�";
	addr = "δ������ַ";
	age = 0;
	balance = 0.0;
	data = nullptr;
}

BankAccount::BankAccount(int size) {
	cout << "BankAccount�вι��캯����thisָ���ֵΪ��" << this << endl;
	name = "δ�����˻�";
	addr = "δ������ַ";
	age = 0;
	balance = 0.0;
	data = new int[size]; //��̬�����ڴ�
}

BankAccount::~BankAccount() {
	cout << "BankAccount����������thisָ���ֵΪ��" << this << endl;
	delete[] data; //�ͷŶ�̬������ڴ�
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

BankAccount& BankAccount::setAge(int newAge) {
	this->age = newAge; //ʹ��thisָ����ʳ�Ա����
	return *this; //���ص�ǰ��������ã��Ա���ʽ����
}

void BankAccount::printAccountInfo() {
	string str = "�˻�����" + name + "���˻���ַ��" + addr + "���˻����䣺" + to_string(age) + "���˻���" + to_string(balance);
	cout << str << endl;
}