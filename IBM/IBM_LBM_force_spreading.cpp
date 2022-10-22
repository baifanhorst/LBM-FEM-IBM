#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"

void noderange_cal(int *noderange, double h, double pos);
double delta_LBM_1D_4(double x);
double delta_LBM_1D_3(double x);

void IBM_LBM_force_spreading(flow &f, particle &p)
{
	int np;
	//对每个节点分配力
	int noderange[3][2]; //插值所在的流场节点，3代表三个方向，2代表最小和最大值
	int i;
	double h=1.5; //插值函数（delta）覆盖的范围，h=1,1.5或2
	int ifx,ify,ifz;
	double delta;
	double xf,yf,zf,xp,yp,zp;
	int NX=f.NX, NY=f.NY, NZ=f.NZ;
		
	
	for (np=1;np<=p.p_num;np++)
	{
		
		//找到该点周围的流场节点，这与采用什么差值函数有关
		noderange_cal(noderange[0], h, p.p[np].pos[0]);
		noderange_cal(noderange[1], h, p.p[np].pos[1]);
		noderange_cal(noderange[2], h, p.p[np].pos[2]-0.5); //z方向是半反射边界，所以与xy方向稍有不同
		
		//cout<<noderange[0][0]<<' '<<noderange[0][1]<<endl;
		//cout<<noderange[1][0]<<' '<<noderange[1][1]<<endl;
		//cout<<noderange[2][0]<<' '<<noderange[2][1]<<endl;
		//cout<<endl;	
	
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
						
						xp=p.p[np].pos[0];
						yp=p.p[np].pos[1];
						zp=p.p[np].pos[2];
						
						
						
						delta=delta_LBM_1D_3(xf-xp)*delta_LBM_1D_3(yf-yp)*delta_LBM_1D_3(zf-zp);
						
						for (i=0;i<=2;i++) //i代表x,y,z
						{
							f.bodyforce[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]=
									f.bodyforce[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]+p.F[np][i]*delta;
						}
					}					
					
					
					
					
					
				}
			}
		}
		
	}
	/*
	int np;
	//对每个节点分配力
	int noderange[3][2]; //插值所在的流场节点，3代表三个方向，2代表最小和最大值
	int i;
	double h=2; //插值函数（delta）覆盖的范围，h=1,1.5或2
	int ifx,ify,ifz;
	double delta;
	double xf,yf,zf,xp,yp,zp;
	int NX=f.NX, NY=f.NY, NZ=f.NZ;
		
	
	for (np=1;np<=p.p_num;np++)
	{
		
		//找到该点周围的流场节点，这与采用什么差值函数有关
		noderange_cal(noderange[0], h, p.p[np].pos[0]);
		noderange_cal(noderange[1], h, p.p[np].pos[1]);
		noderange_cal(noderange[2], h, p.p[np].pos[2]-0.5); //z方向是半反射边界，所以与xy方向稍有不同
		
		//cout<<noderange[0][0]<<' '<<noderange[0][1]<<endl;
		//cout<<noderange[1][0]<<' '<<noderange[1][1]<<endl;
		//cout<<noderange[2][0]<<' '<<noderange[2][1]<<endl;
		//cout<<endl;	
	
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
						
						xp=p.p[np].pos[0];
						yp=p.p[np].pos[1];
						zp=p.p[np].pos[2];
						
						
						
						delta=delta_LBM_1D_4(xf-xp)*delta_LBM_1D_4(yf-yp)*delta_LBM_1D_4(zf-zp);
						
						for (i=0;i<=2;i++) //i代表x,y,z
						{
							f.bodyforce[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]=
									f.bodyforce[(ifx+NX)%NX][(ify+NY)%NY][ifz][i]+p.F[np][i]*delta;
						}
					}					
					
					
					
					
					
				}
			}
		}
		
	}
	*/
}
