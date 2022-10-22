#include <iostream>
using namespace std;
//向量的线性运算
void linear(double *result, double x1, double *v1, double x2, double *v2)
{
	int i;
	for (i=0;i<=2;i++)
	{
		result[i]=x1*v1[i]+x2*v2[i];
	}
}
