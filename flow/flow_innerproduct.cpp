#include <iostream>
using namespace std;
#include "flow.h"

double flow::innerproduct(double *a, double *b)
{
	double result;
	result=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
	return result;
}

double flow::innerproduct(int *a, double *b)
{
	double result;
	result=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
	return result;
}

