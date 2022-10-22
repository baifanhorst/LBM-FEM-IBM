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

void viscosity_init(flow &f, particle &par, double thickness, double fold);


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
	par[0].mesh_read();
	double xave=f.LX/2.0, yave=f.LY/2.0, zave=f.LZ/2.0, R=3.0;
	par[0].pos_init(xave, yave, zave, R);
	
	
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
	
	int t=1, tmax=20000;
	int tend_last=0;
	int step;
	//初始化粘性	
	double vis_thickness=2, vis_fold=5;
	//viscosity_init(f, par[0], vis_thickness, vis_fold);  //续算时去掉
	//续算所需
	tend_last=input_t();
	input_particle(N_par, par);
	f.input();
	
	
	//颗粒速度初始化
	
	
	IBM_LBM_vel_interpolation(f, par[0]);
	IBM_vel_old_set(par[0]);	
	
	

	
	
	
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
	
		viscosity_set(f, par[0], vis_thickness, vis_fold);	
	
	
		
	}
	par[0].inertia_cal();
	par[0].inertia_output();
	par[0].inertia_D();

	f.output();
	f.output_vis2D_y(f.NY/2);
	par[0].output_vtk();
	output_particle(N_par, par);
	output_t(t);
	return 0;
}
