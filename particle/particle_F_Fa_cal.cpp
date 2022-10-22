#include <iostream>
using namespace std;
#include "particle.h"

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);
void numberproduct(double *result, double a, double *v);

void particle::F_Fa_cal()
{
	int ne;
	double pAjpxi[3][3];
	double Fai[3][3];
	int i,j;
	int j0,j1,j2; //单元三个节点对应编号
	double x21[3], x02[3], x10[3];
	double temp[3];
	for (ne=1;ne<=e_num;ne++)
	{
		//计算pAjpxi
		j0=e[ne].p_no[0];
		j1=e[ne].p_no[1];
		j2=e[ne].p_no[2];
		linear(x21, 1,  p[j1].pos, -1, p[j2].pos);
		linear(x02, 1,  p[j2].pos, -1, p[j0].pos);		
		linear(x10, 1,  p[j0].pos, -1, p[j1].pos);
		crossproduct(temp, x21, e[ne].vector_outernormal);
		numberproduct(pAjpxi[0], 0.5, temp);
		crossproduct(temp, x02, e[ne].vector_outernormal);
		numberproduct(pAjpxi[1], 0.5, temp);
		crossproduct(temp, x10, e[ne].vector_outernormal);
		numberproduct(pAjpxi[2], 0.5, temp);
				
	
		//计算Fai，并加入总和力F
		for (i=0;i<=2;i++)
		{
			for (j=0;j<=2;j++)
			{
				Fai[i][j]=-ka*(A-A0)/A0*pAjpxi[i][j];
				F[e[ne].p_no[i]][j]=F[e[ne].p_no[i]][j]+Fai[i][j];
			}
		}
	}
}
