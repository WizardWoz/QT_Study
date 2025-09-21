#include "multiderive.h"

Base::Base(int val) {
	data = val;
}

ClassA::ClassA(int val) : Base(val) {

}

void ClassA::displayA() {
	cout << "This is ClassA" << endl;
	cout << "ClassA类中的data成员变量值（来自唯一的Base基类）: " << data << endl;
}

void ClassA::testFunc() {
	cout << "This is ClassA's testFunc()" << endl;
}

ClassB::ClassB(int val) : Base(val) {
	
}

void ClassB::displayB() {
	cout << "This is ClassB" << endl;
	cout << "ClassB类中的data成员变量值（来自唯一的Base基类）: " << data << endl;
}

void ClassB::testFunc() {
	cout << "This is ClassB's testFunc()" << endl;
}

//初始化列表中需要调用所有直接基类、间接基类的构造函数
Derived::Derived(int val) : ClassA(val), ClassB(val), Base(val) {
	ClassA::data = 1;
	ClassB::data = 2;
}

void Derived::display() {
	cout << "多继承ClassA和ClassB的Derived类:" << endl;
	displayA(); // 调用ClassA的方法
	displayB(); // 调用ClassB的方法
	//testFunc(); // 直接调用会报错，二义性
	ClassA::testFunc(); // 通过类名指定调用ClassA的testFunc()
	ClassB::testFunc(); // 通过类名指定调用ClassB的testFunc()
	cout << "Derived类中的data成员变量值（来自唯一的Base基类）: " << Base::data << endl;
}