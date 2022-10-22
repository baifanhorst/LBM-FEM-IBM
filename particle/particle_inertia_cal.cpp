#include <iostream>
using namespace std;
#include <eigen3/Eigen/Dense>


#include "particle.h"
double innerproduct(double *a, double *b);
double length(double *a);

void particle::inertia_cal()
{
	int a,b,i;
	int k;
	int delta;
	double niri;
	double risquare;
	
	avepos_cal();
	for (i=1;i<=e_num;i++)
	{
		for (k=0;k<=2;k++)
		{
			e[i].pos_center[k]=(e[i].pos[0][k]+e[i].pos[1][k]+e[i].pos[2][k])/3.0-pos_center[k];   //相对于中心的单元中心位置
		}
	}
	for (a=0;a<=2;a++)
	{
		for (b=0;b<=2;b++)
		{
			I[a][b]=0;
			for (i=1;i<=e_num;i++)
			{
				if (a==b)
				{
					delta=1;
				}
				else
				{
					delta=0;
				}
				niri=innerproduct(e[i].vector_outernormal, e[i].pos_center);
				risquare=length(e[i].pos_center); risquare=risquare*risquare;
								
	
				I[a][b]=I[a][b]+niri*(risquare*delta-e[i].pos_center[a]*e[i].pos_center[b])*e[i].A;
			}
			I[a][b]=I[a][b]/5.0;
		}
	}
}
