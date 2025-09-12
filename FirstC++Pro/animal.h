#ifndef __ANIMAL_H__
#define __ANIMAL_H__
#include <iostream>
#include <string>

using namespace std;

/*
  如何实现多态
  1.使用虚函数：在基类中使用virtual关键字定义虚函数，在派生类中重写该函数
  2.创建派生类并重写虚函数
  3.通过基类的指针或引用调用虚函数
*/
/*
  纯虚函数：具有virtual fun()=0声明形式的函数；派生类必须实现基类的所有纯虚函数
  含有纯虚函数的类被称作抽象类abstract class；
  抽象类不能被实例化；包含至少一个纯虚函数；用于提供基础结构，确保所有的派生类具有一致的接口和行为
*/
/*
  C++没有像其它语言可以直接定义接口的关键字（例：Java的interface），但可以通过抽象类和纯虚函数的方式来实现
  接口通常用于定义类该实现的方法，但不提供具体实现。允许多个类共享相同的接口，同时让每个类去实现这些接口
  作为接口的类实现如下：
  1.定义抽象类：创建一个包含纯虚函数的抽象类，构成了接口的一部分（只有声明而无具体定义实现）
  2.派生类实现接口：派生类继承抽象类，并实现其中的纯虚函数，以具体实现接口定义的方法
*/

class Animal
{
public:
	string name;	//动物名称
	int age;		//动物年龄
	Animal();
	//构造函数
	Animal(string,int);
	//如果类中有虚函数，建议析构函数也声明为虚函数，以确保通过基类指针删除派生类对象时，能够正确调用派生类的析构函数，避免资源泄漏
	~Animal();
	//基类的虚函数：C++的成员函数默认不是虚函数，只有显式使用virtual关键字声明的成员函数才是虚函数
	//一旦在基类中声明虚函数，该函数在所有派生类中自动成为虚函数
	virtual void makeSound();

	//抽象类的纯虚函数
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
	//Lion类重写基类的虚函数；派生类中使用override关键字修饰的重写函数，在基类中必须要有相同的虚函数对应
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
		// Lion类不能直接访问Animal类的private成员
		// 但可以通过Animal类的公有或保护成员函数访问
		accessPrivateData(); // 调用Animal类的公有成员函数来访问privateData
	}
};

class Rabbit : protected Animal
{
public:
	Rabbit();
	Rabbit(string name,int age);
	//Rabbit类重写基类的虚函数；派生类中使用override关键字修饰的重写函数，在基类中必须要有相同的虚函数对应
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
