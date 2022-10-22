#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"
#include <cmath>
	
void repulse_cell_basic(particle &par1, particle &par2, double k_repulse, double exponent_repulse, double R_repulse);

void repulse_cell(flow &f, particle &par1, particle &par2, double k_repulse, double exponent_repulse, double R_repulse)
{
	//判断哪个在前哪个在后
	particle *par1_p, *par2_p, *par_temp_p;
	par1_p=&par1;
	par2_p=&par2;
	
	if ((*par1_p).pos_ave[0]>(*par2_p).pos_ave[0])
	{
		//使par1_p指在前面那个
		par_temp_p=par2_p;
		par2_p=par1_p;
		par1_p=par_temp_p;
	}
	
	//移动至真实相对距离
	double dif_ave_distance_x=0; //x方向平均距离之差
	dif_ave_distance_x=(*par2_p).pos_ave[0]-(*par1_p).pos_ave[0];
	int mark_translate=0;
	if (dif_ave_distance_x>0.5*f.LX)  
	{
		(*par2_p).translate_posx(-f.LX);
		mark_translate=1;
	}
	
	//计算平均距离
	double ave_distance=0;
	int i;
	for (i=0;i<=2;i++)
	{
		ave_distance=ave_distance+(par1.pos_ave[i]-par2.pos_ave[i])*(par1.pos_ave[i]-par2.pos_ave[i]);
	}
	ave_distance=sqrt(ave_distance);
	cout<<"ave_distance="<<ave_distance<<endl;
		
	//计算力
	if (ave_distance<(par1.R+par2.R)/2.0*3.0) //平均距离间距
	{
		repulse_cell_basic(par1, par2, k_repulse, exponent_repulse, R_repulse);
	}
	
		
	//移回去
	if (mark_translate==1)
	{
		(*par2_p).translate_posx(f.LX);
		mark_translate=0;
	}
	
}
