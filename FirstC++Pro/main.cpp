#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "car.h"
#include "bank.h"
#include "overload.h"
#include "animal.h"
#include "multiderive.h"
#include "cir.h"

using namespace std;

static bool compare(int a, int b) {
	return a > b;
}

/*
  �ص�����:ͨ������ָ����õĺ�������������ָ�루��ַ����Ϊ�������ݸ���һ�������������ָ�뱻������������ָ��ĺ���ʱ�����Ǿͳ�֮Ϊ�ص�������
  �ص�����ͨ������ʵ���¼�������Ӧ���첽��̻򽫺�����Ϊ�������ݸ�����������
*/
int getMax(int a, int b, bool (*cmp)(int, int)) {
	if (cmp(a, b)) {
		return a;
	} else {
		return b;
	}
}

double vals[] = { 10.1,12.6,33.1,24.1,50.0 };

//����������ֵΪһ������ʱ������������Ϊ���ʽ��ֵ
double& setvalues(int i) {
	double& ref = vals[i];
	return ref; //���������е�i��Ԫ�ص�����
	//Ҫע�ⲻ�����ú����ڲ��ľֲ���������Ϊ�ֲ�������ջ�ռ��ں�����������Զ�����
	//�����Ҫ����һ�����ã�����ȷ�����õĶ����ں������ý�������Ȼ���ڣ����磺ȫ�ֱ�����static��������̬������ڴ�
}

int main() {
    //std::cout << "Hello, World!" << std::endl;
	double myRadius = 5.0;
	int a,b;
	bool btype=false;	//C99��׼����֧��
	//��׼��������
	cout << "Hello, World!" << endl;
	cout << "��ã����磡" << "���ǲ�������ġ�" << endl;
	//ʹ�������ռ�cir�еĺ���
	printf("Circle radius: %.2f\n", myRadius);
	printf("Circle length: %.2f\n", cir::getLengthOfCircle(myRadius));
	printf("Circle area: %.2f\n", cir::getAreaOfCircle(myRadius));
	//ʹ���Զ���ı���a��b
	cin >> a >> b;
	cout << "You entered: " << a << " and " << b << endl;
	cout << a << " + " << b << " = " << a + b << endl;
	//��׼���������
	cerr << "This is an error message." << endl;
	//��ӡint��unsigned int��long long��ȡֵ��Χ
	std::cout << "The range of int is from " << INT_MIN << " to " << INT_MAX << std::endl;
	std::cout << "The range of unsigned int is from " << 0 << " to " << UINT_MAX << std::endl;
	std::cout << "The range of long long is from " << LLONG_MIN << " to " << LLONG_MAX << std::endl;

	//Lamda���ʽ��C++11��������ԣ�������Ϊ������������������Ҫ������λ���������庯���������赥������
	//[capture clause](parameter)->returnType {
	//	//�����壬��ʹ�ò����б��еı���
	// return expression;	//��ѡ�ķ������
	//}
	//1.�����б�(capture clause)�����ڲ����ⲿ��������Lambda���ʽ��ʹ�á����԰�ֵ��������ò��񡣲����б����Ϊ�գ�Ҳ���԰����������[var1,var2,var3,...]
	//2.�����б�(parameter)��ָ��Lambda���ʽ�Ĳ���������Ϊ�ջ�����������(param1,param2,param3,...)�������б�����ͨ�������ƣ�����ָ���������͡�
	//3.��������(returnType)��ָ��Lambda���ʽ�ķ������ͣ�����ʡ�ԣ�����������ݺ������Զ��ƶϷ�������(auto)�������Ҫ��ʽָ���������ͣ�����ʹ��->���š�
	//4.�����壺Lambda���ʽ�����岿�֣�����ʵ�ʵĴ����߼������԰���������䣬Ҳ�����ǵ������ʽ��
	//ʹ��Lambda���ʽ�����б�
	auto add = [](int x, int y) -> int {
		return x + y;
		};
	cout << "Using Lambda expression to add: " << add(10, 4) << endl;
	//ʹ��Lambda���ʽ�����б�
	int x = 5, y = 10;
	int* px = &x;
	int* py = &y;
	auto add_capture1 = [&px, &py]() -> int {	//��ָ�벶���ⲿ����
		//x++; //����ı���������Lambda���ʽ��ʹ�ã��������޸�
		*px += 1; //�����Ҫ�޸Ĳ���ı���������ʹ�����û�ָ�벶��
		return *px + *py;
		};
	cout << "Using Lambda expression with captured variables��ָ�벶��: " << add_capture1() << endl;
	auto add_capture2 = [&]() -> int {	//�����ò��������ⲿ����
		//x++; //����ı���������Lambda���ʽ��ʹ�ã��������޸�
		x += 1; //�����Ҫ�޸Ĳ���ı���������ʹ�����û�ָ�벶��
		return x + y;
		};
	cout << "Using Lambda expression with captured variables�������ò������б�����: " << add_capture2() << endl;
	auto add_capture3 = [=]() -> int {	//��ֵ���������ⲿ����
		//x++; //����ı���������Lambda���ʽ��ʹ�ã��������޸�
		//x += 1; //�����Ҫ�޸Ĳ���ı���������ʹ�����û�ָ�벶��
		return x + y;
		};
	cout << "Using Lambda expression with captured variables����ֵ�������б�����: " << add_capture3() << endl;

	bool (*p)(int a, int b) = compare; //����ָ��ָ��compare����
	//ʹ�ûص�������ȡ���ֵ
	int maxVal = getMax(x, y, p);
	//�ص�������ʹ��Lambda���ʽ��Ϊ��������ָ��
	int maxValLambda = getMax(x, y, [](int a, int b) { 
		return a > b;
	});
	cout << maxVal << " is the maximum value between " << x << " and " << y << endl;
	cout << maxValLambda << " is the maximum value between " << x << " and " << y << " (using lambda)" << endl;

	// ֱ�ӽ���struct Car��ʵ����û���⣩
	/*struct Car BMWThreeSeries;
	BMWThreeSeries.color = "Black";
	BMWThreeSeries.brand = "BMW";
	BMWThreeSeries.type = "Sedan";
	BMWThreeSeries.year = 2023;
	BMWThreeSeries.printCarInfo = PrintCarInfo;
	BMWThreeSeries.printCarInfo(BMWThreeSeries.color, BMWThreeSeries.brand, BMWThreeSeries.type, BMWThreeSeries.year);*/
	// ͨ��malloc��̬�����ڴ潨��struct Car��ʵ�����������⣩������ת����C++����������
	Car* AudiA6 = new Car();	//new��̬�����ڴ��Car����ʵ���������޲ι��캯��
	AudiA6->color = "White";
	AudiA6->brand = "Audi";
	AudiA6->type = "Sedan";
	AudiA6->wheel.brand = "Michelin"; //������̥Ʒ��
	AudiA6->wheel.year = "2022"; //������̥���
	AudiA6->engine = new Engine; //new��̬�����ڴ������
	AudiA6->engine->brand = "Audi Engine"; //��������Ʒ��
	AudiA6->engine->year = "2022"; //�����������
	AudiA6->year = 2022;
	//ֱ�Ӵ���һ��Car���ʵ�������ô��������캯��
	Car BenzCClass("Benz",2025);
	Car& BMWFiveSeries = *new Car("BMW", 2024); //����һ��BMW��ϵ��ʵ����ʹ������
	Car* TeslaModelS = new Car("Tesla"); //����һ��Tesla Model S��ʵ����ʹ��ָ��
	delete TeslaModelS; //�ͷ�Tesla Model S���ڴ�
	//������̰汾
	//AudiA6->printCarInfo = PrintCarInfo;
	//AudiA6->printCarInfo(AudiA6->color, AudiA6->brand, AudiA6->type, AudiA6->year);
	//�������汾
	AudiA6->realPrintCarInfo();
	delete AudiA6;

	//new���䵥������
	Car* car1 = new Car();
	//new�����������
	int* arr = new int[5] {1, 2, 3, 4, 5};
	delete[] arr; //�ͷ������ڴ�
	delete car1; //�ͷŵ��������ڴ�

	BankAccount account1;
	cout << "main������BankAccount account1����ĵ�ַ��" << &account1 << endl;
	account1.registerAccount("Alice", "123 Main St", 30, 1000.0);
	account1.printAccountInfo();
	account1.deposit(500.0);
	account1.printAccountInfo();
	account1.withdraw(200.0);
	account1.printAccountInfo();
	cout << "������ȡ�˻���" << account1.getBalance() << endl;
	//ʵ����ʽ����
	account1.setAge(32).printAccountInfo(); //��������Ϊ32������ӡ�˻���Ϣ
	BankAccount account2; //������һ��BankAccount����
	cout << "main������BankAccount account2����ĵ�ַ��" << &account2 << endl;
	//�вι��캯��
	BankAccount* account3 = new BankAccount(10);
	delete account3;
	//��main()����ִ����ϣ�account1��account2���������ڽ��������������������������Զ�������������

	//������Ϊ����ֵ
	cout << "�ı�ǰ��ֵ��";
	for (int i = 0; i < 5; i++)
	{
		cout << vals[i] << " ";
	}
	cout << endl;
	setvalues(0) = 20.0; //ͨ�������޸������еĵ�һ��Ԫ��
	setvalues(2) = 25.3; //ͨ�������޸������еĵ�����Ԫ��
	cout << "�ı���ֵ��";
	for (int i = 0; i < 5; i++)
	{
		cout << vals[i] << " ";
	}
	cout << endl;

	cout << "����Data���dataʵ��ǰ��numOfInstancesֵ��" << Data::numOfInstances << endl;
	Data* data=new Data;
	cout << "����Data���dataʵ�����numOfInstancesֵ��" << Data::numOfInstances << endl;
	// �������ص�print����
	data->print(42);		   // ����print(int)
	data->print(3.14);         // ����print(double)
	data->print("Hello");      // ����print(const char*)
	Data::staticval = 100; // ���þ�̬��Ա������ֵ
	delete data; // ɾ��Data���ʵ����������������
	cout << "ɾ��Data���dataʵ�����numOfInstancesֵ��" << Data::numOfInstances << endl;
	// ���þ�̬��Ա����
	cout << "Data��ľ�̬��Ա����staticval��" << Data::staticval << endl;
	// ���þ�̬��Ա����
	cout << "Data��ľ�̬��Ա����getStaticVal()����ֵ��" << Data::getStaticVal() << endl;
	Data data1;
	Data data2;
	cout << "��ȫ���������ڴ�����data1����numOfInstancesֵ��" << Data::numOfInstances << endl;
	{
		Data data3; // �ֲ��������������������Զ�������������
		cout << "�ھֲ��������ڴ�����data3����numOfInstancesֵ��" << Data::numOfInstances << endl;
	}
	cout << "��ȫ���������ڴ�����data2����numOfInstancesֵ��" << Data::numOfInstances << endl;

	Person person1, person2;
	person1.name = "Alice";
	person1.age = 30;
	person2.name = "Alice";
	person2.age = 30;
	// ����==������Ƚ�Person����
	// ע�⣺��Ҫ��Person���ж���operator==������ʵ���Զ���ıȽ��߼�;��������Ѿ�������operator==�������Ƚ�name��age�Ƿ����
	// ���û�ж��壬��Ĭ�ϰ���ַ�Ƚ�
	bool ret = person1 == person2;
	cout << "Are person1 and person2 equal? " << (ret ? "Yes" : "No") << endl;

	Point point1, point2, point3;
	point1.x = 10;
	point1.y = 20;
	point2.x = 10;
	point2.y = 20;
	//��������� + ʵ������Point��������
	point3 = point1 + point2;
	cout << "point1 + point2 = (" << point3.x << ", " << point3.y << ")" << endl;

	Roadster myRoadster;
	//myRoadster.color = "Red";	//�����˽�г�Ա���ܱ��������
	myRoadster.brand = "Tesla";	//���ó�public���м̳к�������Է��ʸ���Ĺ��г�Ա
	myRoadster.openTopped();
	myRoadster.pDrifting();

	Lion lion("Simba", 5, 30);
	lion.makeSound();
	lion.eatFood();
	lion.hunt();
	lion.accessProtectedData(); // ����Animal���protected��Ա
	lion.accessPublicData(); // ����Animal���public��Ա
	lion.accessPrivateData(); // ����Animal���private��Ա��ͨ��Animal��Ĺ��г�Ա��������
	Rabbit rabbit("Bunny", 3);
	rabbit.makeSound();
	rabbit.accessProtectedData(); // ����Animal���protected��Ա
	rabbit.accessPublicData(); // ����Animal���public��Ա
	Animal* animalPtr1=new Lion("Simba", 5, 30); //����ָ��
	animalPtr1->makeSound(); // �������������д����
	animalPtr1->jump();	// �������������д����
	//����ָ��ֻ��ָ���м̳е���������󣬲���ָ�򱣻��̳л�˽�м̳е����������
	//Animal* animalPtr2 = new Rabbit("Bunny", 3); //����������ǿ��ת����: �ӡ�Rabbit *������Animal *����ת�����ڣ����޷�����
	//animalPtr2->makeSound(); // �������������д����
	delete animalPtr1; //�ͷ��ڴ棬�������������������
	//delete animalPtr2; //�ͷ��ڴ棬�������������������
	Animal& animalRef = *new Lion; //��������
	animalRef.makeSound(); // �������������д����
	animalRef.jump();

	Derived obj(0);
	obj.displayA();
	obj.displayB();
	obj.display();
    return 0;
}