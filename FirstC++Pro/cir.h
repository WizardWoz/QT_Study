#ifndef CIR_H
#define CIR_H

//���������ռ�cir
namespace cir
{
	double PI = 3.1415926;
	//��ȡԲ���ܳ��ĺ���
	double getLengthOfCircle(double radius)
	{
		return 2 * PI * radius;
	}
	//��ȡԲ������ĺ���
	double getAreaOfCircle(double radius)
	{
		return PI * radius * radius;
	}
}

#endif // CIR_H