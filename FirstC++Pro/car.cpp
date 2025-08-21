#include "car.h"

void Wheel::wheelPrintInfo() {
	string str = "Ʒ���ǣ�" + brand + "������ǣ�" + year;
	cout << "��̥��Ϣ��ӡ��" << str << endl;
}

void Engine::enginePrintInfo() {
	string str = "Ʒ���ǣ�" + brand + "������ǣ�" + year;
	cout << "������Ϣ��ӡ��" << str << endl;
}

//::���������������������ڷ�����ĳ�Ա���������
void Car::realPrintCarInfo() {
	string str = "����Ʒ���ǣ�" + brand + "���ͺ��ǣ�" + type + "����ɫ�ǣ�" + color + "����������ǣ�" + to_string(year);
	cout << "��Ա������ӡ��" << str << endl;
	wheel.wheelPrintInfo(); //������̥�ĳ�Ա����
	if (engine != nullptr) {
		engine->enginePrintInfo(); //��������ĳ�Ա����
	}
	else {
		cout << "������Ϣδ���á�" << endl;
	}
}

void PrintCarInfo(string color, string brand, string type, int year)
{
	//printf("%s",ָ��)
	string str = "����Ʒ���ǣ�" + brand + "���ͺ��ǣ�" + type + "����ɫ�ǣ�" + color + "����������ǣ�" + to_string(year);
	cout << str << endl;
}

void carRun()
{
	printf("The car is running.\n");
}

void carStop()
{
	printf("The car has stopped.\n");
}