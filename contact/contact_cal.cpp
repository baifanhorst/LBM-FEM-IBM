#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include <cmath>
#include <stdio.h>
#include <omp.h>
//double d_p_particle_cal(double *pos, particle &p);

void contact_cal(double &contact_d, particle &par0, particle &par1, double &contact_d_crit)
{
	int ip0,ip1;
	double d;
	double pos0[3],pos1[3];
	int k;
	int ipe;
	int ie;
	int ip;

	//关于接触标志，有两种
	//(1)节点的接触标志 （2）单元的接触标志	
	//由于后面算法的需要，对于两种标志，均认为0代表接触，1代表不接触
	
	//接触标志初始化（置1）
	//节点接触标志初始化
	#pragma omp parallel for
	for (ip=1;ip<=par0.p_num;ip++)
	{
		par0.p[ip].mark_contact=1;
	}
	#pragma omp parallel for
	for (ip=1;ip<=par1.p_num;ip++)
	{
		par1.p[ip].mark_contact=1;
	}
 	//单元接触标志初始化
	#pragma omp parallel for
	for (ie=1;ie<=par0.e_num;ie++)
	{
		par0.e[ie].mark_contact=1;
	}
	#pragma omp parallel for
	for (ie=1;ie<=par1.e_num;ie++)
	{
		par1.e[ie].mark_contact=1;
	}
	//接触面积置零
	par0.contact_area=0;
	par1.contact_area=0;
	
	//给一个最短接触距离的初值，以便后面比较
	ip0=1; ip1=1;
	d=0;
	for (k=0;k<=2;k++)
	{
		d=d+(par0.p[ip0].pos[k]-par1.p[ip1].pos[k])*(par0.p[ip0].pos[k]-par1.p[ip1].pos[k]);
	}
	d=sqrt(d);		
	contact_d=d;
	
	
	//求两细胞最短距离 判断节点接触
	for (ip0=1;ip0<=par0.p_num;ip0++)
	{
		for (ip1=1;ip1<=par1.p_num;ip1++)
		{
			//计算两节点之间的距离
			d=0;
			for (k=0;k<=2;k++)
			{
				d=d+(par0.p[ip0].pos[k]-par1.p[ip1].pos[k])*(par0.p[ip0].pos[k]-par1.p[ip1].pos[k]);
			}
			d=sqrt(d);
			//求两细胞距离
			if (d<=contact_d)
			{
				//认为最短接触距离为最近的两个节点之间的距离
				contact_d=d;
				
			}
			if (d<=contact_d_crit)
			{
				//设置节点接触标志为0
				par0.p[ip0].mark_contact*=0;
				par1.p[ip1].mark_contact*=0;
			}	
		}
	}
	//判断单元接触
	for (ip=1;ip<=par0.p_num;ip++)
	{
		if (par0.p[ip].mark_contact==0)
		{
			for (ipe=0;ipe<=par0.p[ip].e_num-1;ipe++)
			{
				ie=par0.p[ip].e_no[ipe];
				par0.e[ie].mark_contact*=0;
			}
		}
	}
	for (ip=1;ip<=par1.p_num;ip++)
	{
		if (par1.p[ip].mark_contact==0)
		{
			for (ipe=0;ipe<=par1.p[ip].e_num-1;ipe++)
			{
				ie=par1.p[ip].e_no[ipe];
				par1.e[ie].mark_contact*=0;
			}
		}
	}
	//求接触面积
	for (ie=1;ie<=par0.e_num;ie++)
	{
		par0.contact_area+=par0.e[ie].A*(1-par0.e[ie].mark_contact); //由于接触时mark为0，而这里得乘以(1-mark)
	}
	for (ie=1;ie<=par0.e_num;ie++)
	{
		par1.contact_area+=par1.e[ie].A*(1-par1.e[ie].mark_contact);
	}
	
	
	
}
