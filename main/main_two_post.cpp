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
	//流场尺寸
	int nx=20*int(R), ny=10*int(R), nz=10*int(R);
	flow f(nx,ny,nz);
	//流场 C流初始化
	double LZ=nz;
	double vis0=1.0/6;
	double shear_rate=Re*vis0/R/R;	
	double gx=0.0, gy=0.0, gz=0.0, uw_top=(LZ/2.0)*shear_rate, uw_bottom=-uw_top, den0=1.0;
	cout<<"tao="<<3*vis0+0.5<<endl; //测试tao是否小于一
	f.init(gx, gy, gz, uw_top, uw_bottom, den0, vis0);
	//细胞初始化
	double xave, yave, zave;
	double dx0,dy0,dz0;
	const int N_par=2;
	particle par[N_par];
	
	dx0=4.0*R; dy0=0.5*R; dz0=0.25*R;
	xave=f.LX/2.0-dx0/2.0, yave=f.LY/2.0+dy0/2.0, zave=f.LZ/2.0+dz0/2.0;
	
	par[0].mesh_read();
	//par[0].mesh_PMN_convert();
	//cout<<"par[0].p[1].pos="<<par[0].p[1].pos[0]<<' '<<par[0].p[1].pos[1]<<' '<<par[0].p[1].pos[2]<<endl;
	//double pos_penalty[3]={15,15,1};
	//double k_PMN=0.1; 
	//int np_PMN=1;
	par[0].pos_init(xave, yave, zave, R);
	
	par[1].mesh_read();
	xave=f.LX/2.0+dx0/2.0, yave=f.LY/2.0-dy0/2.0, zave=f.LZ/2.0-dz0/2.0;
	
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
		par[i].ks=den0*vis0*shear_rate*R/Ca; par[i].k_alpha=par[i].ks; par[i].kb=0; par[i].ka=0; 
		par[i].kv=0; //暂时这么设，可能不合理
		
		//为力分配存储空间
		par[i].F_allocate();
	}
	
	
	
	//wall repulse所需参数
	double k_repulse=0.001, exponent_repulse=2.0, R_repulse=0.5;
	
	int t=1, tmax;
	int tend_last=0;
	int step;
	
	//初始化粘性
	double vis_thickness=2, vis_fold=1;
	for (i=0;i<=N_par-1;i++)
	{	
		//viscosity_init(f, par[i], vis_thickness, vis_fold);  
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
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//读写数据所需
	ifstream fin;
	ofstream fout;
	ofstream fout_dxdy,fout_dxdz,fout_dxdcenter;
	ofstream fout_dcontact;
	ofstream fout_area_contact;
	//细胞膜节点编号
	int np;
	//两次记录数据之间的间隔
	int record_interval=100;

	//设置接触距离判定值 d_contact_crit
	double d_contact_crit=0.4*R;
	//接触距离
	double d_contact;
	//三个方向细胞型心间距 总型心间距
	double dx,dy,dz;
	double dcenter;	
	
	//计算相对位置(用半径R无量纲化) 最小间距(用半径R无量纲化) 接触面积(用4*PI*R*R无量纲化)
	fin.open("./result/particle/result_particle_alltime.txt",ios::in);
	fout_dxdy.open("./result/interaction/result_particle_dxdy.txt",ios::out);
	fout_dxdz.open("./result/interaction/result_particle_dxdz.txt",ios::out);
	fout_dxdcenter.open("./result/interaction/result_particle_dxdcenter.txt",ios::out);
	fout_dcontact.open("./result/interaction/result_particle_contact_dmin.txt",ios::out);
	fout_area_contact.open("./result/interaction/result_particle_contact_area.txt",ios::out);
	

	//读入最终时间步
	tmax=input_t();



	
	
	for (step=1;step<=tmax/record_interval;step++)
	{
		cout<<"step="<<step<<endl;
		//读取当前时间的细胞位置和速度
		fin>>t;
		cout<<"t="<<t<<endl;
		for (i=0;i<=N_par-1;i++)
		{
			for (np=1;np<=par[i].p_num;np++)
			{
				fin>>par[i].p[np].pos[0]>>par[i].p[np].pos[1]>>par[i].p[np].pos[2];
				fin>>par[i].p[np].vel[0]>>par[i].p[np].vel[1]>>par[i].p[np].vel[2];
			}
		}
		//计算必备的几何量
		for (i=0;i<=N_par-1;i++)
		{
			par[i].e_pointpos_set(); //设置单元三个节点的坐标，下面一个函数要用
			par[i].parameter_cal(); //计算几何量
			
		}
		//计算型心
		for (i=0;i<=N_par-1;i++)
		{
			par[i].pos_center_cal();
		}
		//计算型心间距并记录
		dx=par[0].pos_center[0]-par[1].pos_center[0];
		dy=par[0].pos_center[1]-par[1].pos_center[1];
		dz=par[0].pos_center[2]-par[1].pos_center[2];
		dcenter=sqrt(dy*dy+dz*dz);

		fout_dxdy<<dx/R<<' '<<dy/R<<endl;
		fout_dxdz<<dx/R<<' '<<dz/R<<endl;
		fout_dxdcenter<<dx/R<<' '<<dcenter/R<<endl;
		//计算最小间距 接触面积
		contact_cal(d_contact, par[0], par[1], d_contact_crit);
		//记录最小间距
		fout_dcontact<<dx/R<<' '<<d_contact/R<<endl;
		//记录接触面积
		fout_area_contact<<dx/R<<' '<<par[0].contact_area/(4*PI*R*R)<<' '<<par[1].contact_area/(4*PI*R*R)<<endl;
		
	}
	
	fin.close();
	fout_dxdy.close();	
	fout_dxdz.close();
	fout_dxdcenter.close();
	fout_dcontact.close();
	fout_area_contact.close();

	//提取接触时间
	//打开最短接触距离文件 result_contact_d.txt
	
	fin.open("./result/interaction/result_particle_contact_dmin.txt",ios::in);
	fout.open("./result/interaction/result_particle_contact_t.txt",ios::out);

	//累计接触时间
	double dmin;
	double temp; //为了读数据，用这个变量读入的数据没有实际作用
	double t_contact=0;
	
	for (step=1;step<=tmax/record_interval;step++)
	{
		fin>>temp>>dmin;
		if (dmin<=d_contact_crit/R) //因为dmin是用d_contact/R计算的，从而这里比较也应该用d_contact_crit/R
		{
			t_contact+=record_interval;
		}
	}
	//记录原始时间，并换算成真实时间
	fout<<"original contact steps:"<<endl;
	fout<<t_contact<<endl;
	fout<<"dimensionless contact steps:"<<endl;
	fout<<t_contact*shear_rate<<endl;


	fin.close();
	fout.close();
	///////////////////////////////////////////////////////////////////////////////////////////////////











	//细胞力内存释放
	for (i=0;i<=N_par-1;i++)
	{
		par[i].F_deallocate();
	}
	
	return 0;
}
