#include <stdio.h>
#include <stdlib.h>

// 通过C语言结构体引入C++的类
struct Car
{
	char* color;    //车辆颜色
	char* brand;    //车辆品牌
	char* type;     //车辆类型
	int year;       //车辆年份

    void (*printCarInfo)(char* color, char* brand, char* type, int year);     //函数指针，指向车辆介绍函数
	void (*carRun)(char* type);       //函数指针，指向车辆行驶函数
	void (*carStop)(char* type);      //函数指针，指向车辆停止函数
};

void PrintCarInfo(char* color, char* brand, char* type, int year)
{
	//printf("%s",指针)
	printf("车的品牌是：%s，型号是：%s，颜色是：%s，上市年份是：%d\n",brand,type,color,year);
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
    printf("你好，世界！\n");
    //警告：error C6031：返回值被忽略: “scanf”。
	//scanf("%d %d", &a,&b);
    if (scanf("%d %d", &a, &b) != 2) {
        printf("输入无效，请输入两个整数。\n");
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