#include <iostream>
using namespace std;

//由于没有办法返回一个数组，从而设成void，p指向的数组为结果
void crossproduct(double *p, double *a, double *b)
{
	p[0]=a[1]*b[2]-a[2]*b[1];
	p[1]=a[2]*b[0]-a[0]*b[2];
	p[2]=a[0]*b[1]-a[1]*b[0];
}
