#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);
void numberproduct(double *result, double a, double *v);

void particle::F_Fb_cal()
{	
	double Ai,Aj; //面积
	double ninj; //内积
	double x1[3],x2[3],x3[3],x4[3]; //四个点位置
	double pninjpx[5][3]; //第一个不用
	double Fbk1234[5][3]; //第一个不用 在1234编号下计算的Fbk
	int nl;
	int i,j;
	double x32[3],x43[3],x13[3],x21[3],x14[3],x31[3];
	double tempji[3], tempij[3];
	int n1,n2,n3,n4,ni,nj;
	double firstterm[3], secondterm[3];
	
	for (nl=1;nl<=l_num;nl++)
	{	
		//必要的参数设置
		n1=l[nl].p_n1;
		n2=l[nl].p_n2;
		n3=l[nl].p_n3;
		n4=l[nl].p_n4;
		ni=l[nl].e_ni;
		nj=l[nl].e_nj;
		
		Ai=e[ni].A;
		Aj=e[nj].A;
		
		ninj=innerproduct(e[ni].vector_outernormal, e[nj].vector_outernormal);
		linear(tempij, 1, e[ni].vector_outernormal, -ninj, e[nj].vector_outernormal);
		linear(tempji, 1, e[nj].vector_outernormal, -ninj, e[ni].vector_outernormal);
		
		//计算pninj[i][j]
		//k=1
		linear(x32, 1, p[n2].pos, -1, p[n3].pos);
		linear(x43, 1, p[n3].pos, -1, p[n4].pos);
		crossproduct(firstterm, x32, tempji);
		crossproduct(secondterm, x43, tempij);
		linear(pninjpx[1], 1.0/2.0/Ai, firstterm, 1.0/2.0/Aj, secondterm);
		//k=2
		linear(x13, 1, p[n3].pos, -1, p[n1].pos);
		crossproduct(firstterm, x13, tempji);
		numberproduct(pninjpx[2], 1.0/2.0/Ai, firstterm);
		//k=3
		linear(x21, 1, p[n1].pos, -1, p[n2].pos);
		linear(x14, 1, p[n4].pos, -1, p[n1].pos);
		crossproduct(firstterm, x21, tempji);
		crossproduct(secondterm, x14, tempij);
		linear(pninjpx[3], 1.0/2.0/Ai, firstterm, 1.0/2.0/Aj, secondterm);
		//k=4
		linear(x31, 1, p[n1].pos, -1, p[n3].pos);
		crossproduct(firstterm, x31, tempij);
		numberproduct(pninjpx[4], 1.0/2.0/Aj, firstterm);				
	
		//计算Fbk1234,并加到F里面
		for (i=1;i<=4;i++)
		{
			for (j=0;j<=2;j++)
			{
				Fbk1234[i][j]=kb*(l[nl].theta-l[nl].theta0)/sqrt(1-ninj*ninj)*pninjpx[i][j];
			}
		}
		
		for (j=0;j<=2;j++)
		{
			F[n1][j]=F[n1][j]+Fbk1234[1][j];
			F[n2][j]=F[n2][j]+Fbk1234[2][j];
			F[n3][j]=F[n3][j]+Fbk1234[3][j];
			F[n4][j]=F[n4][j]+Fbk1234[4][j];
		}
		
	}
	
}
