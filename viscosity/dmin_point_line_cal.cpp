#include <iostream>
using namespace std;
#include <cmath>

double length(double *a);
double innerproduct(double *a, double *b);


double dmin_point_line_cal(double *P, double *A, double *B) //求P点到线段AB的最短距离
{
	double vAP[3],vAB[3],vBP[3];
	double dAB,dAP;
	double proj_AP;
	double dmin;
	int k;
	for (k=0;k<=2;k++)
	{
		vAP[k]=P[k]-A[k];
		vAB[k]=B[k]-A[k];
	}
	
	dAB=length(vAB);
	dAP=length(vAP);
	proj_AP=innerproduct(vAP,vAB)/dAB;
	if (proj_AP>dAB)
	{
		for (k=0;k<=2;k++)
		{
			vBP[k]=P[k]-B[k];
		}
		dmin=length(vBP);
	}
	else if (proj_AP<0)
	{
		dmin=dAP;
	}
	else
	{
		dmin=sqrt(dAP*dAP-proj_AP*proj_AP);	
	}
	return dmin;
}
