#include "animal.h"

Animal::Animal(string name,int age) {
	this->name = name;
	this->age = age;
	protectedData = 0; // 初始化protected成员
	privateData = 0;  // 初始化private成员
	cout << "基类Animal的构造函数被调用。" << endl;
}

Animal::~Animal()
{

}

void Animal::makeSound() {
	// 默认实现，子类可以重写
	cout << "Animal makes a sound." << endl;
}

void Animal::eatFood() {
	// 默认实现，子类可以重写
	cout << "Animal eats food." << endl;
}

/*
  派生类可以通过初始化列表来调用基类的构造函数；先调用基类，后调用派生类的构造函数
*/
Lion::Lion(string name,int age,int teeth) : Animal(name,age){
	this->teeth = teeth;
	cout << "派生类Lion的构造函数被调用。" << endl;
}

// Lion类重写基类的虚函数，只需要在函数声明加上override关键字，函数实现不需要加override
void Lion::makeSound() {
	// 重写基类的虚函数
	cout << "Lion roars." << endl;
}

void Lion::hunt()
{
	cout << "Lion hunts for prey." << endl;
}

Rabbit::Rabbit(string name,int age) : Animal(name,age) {
	cout << "派生类Rabbit的构造函数被调用。" << endl;
}
