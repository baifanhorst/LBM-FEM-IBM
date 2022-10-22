#include <iostream>
#include <cmath>
using namespace std;
#include "flow.h"

void flow::init(double gx_, double gy_, double gz_, double Uw_top_, double Uw_bottom_, double den0_, double vis0_)
{
	LX=NX; LY=NY; //周期边条，实际上以每个节点为起始都有一段
	LZ=NZ; //上下half-way bounce back边界，上下各多1/2
	gx=gx_; gy=gy_; gz=gz_;
	Uw_top=Uw_top_; //上壁面速度
	Uw_bottom=Uw_bottom_; //下壁面速度
	den0=den0_; //密度
	vis0=vis0_; //粘性
	
	int i,j,k;
	double z; //z方向坐标
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				vis[i][j][k]=vis0;
				den[i][j][k]=den0;
				
				bodyforce[i][j][k][0]=gx;
				bodyforce[i][j][k][1]=gy;
				bodyforce[i][j][k][2]=gz;
			
				z=k+0.5;
				//vel[i][j][k][0]=0.0; //从静止启动
				vel[i][j][k][0]=gx/(2*vis0*den0)*z*(LZ-z)+(Uw_top-Uw_bottom)/LZ*z+Uw_bottom; //从充分发展启动
				vel[i][j][k][1]=0.0;
				vel[i][j][k][2]=0.0;
	
				mark[i][j][k]=0;
			}
	//初始化feq
	
	eq();  

	int q;
	//初始化f,fc
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
				for (q=0;q<=Q-1;q++)
				{
					f[i][j][k][q]=feq[i][j][k][q];
					fc[i][j][k][q]=0.0;
				}
	
	
}


/*
void flow::init(double Gx,double Gy, double Gz, double re)
{

	LX=NX-1; LY=NY-1;//因为NX为节点数，所以段数要-1
	LZ=NZ;//因为采用half-way bounce back，所以要多一段
	//这里有个问题，就是要是从周期性的角度来考虑，一个x周期的长度应该是NX而不是NX-1，y方向也是如此。但是还是按照这里设置LX,LY
	Re=re;
	//泊肃叶流动，上下壁面速度为零
	Uw_top=0;
	Uw_bottom=0;
	//gx，gy，gz中包含密度，跟重力加速度不同
	gx=Gx; gy=Gy; gz=Gz;
	cout<<"LX="<<LX<<endl<<"LY="<<LY<<endl<<"LZ="<<LZ<<' '<<"Re="<<Re<<endl;
	//初始化宏观量
	den0=1.0;
	vis0=sqrt(abs(gx)*(LZ*LZ*LZ)/(8*den0*Re));
	umax=abs(gx)*LZ*LZ/(8*vis0*den0); //这里认为是一个二维流动，即平面流动，即xz平面内的泊肃叶流动
	cout<<"vis_flow="<<vis0<<endl<<"umax="<<umax<<endl;

	int i,j,k;
	double z;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				vis[i][j][k]=vis0;
				den[i][j][k]=den0;
				
				bodyforce[i][j][k][0]=gx;
				bodyforce[i][j][k][1]=gy;
				bodyforce[i][j][k][2]=gz;
			
				z=k+0.5;
				vel[i][j][k][0]=0.0; //从静止启动
				//vel[i][j][k][0]=gx/(2*vis0*den0)*z*(LZ-z); //从充分发展启动
				vel[i][j][k][1]=0.0;
				vel[i][j][k][2]=0.0;

				
	
				mark[i][j][k]=0;
			}
	//初始化feq
	
	eq();  

	int q;
	//初始化f,fc
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
				for (q=0;q<=Q-1;q++)
				{
					f[i][j][k][q]=feq[i][j][k][q];
					fc[i][j][k][q]=0.0;
				}
	
}


void flow::init1(double re)
{
	//这个版本的初始化认为tao=1,进而确定vis0,然后确定gx
	//认为gy=gz=0

	LX=NX-1; LY=NY-1;//因为NX为节点数，所以段数要-1
	LZ=NZ;//因为采用half-way bounce back，所以要多一段
	//这里有个问题，就是要是从周期性的角度来考虑，一个x周期的长度应该是NX而不是NX-1，y方向也是如此。但是还是按照这里设置LX,LY
	Re=re;
	
	//泊肃叶流动，上下壁面速度为零
	Uw_top=0;
	Uw_bottom=0;
	
	//tao=1,vis0=(tao-0.5)/3=1.0/6;
	vis0=1.0/6;
	den0=1.0;
	
	//umax=gx*LZ*LZ/8/vis0; Re=umax*LZ/vis0;
	umax=Re*vis0/LZ;
	gx=umax*8*den0*vis0/LZ/LZ;
	gy=0;
	gz=0;

	cout<<"vis_flow="<<vis0<<endl;
	cout<<"umax="<<umax<<endl;
	cout<<"gx="<<gx<<endl;

	int i,j,k;
	double z;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				vis[i][j][k]=vis0;
				den[i][j][k]=den0;
				
				bodyforce[i][j][k][0]=gx;
				bodyforce[i][j][k][1]=gy;
				bodyforce[i][j][k][2]=gz;
			
				z=k+0.5;
				//vel[i][j][k][0]=0.0; //从静止启动
				vel[i][j][k][0]=gx/(2*vis0*den0)*z*(LZ-z); //从充分发展启动
				vel[i][j][k][1]=0;
				vel[i][j][k][2]=0;

				
	
				mark[i][j][k]=0;
			}
	//初始化feq
	
	eq();  

	int q;
	//初始化f,fc
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
				for (q=0;q<=Q-1;q++)
				{
					f[i][j][k][q]=feq[i][j][k][q];
					fc[i][j][k][q]=0.0;
				}
	
}

void flow::init2(double re)
{
	//这个版本的初始化认为tao=1,进而确定vis0,然后确定gx
	//认为gx=gy=gz=0
	//Couette流动

	LX=NX-1; LY=NY-1;//因为NX为节点数，所以段数要-1
	LZ=NZ;//因为采用half-way bounce back，所以要多一段
	//这里有个问题，就是要是从周期性的角度来考虑，一个x周期的长度应该是NX而不是NX-1，y方向也是如此。但是还是按照这里设置LX,LY
	Re=re;
	
	Uw_bottom=0;
	
	//tao=1,vis0=(tao-0.5)/3=1.0/6;
	vis0=1.0/6;
	den0=1.0;
	
	//umax=gx*LZ*LZ/8/vis0; Re=umax*LZ/vis0;
	Uw_top=Re*vis0/LZ;
	umax=Uw_top;
	gx=0;
	gy=0;
	gz=0;

	cout<<"vis_flow="<<vis0<<endl;
	cout<<"umax="<<umax<<endl;

	int i,j,k;
	double z;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				vis[i][j][k]=vis0;
				den[i][j][k]=den0;
				
				bodyforce[i][j][k][0]=gx;
				bodyforce[i][j][k][1]=gy;
				bodyforce[i][j][k][2]=gz;
			
				z=k+0.5;
				vel[i][j][k][0]=0.0; //从静止启动
				//vel[i][j][k][0]=z/LZ*Uw_top; //从充分发展启动
				vel[i][j][k][1]=0.0;
				vel[i][j][k][2]=0.0;

				
	
				mark[i][j][k]=0;
			}
	//初始化feq
	
	eq();  

	int q;
	//初始化f,fc
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
				for (q=0;q<=Q-1;q++)
				{
					f[i][j][k][q]=feq[i][j][k][q];
					fc[i][j][k][q]=0.0;
				}
	
}

*/


