#ifndef __BANK_H__
#define __BANK_H__
#include <iostream>
#include <string>

using namespace std;

/*
  ���е��˻���һ���࣬��������˵ĸ�����Ϣ�Ͷ�ȣ�����private���ε�˽�б���������Ĵ��������һ�����󣬲���˽���޸��˻���Ϣ����Ҫ���еĲ������̣�
  Ҳ����public���εĹ��к���ȥ����private���ε�˽�б���
*/
class BankAccount
{
private:
	string name;    //�˻���
	string addr;	//�˻���ַ
	int age;	   //�˻�����
	double balance; //�˻����
public:
	void registerAccount(string newName, string newAddr, int age, double balance); //ע���˻�
	void withdraw(double amount);	//ȡ��
	void deposit(double amount);	//���
	double getBalance();	//��ȡ���
	void printAccountInfo();
};

#endif // !__BANK_H__