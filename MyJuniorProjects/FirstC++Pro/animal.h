#ifndef __ANIMAL_H__
#define __ANIMAL_H__
#include <iostream>
#include <string>

using namespace std;

/*
  ���ʵ�ֶ�̬
  1.ʹ���麯�����ڻ�����ʹ��virtual�ؼ��ֶ����麯����������������д�ú���
  2.���������ಢ��д�麯��
  3.ͨ�������ָ������õ����麯��
*/
/*
  ���麯��������virtual fun()=0������ʽ�ĺ��������������ʵ�ֻ�������д��麯��
  ���д��麯�����౻����������abstract class��
  �����಻�ܱ�ʵ��������������һ�����麯���������ṩ�����ṹ��ȷ�����е����������һ�µĽӿں���Ϊ
*/
/*
  C++û�����������Կ���ֱ�Ӷ���ӿڵĹؼ��֣�����Java��interface����������ͨ��������ʹ��麯���ķ�ʽ��ʵ��
  �ӿ�ͨ�����ڶ������ʵ�ֵķ����������ṩ����ʵ�֡��������๲����ͬ�Ľӿڣ�ͬʱ��ÿ����ȥʵ����Щ�ӿ�
  ��Ϊ�ӿڵ���ʵ�����£�
  1.��������ࣺ����һ���������麯���ĳ����࣬�����˽ӿڵ�һ���֣�ֻ���������޾��嶨��ʵ�֣�
  2.������ʵ�ֽӿڣ�������̳г����࣬��ʵ�����еĴ��麯�����Ծ���ʵ�ֽӿڶ���ķ���
*/

class Animal
{
public:
	string name;	//��������
	int age;		//��������
	Animal();
	//���캯��
	Animal(string,int);
	//����������麯����������������Ҳ����Ϊ�麯������ȷ��ͨ������ָ��ɾ�����������ʱ���ܹ���ȷ���������������������������Դй©
	~Animal();
	//������麯����C++�ĳ�Ա����Ĭ�ϲ����麯����ֻ����ʽʹ��virtual�ؼ��������ĳ�Ա���������麯��
	//һ���ڻ����������麯�����ú������������������Զ���Ϊ�麯��
	virtual void makeSound();

	//������Ĵ��麯��
	virtual void jump() = 0;
	virtual void run() = 0;

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
	Lion();
	Lion(string,int,int);
	//Lion����д������麯������������ʹ��override�ؼ������ε���д�������ڻ����б���Ҫ����ͬ���麯����Ӧ
	void makeSound() override;

	void jump() override;
	void run() override;
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
	Rabbit();
	Rabbit(string name,int age);
	//Rabbit����д������麯������������ʹ��override�ؼ������ε���д�������ڻ����б���Ҫ����ͬ���麯����Ӧ
	void makeSound() override;

	void jump() override;
	void run() override;
	void accessProtectedData() {
		cout << "Rabbit Accessing Animal protected data: " << protectedData << endl;
	}
	void accessPublicData() {
		cout << "Rabbit Accessing Animal public data: " << name << ", " << age << endl;
	}
private:

};

#endif // !__ANIMAL_H__
