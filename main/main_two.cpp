#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include "../flow/flow.h"
#include <cmath>
#include <ctime> //记录运行时间
#include <fstream>

void IBM_LBM_force_spreading(flow &f, particle &p);
void IBM_LBM_vel_interpolation(flow &f, particle &par);
void IBM_vel_old_set(particle &par);
void IBM_LBM_particle_pos_update(particle &par);
void IBM_LBM_particle_pos_adjust(flow &f, particle &par);
void repulse_wall(flow &f, particle &par, double k_repulse, double exponent_repulse, double R_repulse);
void output_particle(int N_par, particle *par);
void input_particle(int N_par, particle *par);
void repulse_cell(flow &f, particle &par1, particle &par2, double k_repulse, double exponent_repulse, double R_repulse);

int input_t();
void output_t(int t);


int main()
{
	//流场 分配空间
	int nx=10, ny=10, nz=10;
	flow f(nx,ny,nz);
	//流场 C流初始化
	double Re=0.23;
	double LZ=nz;	
	double gx=0.0, gy=0.0, gz=0.0, uw_top=6.4*pow(10,-4), uw_bottom=0.0, den0=1.0, vis0=fabs(uw_top-uw_bottom)*LZ/Re;
	cout<<"tao="<<3*vis0+0.5<<endl; //测试tao是否小于一
	f.init(gx, gy, gz, uw_top, uw_bottom, den0, vis0);
	
	//细胞初始化
	const int N_par=2;
	particle par[N_par];
	par[0].mesh_read();
	par[1].mesh_read();
	double xave=f.LX/2.0+1.0, yave=f.LY/2.0, zave=f.LZ/2.0, R=1;
	par[0].pos_init(xave, yave, zave, R);
	       xave=f.LX/2.0-1.0, yave=f.LY/2.0, zave=f.LZ/2.0, R=1;
	par[1].pos_init(xave, yave, zave, R);
	
	
	
	
	
	
	
	//设置单元节点坐标
	par[0].e_pointpos_set();
	par[1].e_pointpos_set();
	//初始化相关几何参数
	par[0].parameter_init();
	par[1].parameter_init();
	//设置计算Fb时编号对应的节点	
	par[0].F_Fb_setnum();
	par[1].F_Fb_setnum();
	//弹性常数
	par[0].ks=1.8*pow(10,-4); par[0].k_alpha=2*par[0].ks; par[0].kb=0.2*par[0].ks; par[0].ka=10*par[0].ks; 
	par[0].kv=10*par[0].ks; //暂时这么设，可能不合理
	par[1].ks=1.8*pow(10,-4); par[1].k_alpha=2*par[1].ks; par[1].kb=0.2*par[1].ks; par[1].ka=10*par[1].ks; 
	par[1].kv=10*par[1].ks; //暂时这么设，可能不合理
	
	
	
	//为力分配存储空间
	par[0].F_allocate();	
	par[1].F_allocate();
	
	//wall repulse所需参数
	double k_repulse=0.01, exponent_repulse=2.0, R_repulse=0.5;
	
	int t=1, tmax=30000;
	int tend_last=0;
	int step;

	//续算所需
	tend_last=input_t();
	input_particle(N_par, par);
	f.input();
	
	
	//颗粒速度初始化
	
	
	IBM_LBM_vel_interpolation(f, par[0]);
	IBM_vel_old_set(par[0]);
	
	IBM_LBM_vel_interpolation(f, par[1]);
	IBM_vel_old_set(par[1]);	


	
	//记录主循环运行时间
	time_t time_start, time_end;
	time(&time_start);
		
	
	for (step=1;step<=tmax;step++)
	{
		//if (t%10==0)
		t=step+tend_last;
		cout<<"t="<<t<<endl;
		
		//由于将细胞力叠加在上面，故每次置零
		f.set_bodyforce();
		//计算细胞节点力
		par[0].F_cal();
		par[1].F_cal();
		//计算wall repulse
		repulse_wall(f, par[0], k_repulse, exponent_repulse, R_repulse);
		repulse_wall(f, par[1], k_repulse, exponent_repulse, R_repulse);
		//计算cell-cell repulse
		//repulse_cell(f, par[0], par[1], k_repulse, exponent_repulse, R_repulse);		
	
	
		//节点力分配
		IBM_LBM_force_spreading(f, par[0]);
		IBM_LBM_force_spreading(f, par[1]);
		


		
		f.eq();
		f.collision();
		f.streaming();
		f.macro();
		
		IBM_vel_old_set(par[0]);
		IBM_LBM_vel_interpolation(f, par[0]);
		IBM_LBM_particle_pos_update(par[0]);
		IBM_LBM_particle_pos_adjust(f, par[0]);
		cout<<"particle average position "<<par[0].pos_ave[0]<<' '<<par[0].pos_ave[1]<<' '<<par[0].pos_ave[2]<<' '<<endl;
		
		IBM_vel_old_set(par[1]);
		IBM_LBM_vel_interpolation(f, par[1]);
		IBM_LBM_particle_pos_update(par[1]);
		IBM_LBM_particle_pos_adjust(f, par[1]);
		cout<<"particle average position "<<par[1].pos_ave[0]<<' '<<par[1].pos_ave[1]<<' '<<par[1].pos_ave[2]<<' '<<endl;
		
		cout<<"particle average position dif "<<par[0].pos_ave[0]-par[1].pos_ave[0]<<' '
			<<par[0].pos_ave[1]-par[1].pos_ave[1]<<' '<<par[0].pos_ave[2]-par[1].pos_ave[2]<<endl;
		
		
	}
		
	time(&time_end);
	cout<<"time_start: "<<ctime(&time_start);
	cout<<"time_end: "<<ctime(&time_end);
	
	ofstream fout;
	fout.open("./result/time/mainlooptime.txt",ios::out);
	fout<<"time_start: "<<ctime(&time_start);
	fout<<"time_end: "<<ctime(&time_end);
	fout.close();
	
	
		
	f.output();
	par[0].output_vtk_multiple(0);
	par[1].output_vtk_multiple(1);
	output_particle(N_par, par);
	output_t(t);
	
	return 0;
}
