#include <iostream>
using namespace std;
#include "particle.h"

void particle::pos_init(double x_ave, double y_ave, double z_ave, double r)
{
	R=r;
	pos_ave[0]=x_ave; pos_ave[1]=y_ave; pos_ave[2]=z_ave;
	
	int i,j;
	for (i=1;i<=p_num;i++)
	{
		p[i].pos[0] =p[i].pos[0]*r+x_ave; //设置节点初始位置
		p[i].pos[1] =p[i].pos[1]*r+y_ave;
		p[i].pos[2] =p[i].pos[2]*r+z_ave;
		
	}
}
