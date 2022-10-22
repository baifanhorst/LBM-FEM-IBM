#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>

void normalize(double *e, double *a);
void crossproduct(double *p, double *a, double *b);


void particle::F_Fs3D_convert(double **Fs2D, int ne)
{
	//求x轴y轴方向
	//01的向量和方向
	double r01[3],ex[3]; 
	int j;
	for (j=0;j<=2;j++)
	{
		r01[j]=e[ne].pos[1][j]-e[ne].pos[0][j];
	}
	normalize(ex,r01);
	//02向量
	double r02[3];
	for (j=0;j<=2;j++)
	{
		r02[j]=e[ne].pos[2][j]-e[ne].pos[0][j];
	}
	//z方向 z方向单位向量
	double rz[3],ez[3];
	crossproduct(rz,r01,r02);
	normalize(ez,rz);
	//y方向单位向量
	double ey[3];
	crossproduct(ey,ez,ex);
	
	//节点编号
	int i;
	//对每个节点转换Fs
	//单元e的第i个节点对应的整体节点编号
	int np;
	for (i=0;i<=2;i++)
	{
		np=e[ne].p_no[i];
		for (j=0;j<=2;j++)
		{
			F[np][j]=F[np][j]+Fs2D[i][0]*ex[j]+Fs2D[i][1]*ey[j];
		}
	}
}
