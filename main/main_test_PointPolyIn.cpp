#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include "../flow/flow.h"
#include <cmath>

void IBM_LBM_force_spreading(flow &f, particle &p);
void IBM_LBM_vel_interpolation(flow &f, particle &par);
void IBM_vel_old_set(particle &par);
void IBM_LBM_particle_pos_update(particle &par);
void IBM_LBM_particle_pos_adjust(flow &f, particle &par);
void repulse_wall(flow &f, particle &par, double k_repulse, double exponent_repulse, double R_repulse);
void output_particle(int N_par, particle *par);
void input_particle(int N_par, particle *par);

int input_t();
void output_t(int t);


void viscosity_set(flow &f, particle &p, double thickness, double fold);
void PointPolyIn(double *q, particle &par);


int main()
{
	//流场 分配空间
	int nx=30, ny=30, nz=30;
	flow f(nx,ny,nz);
	//流场 C流初始化
	double Re=0.02;
	double LZ=nz;	
	double gx=0.0, gy=0.0, gz=0.0, uw_top=1.0/180, uw_bottom=-1.0/180, den0=1.0, vis0=1.0/6;
	cout<<"tao="<<3*vis0+0.5<<endl; //测试tao是否小于一
	f.init(gx, gy, gz, uw_top, uw_bottom, den0, vis0);
	
	//细胞初始化
	const int N_par=1;
	particle par[N_par];
	//par[0].mesh_read();
	//double xave=f.LX/2.0, yave=f.LY/2.0, zave=f.LZ/2.0, R=3.0;
	//par[0].pos_init(xave, yave, zave, R);
	
	
	

	
	//四面体设置
	par[0].p_num=4; par[0].l_num=6; par[0].e_num=4;
	par[0].mesh_allocate();
	par[0].p[1].pos[0]=15; par[0].p[1].pos[1]=15; par[0].p[1].pos[2]=15+0.5; 
	par[0].p[2].pos[0]=17; par[0].p[2].pos[1]=15; par[0].p[2].pos[2]=15+0.5; 
	par[0].p[3].pos[0]=15; par[0].p[3].pos[1]=17; par[0].p[3].pos[2]=15+0.5; 
	par[0].p[4].pos[0]=15; par[0].p[4].pos[1]=15; par[0].p[4].pos[2]=15+2+0.5; 
	
	par[0].l[1].p_no[0]=1; par[0].l[1].p_no[1]=2;
	par[0].l[2].p_no[0]=1; par[0].l[2].p_no[1]=3;
	par[0].l[3].p_no[0]=1; par[0].l[3].p_no[1]=4;
	par[0].l[4].p_no[0]=2; par[0].l[4].p_no[1]=3;
	par[0].l[5].p_no[0]=3; par[0].l[5].p_no[1]=4;
	par[0].l[6].p_no[0]=4; par[0].l[6].p_no[1]=2;
	
	par[0].l[1].e_no[0]=1; par[0].l[1].e_no[1]=3;
	par[0].l[2].e_no[0]=1; par[0].l[2].e_no[1]=2;
	par[0].l[3].e_no[0]=2; par[0].l[3].e_no[1]=3;
	par[0].l[4].e_no[0]=1; par[0].l[4].e_no[1]=4;
	par[0].l[5].e_no[0]=2; par[0].l[5].e_no[1]=4;
	par[0].l[6].e_no[0]=3; par[0].l[6].e_no[1]=4;
	
	par[0].e[1].p_no[0]=1; par[0].e[1].p_no[1]=3; par[0].e[1].p_no[2]=2;
	par[0].e[2].p_no[0]=1; par[0].e[2].p_no[1]=4; par[0].e[2].p_no[2]=3;
	par[0].e[3].p_no[0]=1; par[0].e[3].p_no[1]=2; par[0].e[3].p_no[2]=4;
	par[0].e[4].p_no[0]=2; par[0].e[4].p_no[1]=3; par[0].e[4].p_no[2]=4;
	
	
	//设置单元节点坐标
	par[0].e_pointpos_set();
	//初始化相关几何参数
	par[0].parameter_init();
	//设置计算Fb时编号对应的节点	
	par[0].F_Fb_setnum();
	//弹性常数
	//par[0].ks=1.8*pow(10,-4); par[0].k_alpha=2*par[0].ks; par[0].kb=0.2*par[0].ks; par[0].ka=10*par[0].ks; 
	//par[0].kv=10*par[0].ks; //暂时这么设，可能不合理

	par[0].ks=1.0/54.0; par[0].k_alpha=par[0].ks; par[0].kb=0; par[0].ka=0; 
	par[0].kv=0; //暂时这么设，可能不合理
	
	
	//为力分配存储空间
	par[0].F_allocate();	
	
	
	//wall repulse所需参数
	double k_repulse=0.001, exponent_repulse=2.0, R_repulse=0.5;
	
	int t=1, tmax=1;
	int tend_last=0;
	int step;

	//续算所需
	//tend_last=input_t();
	//input_particle(N_par, par);
	//f.input();
	
	
	//颗粒速度初始化
	
	
	IBM_LBM_vel_interpolation(f, par[0]);
	IBM_vel_old_set(par[0]);	

	
	double q[3]={19,19,19.5};
	
	int i,j,k;
	#pragma omp parallel for private(i,j,k)
	for (i=0;i<=f.NX-1;i++)
	{
		for (j=0;j<=f.NY-1;j++)
		{
			for (k=0;k<=f.NZ-1;k++)
			{
				f.mark[i][j][k]=0;
			}
		}
	}
	int ne;
	//计算单元中心位置，生成射线时候要用
	for (ne=1;ne<=par[0].e_num;ne++)
	{
		par[0].e[ne].pos_center_abs_cal();
	}
	par[0].pos_rangebox_cal(); //计算par的坐标范围，用于生成射线
	//计算每个单元坐标范围
	for (ne=1;ne<=par[0].e_num;ne++)
	{
		par[0].e[ne].pos_range_cal();
	}	
	
	
	
	

	PointPolyIn(q, par[0]);
	
	/*
	for (step=1;step<=tmax;step++)
	{
		//if (t%10==0)
		t=step+tend_last;
		cout<<"t="<<t<<endl;
		
		//由于将细胞力叠加在上面，故每次置零
		f.set_bodyforce();
		//计算细胞节点力
		par[0].F_cal();
		//计算wall repulse
		repulse_wall(f, par[0], k_repulse, exponent_repulse, R_repulse);
		
		//节点力分配
		IBM_LBM_force_spreading(f, par[0]);
		


		
		f.eq();
		f.collision();
		f.streaming();
		f.macro();
		
		IBM_vel_old_set(par[0]);
		IBM_LBM_vel_interpolation(f, par[0]);
		IBM_LBM_particle_pos_update(par[0]);
		IBM_LBM_particle_pos_adjust(f, par[0]);
		cout<<"particle average position x "<<par[0].pos_ave[0]<<endl;
		cout<<"particle volume "<<par[0].V<<endl;
		
	}
	*/
	
	f.output();
	par[0].output_vtk();
	output_particle(N_par, par);
	output_t(t);
	return 0;
}
