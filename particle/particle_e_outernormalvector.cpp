#include <iostream>
using namespace std;
#include "particle.h"

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);

void particle::e_outernormalvector()
{
	int ne;
	for (ne=1;ne<=e_num;ne++)
	{
		e[ne].vector_outernormal_cal();
	}
	/*
	double pos[3][3];
	double normalvector[3];
	double x01[3],x02[3];
	int i,j;
	double sign;
	for (ne=1;ne<=e_num;ne++)
	{
		for (i=0;i<=2;i++)
		{
			for (j=0;j<=2;j++)
			{
				pos[i][j]=p[e[ne].p_no[i]].pos[j];
			}
		}
		for (j=0;j<=2;j++)
		{
			x01[j]=pos[1][j]-pos[0][j];
			x02[j]=pos[2][j]-pos[0][j];
		}
		crossproduct(normalvector, x01, x02);
		sign=innerproduct(normalvector, pos[0]);
		if (sign>0)
		{
			cout<<"outer"<<' '<<sign<<endl;
		}
		else
			cout<<"nononononononononononononononono!!!!!!!!!!!"<<endl;
	}
	*/
}
