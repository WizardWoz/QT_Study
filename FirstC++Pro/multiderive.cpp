#include "multiderive.h"

Base::Base(int val) {
	data = val;
}

ClassA::ClassA(int val) : Base(val) {

}

void ClassA::displayA() {
	cout << "This is ClassA" << endl;
	cout << "ClassA���е�data��Ա����ֵ������Ψһ��Base���ࣩ: " << data << endl;
}

void ClassA::testFunc() {
	cout << "This is ClassA's testFunc()" << endl;
}

ClassB::ClassB(int val) : Base(val) {
	
}

void ClassB::displayB() {
	cout << "This is ClassB" << endl;
	cout << "ClassB���е�data��Ա����ֵ������Ψһ��Base���ࣩ: " << data << endl;
}

void ClassB::testFunc() {
	cout << "This is ClassB's testFunc()" << endl;
}

//��ʼ���б�����Ҫ��������ֱ�ӻ��ࡢ��ӻ���Ĺ��캯��
Derived::Derived(int val) : ClassA(val), ClassB(val), Base(val) {
	ClassA::data = 1;
	ClassB::data = 2;
}

void Derived::display() {
	cout << "��̳�ClassA��ClassB��Derived��:" << endl;
	displayA(); // ����ClassA�ķ���
	displayB(); // ����ClassB�ķ���
	//testFunc(); // ֱ�ӵ��ûᱨ��������
	ClassA::testFunc(); // ͨ������ָ������ClassA��testFunc()
	ClassB::testFunc(); // ͨ������ָ������ClassB��testFunc()
	cout << "Derived���е�data��Ա����ֵ������Ψһ��Base���ࣩ: " << Base::data << endl;
}