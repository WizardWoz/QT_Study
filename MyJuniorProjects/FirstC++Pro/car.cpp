#include "car.h"

void Wheel::wheelPrintInfo() {
	string str = "Ʒ���ǣ�" + brand + "������ǣ�" + year;
	cout << "��̥��Ϣ��ӡ��" << str << endl;
}

void Engine::enginePrintInfo() {
	string str = "Ʒ���ǣ�" + brand + "������ǣ�" + year;
	cout << "������Ϣ��ӡ��" << str << endl;
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

/*
  Car��������޲ι��캯��
  ʹ���˳�Ա������ʼ���б�: engine(nullptr)����ʼ����Ա�����ͺ���ָ�룻
  ֱ���ڶ���Ĺ�������б����ƣ��������ȴ�����Ա������ֵ�����������
*/
Car::Car() {
	cout << "Car����޲������캯�������á�" << endl;
	//���캯����ʼ����Ա����
	color = "Unknown";
	brand = "Unknown";
	type = "Unknown";
	year = 0;
	engine = nullptr; //����ָ���ʼ��Ϊnullptr����ʾδ��������
	printCarInfo = PrintCarInfo; //��ʼ������ָ��
	carRun = carRun; //��ʼ��������ʻ����ָ��
	carStop = carStop; //��ʼ������ֹͣ����ָ��
}

/*
  Car��������вι��캯��
  ʹ���˳�Ա������ʼ���б�: brand(brand), year(year), engine(nullptr)����ʼ����Ա�����ͺ���ָ�룻
*/
Car::Car(string brand, int year) : brand(brand), year(year), engine(nullptr) {
	cout << "Car��Ĵ��������캯�������á�" << endl;
	//���캯����ʼ����Ա����
	color = "Unknown";
	type = "Unknown";
	printCarInfo = PrintCarInfo; //��ʼ������ָ��
	carRun = carRun; //��ʼ��������ʻ����ָ��
	carStop = carStop; //��ʼ������ֹͣ����ָ��
}

//ʵ�ʺͳ�Ա������ʼ���б�: brand(brand), year(year), engine(nullptr)Ч��һ����
// ���Ա���׶α���C2084 ������Car::Car(std::string,int)����������
//Car::Car(string brand, int year) : engine(nullptr) {
//	cout << "Car��Ĵ��������캯�������á�" << endl;
//	//���캯����ʼ����Ա����
//	color = "Unknown";
// C++��thisָ��ָ��ǰ����ʵ������������������ĳ�Ա�����ͳ�Ա����
//	this->brand = brand; //ʹ��thisָ����ʳ�Ա����
//	type = "Unknown";
//	this->year = year;
//	printCarInfo = PrintCarInfo; //��ʼ������ָ��
//	carRun = carRun; //��ʼ��������ʻ����ָ��
//	carStop = carStop; //��ʼ������ֹͣ����ָ��
//}

Car::Car(string brand) : engine(nullptr) {
	cout << "Car��Ĵ��������캯�������á�" << endl;
	//���캯����ʼ����Ա����
	color = "Unknown";
	//C++��thisָ��ָ��ǰ����ʵ������������������ĳ�Ա�����ͳ�Ա����
	this->brand = brand; //ʹ��thisָ����ʳ�Ա����
	type = "Unknown";
	year = 0;
	printCarInfo = PrintCarInfo; //��ʼ������ָ��
	carRun = carRun; //��ʼ��������ʻ����ָ��
	carStop = carStop; //��ʼ������ֹͣ����ָ��
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

void Roadster::openTopped() {
	cout << "���񳵿������ܱ����á�" << endl;
}

void Roadster::pDrifting() {
	cout << "����Ư�ƹ��ܱ����á�" << endl;
}