#include <iostream>
using namespace std;
#include "particle.h"

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);
void numberproduct(double *result, double a, double *v);

void particle::F_Fv_cal()
{
	int ne;
	double pVjpxi[3][3];
	double Fvi[3][3];
	int j0,j1,j2;
	double temp[3];
	int i,j;
	for (ne=1;ne<=e_num;ne++)
	{
		//计算pVjpxi
		j0=e[ne].p_no[0];
		j1=e[ne].p_no[1];
		j2=e[ne].p_no[2];
		crossproduct(temp, p[j1].pos, p[j2].pos);
		numberproduct(pVjpxi[0], 1.0/6.0, temp);
		crossproduct(temp, p[j2].pos, p[j0].pos);
		numberproduct(pVjpxi[1], 1.0/6.0, temp);
		crossproduct(temp, p[j0].pos, p[j1].pos);
		numberproduct(pVjpxi[2], 1.0/6.0, temp);
		//计算Fvi，并加入总和
		for (i=0;i<=2;i++)
		{
			for (j=0;j<=2;j++)
			{
				Fvi[i][j]=-kv*(V-V0)/V0*pVjpxi[i][j];
				F[e[ne].p_no[i]][j]=F[e[ne].p_no[i]][j]+Fvi[i][j];
			}
		}
	}
}
