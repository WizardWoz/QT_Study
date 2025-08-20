#include <stdio.h>
#include <stdlib.h>

// ͨ��C���Խṹ������C++����
struct Car
{
	char* color;    //������ɫ
	char* brand;    //����Ʒ��
	char* type;     //��������
	int year;       //�������

    void (*printCarInfo)(char* color, char* brand, char* type, int year);     //����ָ�룬ָ�������ܺ���
	void (*carRun)(char* type);       //����ָ�룬ָ������ʻ����
	void (*carStop)(char* type);      //����ָ�룬ָ����ֹͣ����
};

void PrintCarInfo(char* color, char* brand, char* type, int year)
{
	//printf("%s",ָ��)
	printf("����Ʒ���ǣ�%s���ͺ��ǣ�%s����ɫ�ǣ�%s����������ǣ�%d\n",brand,type,color,year);
}

void carRun()
{
	printf("The car is running.\n");
}

void carStop()
{
	printf("The car has stopped.\n");
}

int main() {
    int a,b;
    printf("Hello, World!\n");
    printf("��ã����磡\n");
    //���棺error C6031������ֵ������: ��scanf����
	//scanf("%d %d", &a,&b);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("������Ч������������������\n");
        return 1;
    }
	printf("You entered: %d %d\n", a,b);
	printf("%d + %d = %d\n", a, b, a + b);

	struct Car BMWThreeSeries;
	BMWThreeSeries.color = "Black";
	BMWThreeSeries.brand = "BMW";
	BMWThreeSeries.type = "Sedan";
	BMWThreeSeries.year = 2023;
	BMWThreeSeries.printCarInfo = PrintCarInfo;
	BMWThreeSeries.printCarInfo(BMWThreeSeries.color,BMWThreeSeries.brand,BMWThreeSeries.type,BMWThreeSeries.year);

	struct Car* AudiA6=NULL;
	AudiA6 = (struct Car*)malloc(sizeof(struct Car));
	AudiA6->color = "White";
	AudiA6->brand = "Audi";
	AudiA6->type = "Sedan";
	AudiA6->year = 2022;
	AudiA6->printCarInfo = PrintCarInfo;
	AudiA6->printCarInfo(AudiA6->color, AudiA6->brand, AudiA6->type, AudiA6->year);
	free(AudiA6);
    return 0;
}