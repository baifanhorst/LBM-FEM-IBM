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

void contact_cal(double &contact_d, particle &p0, particle &p1, double &contact_d_crit);


int main()
{
	const double PI=3.141592653;
	//流场 分配空间
	//把R, Re, Ca放在最前面，便于修改
	double R=9; //初始细胞半径
	double Re=0.02;
	double Ca=0.01;
	//位置较低的细胞与底面的间距
	double gap_wall=0.3*R;
	//细胞位置（这里放在这么靠前的位置是因为流场设置依赖于细胞的初始位置）
	double xave, yave, zave;
	double dx0,dy0,dz0;
	dx0=4.0*R;  dy0=0; dz0=0.5*R;
	//流场尺寸
	int nx=20*int(R), ny=10*int(R), nz=10*int(R);
	flow f(nx,ny,nz);
	//流场 C流初始化
	double LZ=nz;
	double vis0=1.0/6;
	double shear_rate=Re*vis0/R/R;	
	double gx=0.0, gy=0.0, gz=0.0, uw_top=(LZ-(gap_wall+R+dz0/2.0))*shear_rate, uw_bottom=-(gap_wall+R+dz0/2.0)*shear_rate, den0=1.0;     
	cout<<"tao="<<3*vis0+0.5<<endl; //测试tao是否小于一
	f.init(gx, gy, gz, uw_top, uw_bottom, den0, vis0);
	//细胞初始化
	const int N_par=2;
	particle par[N_par];
	xave=f.LX/2.0-dx0/2.0, yave=f.LY/2.0+dy0/2.0;
	zave=gap_wall+R+dz0;
	par[0].mesh_read();
	//par[0].mesh_PMN_convert();
	//cout<<"par[0].p[1].pos="<<par[0].p[1].pos[0]<<' '<<par[0].p[1].pos[1]<<' '<<par[0].p[1].pos[2]<<endl;
	//double pos_penalty[3]={15,15,1};
	//double k_PMN=0.1; 
	//int np_PMN=1;
	par[0].pos_init(xave, yave, zave, R);
	
	par[1].mesh_read();
	xave=f.LX/2.0+dx0/2.0, yave=f.LY/2.0-dy0/2.0;
	zave=gap_wall+R;
	
	par[1].pos_init(xave, yave, zave, R);

	
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
		par[i].ks=den0*vis0*shear_rate*R/Ca; par[i].k_alpha=par[i].ks; //plain stress
		par[i].kb=0; //bending
		par[i].ka=0; //area
		par[i].kv=0; //volume
		//为力分配存储空间
		par[i].F_allocate();
	}
	
	
	
	//wall repulse所需参数
	double k_repulse=0.001, exponent_repulse=2.0, R_repulse=0.5;
	
	
	//初始化粘性
	double vis_thickness=2, vis_fold=1;
	for (i=0;i<=N_par-1;i++)
	{	
		//viscosity_init(f, par[i], vis_thickness, vis_fold);  
	}
	
	
	
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
	ofstream fout0,fout1,foutdz, foutdcenter;
	//fout0.open("./result/result_particle0_pos.txt",ios::out);
	//fout1.open("./result/result_particle1_pos.txt",ios::out);
	foutdz.open("./result/result_particle_show_dxdz.txt",ios::out);
	//foutdcenter.open("./result/result_particle_dcenter",ios::out);
	//记录哪些时间点是contact的，以及每时刻的contact area
	ofstream fout_contact_time, fout_contact_area, fout_contact_d;
	//fout_contact_time.open("./result/result_contact_time.txt",ios::out);
	//fout_contact_area.open("./result/result_contact_area.txt",ios::out);
	//fout_contact_d.open("./result/result_contact_d.txt",ios::out);
	double contact_d, contact_d_crit=0.3*R; //两cell间距，接触面积，接触所需最小距离
	//contact_cal(contact_d, par[0], par[1], contact_d_crit);
	//cout<<"contact_d="<<contact_d<<endl;
	//cout<<"contact_area0="<<par[0].contact_area<<endl;
	//cout<<"contact_area1="<<par[1].contact_area<<endl;
	
	ofstream fout_particle_alltime;
	fout_particle_alltime.open("./result/particle/result_particle_alltime.txt",ios::out);




	double dx,dy,dz; //两细胞型心x,y,z间距
	double dcenter; //型心间距
	
	int np; //节点编号，用于输出所有时间的细胞位置速度
	
	int t=1, tmax=300000; //初始时间，结束时间
	int tend_last=0; //上次迭代结束的时间，用于续算
	int step; //迭代步数
	
	//续算所需
	//tend_last=input_t();
	//input_particle(N_par, par);
	//f.input();
	
	
	
	for (step=1;step<=tmax;step++)
	{
		//计算当前时间并输出
		t=step+tend_last;
		cout<<"t="<<t<<endl;
		
		//计算细胞力 IBM force spreading		
		//由于将细胞力叠加在上面，故每次置零
		f.set_bodyforce();
		for (i=0;i<=N_par-1;i++)
		{
			//计算细胞节点力
			par[i].F_cal();
			//if (i==0)
			//{
			//	par[0].F_PMN_cal(np_PMN, k_PMN, pos_penalty);
			//}
			//计算wall repulse
			//repulse_wall(f, par[i], k_repulse, exponent_repulse, R_repulse);
		
			//节点力分配
			IBM_LBM_force_spreading(f, par[i]);
		}
		//cout<<"par[0].p[1].pos="<<par[0].p[1].pos[0]<<' '<<par[0].p[1].pos[1]<<' '<<par[0].p[1].pos[2]<<endl;

		//计算流场
		f.eq();
		f.collision();
		f.streaming();
		f.macro();
		
		//IBM velocity interpolation
		for (i=0;i<=N_par-1;i++)
		{
			IBM_vel_old_set(par[i]);
			IBM_LBM_vel_interpolation(f, par[i]);
			IBM_LBM_particle_pos_update(par[i]);
			IBM_LBM_particle_pos_adjust(f, par[i]);
			cout<<"particle average position x "<<par[i].pos_ave[0]<<endl;
			cout<<"particle volume "<<par[i].V<<endl;
		}

		//更新粘性
		//for (i=0;i<=N_par-1;i++)
		//{
		//	viscosity_set(f, par[i], vis_thickness, vis_fold);	
		//}
	
		//每隔一段时间输出一下位置,接触的信息
		if (t%100==0)
		{
			//计算型心
			for (i=0;i<=N_par-1;i++)
			{
				par[i].pos_center_cal();
			}
			//输出型心
			//fout0<<t<<' '<<par[0].pos_center[0]<<' '<<par[0].pos_center[1]<<' '<<par[0].pos_center[2]<<endl;
			//fout1<<t<<' '<<par[1].pos_center[0]<<' '<<par[1].pos_center[1]<<' '<<par[1].pos_center[2]<<endl;
			//计算dx dy dz
			dx=par[0].pos_center[0]-par[1].pos_center[0];
			dz=par[0].pos_center[2]-par[1].pos_center[2];

			dy=par[0].pos_center[1]-par[1].pos_center[1];
			//输出dx/R~dz/R结果
			foutdz<<dx/R<<' '<<dz/R<<endl;
			//计算型心间距并输出
			//dcenter=sqrt(dx*dx+dy*dy+dz*dz);
			//foutdcenter<<dx/R<<' '<<dcenter/R<<endl;
			//计算最小间距并输出
			//contact_cal(contact_d, par[0], par[1], contact_d_crit);
			//fout_contact_d<<dx/R<<' '<<contact_d/R<<endl;
			//输出细胞位置速度信息，累计每100steps输出一次，用于后处理
			fout_particle_alltime<<t<<endl;
			for (i=0;i<=N_par-1;i++)
			{				
				for (np=1;np<=par[i].p_num;np++)
				{
					fout_particle_alltime<<par[i].p[np].pos[0]<<' '<<par[i].p[np].pos[1]<<' '<<par[i].p[np].pos[2]<<' ';
					fout_particle_alltime<<par[i].p[np].vel[0]<<' '<<par[i].p[np].vel[1]<<' '<<par[i].p[np].vel[2]<<endl;
				}		
			}	
			
		}
		
		
	}
	
	
	
	//fout0.close();
	//fout1.close();
	foutdz.close();
	//foutdcenter.close();
	//fout_contact_time.close();
	//fout_contact_area.close();
	//fout_contact_d.close();
	fout_particle_alltime.close();
	

	//记录运行时间
	time(&time_end);
	cout<<"time_start: "<<ctime(&time_start);
	cout<<"time_end: "<<ctime(&time_end);	
	
	ofstream fout;
	fout.open("./result/time/mainlooptime.txt",ios::out);
	fout<<"time_start: "<<ctime(&time_start);
	fout<<"time_end: "<<ctime(&time_end);
	fout.close();	
	
	//输出最终流场数据
	f.output();
	//f.output_vis2D_y(f.NY/2);
	//输出最终细胞数据
	output_particle(N_par, par);
	//输出结束时间，用于续算
	output_t(t);
	//输出用于paraview的数据
	for (i=0;i<=N_par-1;i++)
	{
		par[i].output_vtk_multiple(i);
	}
	//细胞力内存释放
	for (i=0;i<=N_par-1;i++)
	{
		par[i].F_deallocate();
	}	
	
	return 0;
}
