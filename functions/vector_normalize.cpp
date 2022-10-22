#include <iostream>
using namespace std;
#include <cmath>

//由于没有办法返回一个数组，从而设成void，e指向的数组为结果
void normalize(double *e, double *a)
{
	double l; //长度
	l=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2])+1e-20;
	e[0]=a[0]/l;
	e[1]=a[1]/l;
	e[2]=a[2]/l;
}
