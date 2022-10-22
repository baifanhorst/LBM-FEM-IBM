#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"

void noderange_cal(int *noderange, double h, double pos);
double delta_LBM_1D_4(double x);
double delta_LBM_1D_3(double x);

void IBM_LBM_vel_interpolation(flow &f, particle &par)
{
	int np;
	int noderange[3][2]; //插值所在的流场节点，3代表三个方向，2代表最小和最大值
	int i;
	double h=1.5; //插值函数（delta）覆盖的范围，h=1,1.5或2
	int ifx,ify,ifz;
	double delta;
	double xf,yf,zf,xp,yp,zp;
	int NX=f.NX, NY=f.NY, NZ=f.NZ;
	double sum_delta; //应付边界的差值，这个与力分配不同，对于流场外的节点，力不必往那里分配，但是若只用流场内的节点做速度差值，会少一些
	
	for (np=1;np<=par.p_num;np++)
	{	
		for (i=0;i<=2;i++)
		{
			par.p[np].vel[i]=0;
		}		
		//找到该点周围的流场节点，这与采用什么差值函数有关
		noderange_cal(noderange[0], h, par.p[np].pos[0]);
		noderange_cal(noderange[1], h, par.p[np].pos[1]);
		noderange_cal(noderange[2], h, par.p[np].pos[2]-0.5); //z方向是半反射边界，所以与xy方向稍有不同
	
		
		sum_delta=0;
		for (ifx=noderange[0][0];ifx<=noderange[0][1];ifx++)
		{
			for (ify=noderange[1][0];ify<=noderange[1][1];ify++)
			{
				for (ifz=noderange[2][0];ifz<=noderange[2][1];ifz++)
				{
					if ((ifz>=0)&&(ifz<=NZ-1))
					{
						xf=ifx;
						yf=ify;
						zf=ifz+0.5;
						
						xp=par.p[np].pos[0];
						yp=par.p[np].pos[1];
						zp=par.p[np].pos[2];
						
						
						
						delta=delta_LBM_1D_3(xf-xp)*delta_LBM_1D_3(yf-yp)*delta_LBM_1D_3(zf-zp);
						sum_delta=sum_delta+delta;
						for (i=0;i<=2;i++) //i代表x,y,z
						{
							par.p[np].vel[i]=par.p[np].vel[i]
									+f.vel[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]*delta;
						}
					}									
				}
			}
		}
		par.p[np].vel[i]=par.p[np].vel[i]/sum_delta;
	}
	/*
	int np;
	int noderange[3][2]; //插值所在的流场节点，3代表三个方向，2代表最小和最大值
	int i;
	double h=2; //插值函数（delta）覆盖的范围，h=1,1.5或2
	int ifx,ify,ifz;
	double delta;
	double xf,yf,zf,xp,yp,zp;
	int NX=f.NX, NY=f.NY, NZ=f.NZ;
	double sum_delta; //应付边界的差值，这个与力分配不同，对于流场外的节点，力不必往那里分配，但是若只用流场内的节点做速度差值，会少一些
	
	for (np=1;np<=par.p_num;np++)
	{	
		for (i=0;i<=2;i++)
		{
			par.p[np].vel[i]=0;
		}		
		//找到该点周围的流场节点，这与采用什么差值函数有关
		noderange_cal(noderange[0], h, par.p[np].pos[0]);
		noderange_cal(noderange[1], h, par.p[np].pos[1]);
		noderange_cal(noderange[2], h, par.p[np].pos[2]-0.5); //z方向是半反射边界，所以与xy方向稍有不同
	
		
		sum_delta=0;
		for (ifx=noderange[0][0];ifx<=noderange[0][1];ifx++)
		{
			for (ify=noderange[1][0];ify<=noderange[1][1];ify++)
			{
				for (ifz=noderange[2][0];ifz<=noderange[2][1];ifz++)
				{
					if ((ifz>=0)&&(ifz<=NZ-1))
					{
						xf=ifx;
						yf=ify;
						zf=ifz+0.5;
						
						xp=par.p[np].pos[0];
						yp=par.p[np].pos[1];
						zp=par.p[np].pos[2];
						
						
						
						delta=delta_LBM_1D_4(xf-xp)*delta_LBM_1D_4(yf-yp)*delta_LBM_1D_4(zf-zp);
						sum_delta=sum_delta+delta;
						for (i=0;i<=2;i++) //i代表x,y,z
						{
							par.p[np].vel[i]=par.p[np].vel[i]
									+f.vel[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]*delta;
						}
					}									
				}
			}
		}
		par.p[np].vel[i]=par.p[np].vel[i]/sum_delta;
	}
	*/
	
}

