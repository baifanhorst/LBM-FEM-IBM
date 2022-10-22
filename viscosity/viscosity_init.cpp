#include <iostream>
using namespace std;

#include "../flow/flow.h"
#include "../particle/particle.h"

#include <cmath>
//openmp
#include <stdio.h>
#include <omp.h>


char PointPolyIn(double *q, particle &par, flow &f);

void viscosity_init(flow &f, particle &par, double thickness, double fold)
{
	int ne,i,j,k;
	int ip;
	int NX=f.NX,NY=f.NY,NZ=f.NZ;
	int ne1;
	
	//计算单元中心位置，生成射线时候要用
	for (ne=1;ne<=par.e_num;ne++)
	{
		par.e[ne].pos_center_abs_cal();
	}
	par.pos_rangebox_cal(); //计算par的坐标范围，用于生成射线
	//计算每个单元坐标范围
	for (ne=1;ne<=par.e_num;ne++)
	{
		par.e[ne].pos_range_cal();
	}
	
	
	double pos_flowpoint[3]; //被考察的流场节点坐标
	//double theta;
	double vis_out=f.vis0, vis_in=fold*f.vis0;
	char mark_PointPolyIn; //流场节点是否在多面体内部的标志
	
	
	int imin,imax,jmin,jmax,kmin,kmax;
	imin=ceil(par.pos_min[0]-thickness);
	imax=floor(par.pos_max[0]+thickness);
	jmin=ceil(par.pos_min[1]-thickness);
	jmax=floor(par.pos_max[1]+thickness);
	kmin=ceil(par.pos_min[2]-thickness);
	kmax=floor(par.pos_max[2]+thickness);
	
	kmin=max(kmin,0);  //z方向不能越界
	kmax=min(kmax,NZ);
		
	for (i=imin;i<=imax;i++)
	{
		for (j=jmin;j<=jmax;j++)
		{
			for (k=kmin;k<=kmax;k++)
			{
				pos_flowpoint[0]=i;
				pos_flowpoint[1]=j;
				pos_flowpoint[2]=k+0.5;
					
				mark_PointPolyIn=PointPolyIn(pos_flowpoint, par, f);
				//给粘性赋值
				if (mark_PointPolyIn=='o')
				{
					f.vis[(i+NX)%NX][(j+NY)%NY][k]=vis_out;
				}
				else
				{
					f.vis[(i+NX)%NX][(j+NY)%NY][k]=vis_in;
				}			
				
					
			}
		}
	}
		
	
		
}


















