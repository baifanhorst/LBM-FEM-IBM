#include <iostream>
using namespace std;


//S=0.5*(0->1)*(0->2)
double area2Dsigned(double *p0, double *p1, double *p2)
{
	double v01[2];
	double v02[2];
	int k;
	for (k=0;k<=1;k++)
	{
		v01[k]=p1[k]-p0[k];
		v02[k]=p2[k]-p0[k];
	}
	double S;
	S=0.5*(v01[0]*v02[1]-v01[1]*v02[0]);
	return S;
}
