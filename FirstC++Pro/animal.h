#ifndef __ANIMAL_H__
#define __ANIMAL_H__
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
	string name;	//动物名称
	int age;		//动物年龄
	//构造函数
	Animal(string,int);
	//如果类中有虚函数，建议析构函数也声明为虚函数，以确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数，避免资源泄漏
	~Animal();
	//基类的虚函数：C++的成员函数默认不是虚函数，只有显式使用virtual关键字声明的成员函数才是虚函数
	//一旦在基类中声明虚函数，该函数在所有派生类中自动成为虚函数
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
	//Lion类重写基类的虚函数；派生类中使用override关键字修饰的重写函数，在基类中必须要有相同的虚函数对应
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
		// Lion类不能直接访问Animal类的private成员
		// 但可以通过Animal类的公有或保护成员函数访问
		accessPrivateData(); // 调用Animal类的公有成员函数来访问privateData
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
