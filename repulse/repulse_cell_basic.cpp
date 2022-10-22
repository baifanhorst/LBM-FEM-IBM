#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"
#include <cmath>


//仅仅是计算相互作用力，不涉及细胞位置的判断和调整

void repulse_cell_basic(particle &par1, particle &par2, double k_repulse, double exponent_repulse, double R_repulse)
{
	int i1,i2; //par1，par2节点编号
	double d; //节点间距
	int k;
	double F_repulse;
	double direction12_F_repulse[3]={0,0,0};
	for (i1=1;i1<=par1.p_num;i1++)
	{
		for (i2=1;i2<=par2.p_num;i2++)
		{
			//求节点间距
			d=0;
			for (k=0;k<=2;k++)
			{
				d=d+(par1.p[i1].pos[k]-par2.p[i2].pos[k])*(par1.p[i1].pos[k]-par2.p[i2].pos[k]);
			}
			d=sqrt(d);
			//求力
			if (d<R_repulse)
			{
				//cout<<"i1="<<i1<<' '<<"i2="<<i2<<' '<<endl;
				//cout<<"i1 pos"<<' '<<par1.p[i1].pos[0]<<' '<<par1.p[i1].pos[1]<<' '<<par1.p[i1].pos[2]<<endl;
				//cout<<"i2 pos"<<' '<<par2.p[i2].pos[0]<<' '<<par2.p[i2].pos[1]<<' '<<par2.p[i2].pos[2]<<endl;
				cout<<"d="<<d<<endl;
				F_repulse=-k_repulse*(1/pow(d,exponent_repulse)-1/pow(R_repulse,exponent_repulse));
				cout<<"F_repulse="<<F_repulse<<endl;
				for (k=0;k<=2;k++)
				{
					direction12_F_repulse[k]=(par2.p[i2].pos[k]-par1.p[i1].pos[k])/d;
					//cout<<"direction="<<direction12_F_repulse[k]<<endl;	
					par1.F[i1][k]=par1.F[i1][k]+direction12_F_repulse[k]*F_repulse;
					par2.F[i2][k]=par2.F[i2][k]-par1.F[i1][k];
				}
				
			}
			
		}
	}
	
}
