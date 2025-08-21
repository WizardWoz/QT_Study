#include "overload.h"

int Data::staticval = 0; // ��̬��Ա������ʼ��
int Data::numOfInstances = 0; // ��̬��Ա������ʼ��

Data::Data() {
	// ÿ�δ���һ��Data����ʱ��ʵ��������1
	numOfInstances++;
	data = 0; // ��ʼ���Ǿ�̬��Ա����
}

Data::~Data() {
	// ÿ������һ��Data����ʱ��ʵ��������1
	numOfInstances--;
}

int Data::getStaticVal() {
	//data++; // ���ܷ��ʷǾ�̬��Ա����
	return staticval;
}

Point Point::operator+(const Point& other) const {
	Point result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}