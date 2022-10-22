#include <iostream>
using namespace std;

void numberproduct(double *result, double a, double *v)
{
	int i;
	for (i=0;i<=2;i++)
	{
		result[i]=a*v[i];
	}
}
