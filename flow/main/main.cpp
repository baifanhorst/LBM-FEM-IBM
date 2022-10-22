#include <iostream>
using namespace std;
#include "flow.h"
//#include "particle.h"
//#include <cstdlib>
//#include <ctime>
#include <cmath>

/*
//随机生成颗粒位置函数
void particle_rand_pos(flow &f, particle *p, int np, double gap);
//求颗粒位置处流场速度
void particle_vel_flow(flow &f, particle *p, int np);
//求颗粒作用力
void particle_force(flow &f, particle *p, int np);
//移动颗粒位置
void particle_pos(flow &f, particle *p, int np);
*/


int main()
{
	int nx=10, ny=3, nz=10;
	flow f(nx,ny,nz);
	//P流初始化
	//double Re=0.1;
	//double LZ=nz;	
	//double gx=0.00002, gy=0.0, gz=0.0, uw_top=0.0, uw_bottom=0.0, den0=1.0, vis0=sqrt(abs(gx)*(LZ*LZ*LZ)/(8*den0*Re));
	
	//C流初始化
	double Re=0.1;
	double LZ=nz;	
	double gx=0.0, gy=0.0, gz=0.0, uw_top=0.001, uw_bottom=0.0, den0=1.0, vis0=abs(uw_top-uw_bottom)*LZ/Re;
	
	cout<<"tao="<<3*vis0+0.5<<endl; //测试tao是否小于一
	
	f.init(gx, gy, gz, uw_top, uw_bottom, den0, vis0);

	//求解
	
	int t=1, tmax=1000;
	for (t=1;t<=tmax;t++)
	{
		if (t%10==0)
			cout<<"t="<<t<<endl;
		
		f.eq();
		f.collision();
		f.streaming();
		f.macro();
		
	}
	
	//结果输出
	f.output();
	f.output_2Dvector(ny/2); //输出中间截面速度场
	//test q_contrast
	//int q_contr;
	//cin>>q_contr;
	//cout<<"the contrast of "<<q_contr<<"="<<f.q_contrast(q_contr)<<endl;





	//void init(double gx=0.00002, double gy=0.0, double gz=0.0, double re=3);
	//f.init(0.00002,0,0,3);

	//void flow::init1(double re);
	//double Re=0.00001;
	//f.init1(Re);
	



	/*
	//生成颗粒
	int np=1; //颗粒个数
	//设置颗粒半径，质量，这里颗粒的大小质量都一样
	double R=0.1; //颗粒半径
	const double Pi=3.1415926;
	double m=f.den0*Pi*4.0/3.0*R*R*R;
	particle *p=new particle[np];
	int i;
	for (i=0;i<=np-1;i++)
	{
		p[i].R=R;
		p[i].m=m;
	}
	
	p[0].pos[0]=25;
	p[0].pos[1]=10;
	p[0].pos[2]=10;
	
	//设置粒子初始速度
	particle_vel_flow(f,p,np);
	for (i=0;i<=np-1;i++)
	{
		p[i].vel[0]=p[i].vel_flow[0];
		p[i].vel[1]=p[i].vel_flow[1];
		p[i].vel[2]=p[i].vel_flow[2];

		p[i].vel_old[0]=p[i].vel[0];
		p[i].vel_old[1]=p[i].vel[1];
		p[i].vel_old[2]=p[i].vel[2];
		
	}	
	*/

	/*
	//生成颗粒
	int np=10; //颗粒个数
	//设置颗粒半径，质量，这里颗粒的大小质量都一样
	double R=0.1; //颗粒半径
	const double Pi=3.1415926;
	double m=f.den0*Pi*4.0/3.0*R*R*R;
	particle *p=new particle[np];
	int i;
	for (i=0;i<=np-1;i++)
	{
		p[i].R=R;
		p[i].m=m;
	}
	//随机生成颗粒位置
	srand(time(NULL));
	double gap=R/10; //初始时刻颗粒的最小间距
	particle_rand_pos(f,p,np,gap);
	
	//设置粒子初始速度
	particle_vel_flow(f,p,np);
	for (i=0;i<=np-1;i++)
	{
		p[i].vel[0]=p[i].vel_flow[0];
		p[i].vel[1]=p[i].vel_flow[1];
		p[i].vel[2]=p[i].vel_flow[2];

		p[i].vel_old[0]=p[i].vel[0];
		p[i].vel_old[1]=p[i].vel[1];
		p[i].vel_old[2]=p[i].vel[2];
		
	}
	*/
	
	//f.input();
	/*
	int t=0;
	for (t=1;t<=2;t++)
	{		
		//移动颗粒位置
		particle_pos(f,p,np);
		//if (t%100==0)
		{
			cout<<"t="<<t<<endl;
			cout<<p[0].pos[0]<<' '<<p[0].pos[1]<<' '<<p[0].pos[2]<<endl;
			cout<<p[0].vel[0]<<' '<<p[0].vel[1]<<' '<<p[0].vel[2]<<endl;
			cout<<p[0].force[0]<<' '<<p[0].force[1]<<' '<<p[0].force[2]<<endl;
			cout<<p[0].force[0]/p[0].m<<' '<<p[0].force[1]/p[0].m<<' '<<p[0].force[2]/p[0].m<<endl;
		}

		f.eq();
		f.collision();
		f.streaming();
		f.macro();
	}
	
	f.output();
	f.output_2Dvector(15);
	*/
	return 0;
}
