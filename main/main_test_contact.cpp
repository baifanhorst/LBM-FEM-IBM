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

int input_t();
void output_t(int t);


void viscosity_set(flow &f, particle &p, double thickness, double fold);

void viscosity_init(flow &f, particle &par, double thickness, double fold);

void contact_cal(double &contact_d, double &contact_area, particle &p0, particle &p1, double &contact_d_crit);

double d_p_element_cal(double *pos, element &e);

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
	double xave, yave, zave, R=3;
	const int N_par=2;
	particle par[N_par];
	
	par[0].p_num=4; par[0].l_num=6; par[0].e_num=4;
	par[0].mesh_allocate();
	
	par[0].p[1].pos[0]=15; par[0].p[1].pos[1]=15; par[0].p[1].pos[2]=15+0.5; 
	par[0].p[2].pos[0]=17; par[0].p[2].pos[1]=15; par[0].p[2].pos[2]=15+0.5; 
	par[0].p[3].pos[0]=15; par[0].p[3].pos[1]=17; par[0].p[3].pos[2]=15+0.5; 
	par[0].p[4].pos[0]=15; par[0].p[4].pos[1]=15; par[0].p[4].pos[2]=15+2+0.5; 
	
	
	par[0].p[1].e_no[0]=1; par[0].p[1].e_no[1]=2; par[0].p[1].e_no[2]=3;
	par[0].p[2].e_no[0]=1; par[0].p[2].e_no[1]=3; par[0].p[2].e_no[2]=4;
	par[0].p[3].e_no[0]=1; par[0].p[3].e_no[1]=2; par[0].p[3].e_no[2]=4;
	par[0].p[4].e_no[0]=2; par[0].p[4].e_no[1]=3; par[0].p[4].e_no[2]=4;
	
	
	
	
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
	
	
	
	par[1].p_num=4; par[1].l_num=6; par[1].e_num=4;
	par[1].mesh_allocate();
	par[1].p[1].pos[0]=15; par[1].p[1].pos[1]=15; par[1].p[1].pos[2]=3+15+0.5; 
	par[1].p[2].pos[0]=17; par[1].p[2].pos[1]=15; par[1].p[2].pos[2]=3+15+0.5; 
	par[1].p[3].pos[0]=15; par[1].p[3].pos[1]=17; par[1].p[3].pos[2]=3+15+0.5; 
	par[1].p[4].pos[0]=15; par[1].p[4].pos[1]=15; par[1].p[4].pos[2]=3+15+2+0.5; 
	
	par[1].p[1].e_no[0]=1; par[1].p[1].e_no[1]=2; par[1].p[1].e_no[2]=3;
	par[1].p[2].e_no[0]=1; par[1].p[2].e_no[1]=3; par[1].p[2].e_no[2]=4;
	par[1].p[3].e_no[0]=1; par[1].p[3].e_no[1]=2; par[1].p[3].e_no[2]=4;
	par[1].p[4].e_no[0]=2; par[1].p[4].e_no[1]=3; par[1].p[4].e_no[2]=4;	
	
	
	
	
	
	par[1].l[1].p_no[0]=1; par[1].l[1].p_no[1]=2;
	par[1].l[2].p_no[0]=1; par[1].l[2].p_no[1]=3;
	par[1].l[3].p_no[0]=1; par[1].l[3].p_no[1]=4;
	par[1].l[4].p_no[0]=2; par[1].l[4].p_no[1]=3;
	par[1].l[5].p_no[0]=3; par[1].l[5].p_no[1]=4;
	par[1].l[6].p_no[0]=4; par[1].l[6].p_no[1]=2;
	
	par[1].l[1].e_no[0]=1; par[1].l[1].e_no[1]=3;
	par[1].l[2].e_no[0]=1; par[1].l[2].e_no[1]=2;
	par[1].l[3].e_no[0]=2; par[1].l[3].e_no[1]=3;
	par[1].l[4].e_no[0]=1; par[1].l[4].e_no[1]=4;
	par[1].l[5].e_no[0]=2; par[1].l[5].e_no[1]=4;
	par[1].l[6].e_no[0]=3; par[1].l[6].e_no[1]=4;
	
	par[1].e[1].p_no[0]=1; par[1].e[1].p_no[1]=3; par[1].e[1].p_no[2]=2;
	par[1].e[2].p_no[0]=1; par[1].e[2].p_no[1]=4; par[1].e[2].p_no[2]=3;
	par[1].e[3].p_no[0]=1; par[1].e[3].p_no[1]=2; par[1].e[3].p_no[2]=4;
	par[1].e[4].p_no[0]=2; par[1].e[4].p_no[1]=3; par[1].e[4].p_no[2]=4;
	
	
	
	


	int i;
	
	
	
	for (i=0;i<=N_par-1;i++)
	{		
		//设置单元节点坐标
		par[i].e_pointpos_set();
		
		
		//初始化相关几何参数
		par[i].parameter_init(); 
		//设置计算Fb时编号对应的节点	
		par[i].F_Fb_setnum();
		//弹性常数
		par[i].ks=1.0/54.0; par[i].k_alpha=par[i].ks; par[i].kb=0; par[i].ka=0; 
		par[i].kv=0; //暂时这么设，可能不合理
		
		//为力分配存储空间
		par[i].F_allocate();
		
	}
	
	//cout<<"test d_p_element"<<endl;
	//double pos[3]={14,15,15.5};
	//double d_p_e;
	//d_p_e=d_p_element_cal(pos, par[0].e[4]);
	//cout<<"par[0].e[3].pos[0] "<<par[0].e[3].pos[0][0]<<' '<<par[0].e[3].pos[0][1]<<' '<<par[0].e[3].pos[0][2]<<endl;
	//cout<<"par[0].e[3].pos[1] "<<par[0].e[3].pos[1][0]<<' '<<par[0].e[3].pos[1][1]<<' '<<par[0].e[3].pos[1][2]<<endl;
	//cout<<"par[0].e[3].pos[2] "<<par[0].e[3].pos[2][0]<<' '<<par[0].e[3].pos[2][1]<<' '<<par[0].e[3].pos[2][2]<<endl;
	//cout<<"d_p_e="<<d_p_e<<endl;
	
	//wall repulse所需参数
	double k_repulse=0.001, exponent_repulse=2.0, R_repulse=0.5;
	
	int t=1, tmax=0;
	int tend_last=0;
	int step;
	//初始化粘性
		
	double vis_thickness=2, vis_fold=5;
	//续算时去掉
	
	for (i=0;i<=N_par-1;i++)
	{	
		viscosity_init(f, par[i], vis_thickness, vis_fold);  
	}
	
	//续算所需
	//tend_last=input_t();
	//input_particle(N_par, par);
	//f.input();
	
	
	//颗粒速度初始化
	
	for (i=0;i<=N_par-1;i++)
	{
		IBM_LBM_vel_interpolation(f, par[i]);
		IBM_vel_old_set(par[i]);	
	}
	

	//记录主循环运行时间
	time_t time_start, time_end;
	time(&time_start);
	

	//主循环记录cell的pos，D等等
	ofstream fout0,fout1;
	fout0.open("./result/result_particle0_pos_D_contact.txt",ios::out);
	fout1.open("./result/result_particle1_pos_D_contact.txt",ios::out);
	//记录哪些时间点是contact的，以及每时刻的contact area
	ofstream fout_contact_time, fout_contact_area;
	fout_contact_time.open("./result/result_contact_time.txt",ios::out);
	fout_contact_area.open("./result/result_contact_area.txt",ios::out);
	
	double contact_d, contact_area, contact_d_crit=2; //两cell间距，接触面积，接触所需最小距离

	contact_cal(contact_d, contact_area, par[0], par[1], contact_d_crit);

	
	for (step=1;step<=tmax;step++)
	{
		//if (t%10==0)
		t=step+tend_last;
		cout<<"t="<<t<<endl;
		
		//由于将细胞力叠加在上面，故每次置零
		f.set_bodyforce();
		
		
		for (i=0;i<=N_par-1;i++)
		{
			//计算细胞节点力
			par[i].F_cal();
			//计算wall repulse
			//repulse_wall(f, par[i], k_repulse, exponent_repulse, R_repulse);
		
			//节点力分配
			IBM_LBM_force_spreading(f, par[i]);
		}


		
		f.eq();
		f.collision();
		f.streaming();
		f.macro();
		
		for (i=0;i<=N_par-1;i++)
		{
			IBM_vel_old_set(par[i]);
			IBM_LBM_vel_interpolation(f, par[i]);
			IBM_LBM_particle_pos_update(par[i]);
			IBM_LBM_particle_pos_adjust(f, par[i]);
			cout<<"particle average position x "<<par[i].pos_ave[0]<<endl;
			cout<<"particle volume "<<par[i].V<<endl;
		}
		/*
		for (i=0;i<=N_par-1;i++)
		{
			viscosity_set(f, par[i], vis_thickness, vis_fold);	
		}
		*/
		//每隔一段时间输出一下位置和变形的信息
		if (t%100==0)
		{
			for (i=0;i<=N_par-1;i++)
			{
				par[i].inertia_cal();
				par[i].inertia_D();
			}
			fout0<<t<<' '<<par[0].pos_ave[0]<<' '<<par[0].pos_ave[1]<<' '<<par[0].pos_ave[2]<<' '<<par[0].D<<endl;
			fout1<<t<<' '<<par[1].pos_ave[0]<<' '<<par[1].pos_ave[1]<<' '<<par[1].pos_ave[2]<<' '<<par[1].D<<endl;
		}
		//记录contact信息
		
		//contact_cal(contact_d, contact_area, par[0], par[1], contact_d_crit);
	}
	
	
	
	fout0.close();
	fout1.close();
	
	fout_contact_time.close();
	fout_contact_area.close();
	
	time(&time_end);
	cout<<"time_start: "<<ctime(&time_start);
	cout<<"time_end: "<<ctime(&time_end);	
	
	ofstream fout;
	fout.open("./result/time/mainlooptime.txt",ios::out);
	fout<<"time_start: "<<ctime(&time_start);
	fout<<"time_end: "<<ctime(&time_end);
	fout.close();	
	

	f.output();
	f.output_vis2D_y(f.NY/2);
	
	output_particle(N_par, par);
	output_t(t);
	
	
	
	for (i=0;i<=N_par-1;i++)
	{
		par[i].inertia_cal();
		par[i].inertia_output();
		par[i].inertia_D();
		par[i].output_vtk_multiple(i);
	}
	return 0;
}
