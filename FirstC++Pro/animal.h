#ifndef __ANIMAL_H__
#define __ANIMAL_H__
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
	string name;	//��������
	int age;		//��������
	//���캯��
	Animal(string,int);
	//����������麯����������������Ҳ����Ϊ�麯������ȷ��ͨ������ָ��ɾ�����������ʱ���ܹ���ȷ���������������������������Դй©
	~Animal();
	//������麯����C++�ĳ�Ա����Ĭ�ϲ����麯����ֻ����ʽʹ��virtual�ؼ��������ĳ�Ա���������麯��
	//һ���ڻ����������麯�����ú������������������Զ���Ϊ�麯��
	virtual void makeSound();
	void eatFood();
	void accessPrivateData() {
		cout << "Animal Accessing private data: " << privateData << endl;
	}
protected:
	int protectedData;	
private:
	int privateData;
};

class Lion : public Animal
{
public:
	int teeth;
	Lion(string,int,int);
	//Lion����д������麯������������ʹ��override�ؼ������ε���д�������ڻ����б���Ҫ����ͬ���麯����Ӧ
	void makeSound() override;
	void hunt();
	void accessProtectedData() {
		cout << "Lion Accessing Animal protected data: " << protectedData << endl;
	}
	void accessPublicData() {
		cout << "Lion Accessing Animal public data: " << name << ", " << age << endl;
	}
	void lionAccessPrivateData() {
		//cout << "Lion Accessing Animal private data: " << privateData << endl;
		cout << "Lion cannot access Animal private data directly." << endl;
		// Lion�಻��ֱ�ӷ���Animal���private��Ա
		// ������ͨ��Animal��Ĺ��л򱣻���Ա��������
		accessPrivateData(); // ����Animal��Ĺ��г�Ա����������privateData
	}
};

class Rabbit : protected Animal
{
public:
	Rabbit(string name,int age);
	void accessProtectedData() {
		cout << "Rabbit Accessing Animal protected data: " << protectedData << endl;
	}
	void accessPublicData() {
		cout << "Rabbit Accessing Animal public data: " << name << ", " << age << endl;
	}
private:

};

#endif // !__ANIMAL_H__
