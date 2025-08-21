#include <iostream>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "car.h"
#include "cir.h"

using namespace std;

/*
  ���е��˻���һ���࣬��������˵ĸ�����Ϣ�Ͷ�ȣ�����private���ε�˽�б���������Ĵ��������һ�����󣬲���˽���޸��˻���Ϣ����Ҫ���еĲ������̣�
  Ҳ����public���εĹ��к���ȥ����private���ε�˽�б���
*/
class BankAccount
{
private:
	string name;    //�˻���
	string addr;	//�˻���ַ
	int age;	   //�˻�����
	double balance; //�˻����
public:
	void registerAccount(string newName,string newAddr,int age,double balance); //ע���˻�
	void withdraw(double amount);	//ȡ��
	void deposit(double amount);	//���
	double getBalance();	//��ȡ���
	void printAccountInfo();
};

void BankAccount::registerAccount(string newName, string newAddr, int newAge, double newBalance) {
	name = newName;
	addr = newAddr;
	age = newAge;
	balance = newBalance;
}

void BankAccount::withdraw(double amount) {
	if (amount>balance)
	{
		cerr << "ȡ��ɹ���ȡ��������˻����" << endl;
	}
	else if (amount<=0)
	{
		std::cerr << "ȡ��ɹ���ȡ�������Ϊ����" << std::endl;
	}
	else
	{
		balance -= amount;
	}
}

void BankAccount::deposit(double amount) {
	if (amount>0)
	{
		balance += amount;
	}
	else
	{
		cerr << "���ɹ�����������Ϊ����" << endl;
	}
}

double BankAccount::getBalance() {
	return balance;
}

void BankAccount::printAccountInfo() {
	string str = "�˻�����" + name + "���˻���ַ��" + addr + "���˻����䣺" + to_string(age) + "���˻���" + to_string(balance);
	cout << str << endl;
}

bool compare(int a, int b) {
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
	Car* AudiA6 = new Car();	//new��̬�����ڴ��Car����ʵ��
	AudiA6->color = "White";
	AudiA6->brand = "Audi";
	AudiA6->type = "Sedan";
	AudiA6->wheel.brand = "Michelin"; //������̥Ʒ��
	AudiA6->wheel.year = "2022"; //������̥���
	AudiA6->engine = new Engine; //new��̬�����ڴ������
	AudiA6->engine->brand = "Audi Engine"; //��������Ʒ��
	AudiA6->engine->year = "2022"; //�����������
	AudiA6->year = 2022;
	//������̰汾
	//AudiA6->printCarInfo = PrintCarInfo;
	//AudiA6->printCarInfo(AudiA6->color, AudiA6->brand, AudiA6->type, AudiA6->year);
	//�������汾
	AudiA6->realPrintCarInfo();
	delete AudiA6;

	BankAccount account;
	account.registerAccount("Alice", "123 Main St", 30, 1000.0);
	account.printAccountInfo();
	account.deposit(500.0);
	account.printAccountInfo();
	account.withdraw(200.0);
	account.printAccountInfo();
	cout << "������ȡ�˻���" << account.getBalance() << endl;
    return 0;
}