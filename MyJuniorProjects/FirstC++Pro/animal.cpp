#include "animal.h"

Animal::Animal()
{
	cout << "����Animal��Ĭ�Ϲ��캯�������á�" << endl;
}

Animal::Animal(string name,int age) {
	this->name = name;
	this->age = age;
	protectedData = 0; // ��ʼ��protected��Ա
	privateData = 0;  // ��ʼ��private��Ա
	cout << "����Animal�Ĺ��캯�������á�" << endl;
}

Animal::~Animal()
{

}

void Animal::makeSound() {
	// Ĭ��ʵ�֣����������д
	cout << "Animal makes a sound." << endl;
}

void Animal::eatFood() {
	// Ĭ��ʵ�֣����������д
	cout << "Animal eats food." << endl;
}

Lion::Lion()
{
	cout << "������Lion��Ĭ�Ϲ��캯�������á�" << endl;
}

/*
  ���������ͨ����ʼ���б������û���Ĺ��캯�����ȵ��û��࣬�����������Ĺ��캯��
*/
Lion::Lion(string name,int age,int teeth) : Animal(name,age){
	this->teeth = teeth;
	cout << "������Lion�Ĵ��ι��캯�������á�" << endl;
}

// Lion����д������麯����ֻ��Ҫ�ں�����������override�ؼ��֣�����ʵ�ֲ���Ҫ��override
void Lion::makeSound() {
	// ��д������麯��
	cout << "Lion roars." << endl;
}

void Lion::jump()
{
	// ��д����Ĵ��麯��
	cout << "Lion jump." << endl;
}

void Lion::run()
{
	// ��д����Ĵ��麯��
	cout << "Lion run." << endl;
}

void Lion::hunt()
{
	cout << "Lion hunts for prey." << endl;
}

Rabbit::Rabbit()
{
	cout << "������Rabbit��Ĭ�Ϲ��캯�������á�" << endl;
}

Rabbit::Rabbit(string name,int age) : Animal(name,age) {
	cout << "������Rabbit�Ĵ��ι��캯�������á�" << endl;
}

void Rabbit::makeSound()
{
	// ��д������麯��
	cout << "Rabbit squeaks." << endl;
}

void Rabbit::jump()
{
	// ��д����Ĵ��麯��
	cout << "Rabbit jump." << endl;
}

void Rabbit::run()
{
	// ��д����Ĵ��麯��
	cout << "Rabbit run." << endl;
}