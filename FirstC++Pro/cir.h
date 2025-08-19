#ifndef CIR_H
#define CIR_H

//定义命名空间cir
namespace cir
{
	double PI = 3.1415926;
	//获取圆形周长的函数
	double getLengthOfCircle(double radius)
	{
		return 2 * PI * radius;
	}
	//获取圆形面积的函数
	double getAreaOfCircle(double radius)
	{
		return PI * radius * radius;
	}
}

#endif // CIR_H