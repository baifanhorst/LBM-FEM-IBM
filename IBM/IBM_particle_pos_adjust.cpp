#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"
	
void IBM_LBM_particle_pos_adjust(flow &f, particle &par)
{
	//需要调整x，y两个方向
	double LX=f.LX, LY=f.LY;
	par.avepos_cal();
	int np;
	if (par.pos_ave[0]>LX)
	{
		for (np=1;np<=par.p_num;np++)
		{
			par.p[np].pos[0]=par.p[np].pos[0]-LX;
			par.pos_ave[0]=par.pos_ave[0]-LX;  //这个其实没有必要计算，只是为了程序运行时的显示细胞平均位置而已
		}
	}
	if (par.pos_ave[1]>LY)
	{
		for (np=1;np<=par.p_num;np++)
		{
			par.p[np].pos[1]=par.p[np].pos[1]-LY;
			par.pos_ave[1]=par.pos_ave[1]-LY;
		}
	}
}
