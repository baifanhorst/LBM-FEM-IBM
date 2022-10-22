#include <iostream>
using namespace std;

#include "../particle/particle.h"
#include "../flow/flow.h"

#include <cmath>
//随机数
#include <cstdlib>
#include <ctime>




void linear(double *result, double x1, double *v1, double x2, double *v2);
void normalize(double *e, double *a);


int BoxTest(double *q,double *r, double *pos_min, double *pos_max);
char SegTriInt(element &ele, double *q, double *r);

char PointPolyIn(double *q, particle &par, flow &f)
{
	int ne,i,j,k;
	int ip;
	int ne1;
	
	/*
	//这一段在单独调用时需要，但是在viscosity_set函数中调用时不用，以免发生重复
	//计算单元中心位置，生成射线时候要用
	for (ne=1;ne<=par.e_num;ne++)
	{
		par.e[ne].pos_center_abs_cal();
	}
	par.pos_rangebox_cal(); //计算par的坐标范围，用于生成射线
	double length_ray=0; //射线段长度 
	for (k=0;k<=2;k++) //计算射线段长度
	{
		length_ray=length_ray+(par.pos_max[k]-par.pos_min[k])*(par.pos_max[k]-par.pos_min[k]);
	}
	length_ray=sqrt(length_ray)+2.0; //多出一点，保险
	//计算每个单元坐标范围
	for (ne=1;ne<=par.e_num;ne++)
	{
		par.e[ne].pos_range_cal();
	}
	*/
	
	double length_ray=0; //射线段长度 
	for (k=0;k<=2;k++) //计算射线段长度
	{
		length_ray=length_ray+(par.pos_max[k]-par.pos_min[k])*(par.pos_max[k]-par.pos_min[k]);
	}
	length_ray=sqrt(length_ray)+f.NX*2; //使用两倍流场长度作为射线长度
	
	//double theta;
	char mark_ray_poly; //看射线是否造成degeneracy
		
	double direction_ray[3]; //射线方向
	double theta_ray,fi_ray; //射线方向的两个角度，球坐标
	double pi=3.1415926;
	int crossing=0; //射线穿过的次数
	int direction; //方向标志，以免和k冲突
	double r[3]; //射线段终点
	char mark_ray_seg; //射线与一个单元是否相交的标志	
	
		
	
	srand(time(NULL));
	
	

	
	
	mark_ray_poly='d'; //预设为degeneracy，以便进入循环
	crossing=0; //预设为0，以便进入循环
						
	while ((mark_ray_poly=='d')||(crossing==0)) //出现degeneracy或者射线一次都没有穿过，则为生成失败
	{
		//生成射线
													
		theta_ray=rand()/double(RAND_MAX)*pi;
		fi_ray=rand()/double(RAND_MAX)*2.0*pi;
		direction_ray[0]=sin(theta_ray)*cos(fi_ray);
		direction_ray[1]=sin(theta_ray)*sin(fi_ray);
		direction_ray[2]=cos(theta_ray);
		//cout<<"direction_ray="<<direction_ray[0]<<' '<<direction_ray[1]<<' '<<direction_ray[2]<<endl;
		linear(r,1,q,length_ray,direction_ray);
							
								
		crossing=0;
		mark_ray_poly='i';  //随便给一个，不是d就行
							
		for (ne1=1;ne1<=par.e_num;ne1++) //最外层循环用过ne了，所以不能再用，故这里用ne1
		{
			//cout<<"ne1="<<ne1<<endl;
			//预判断
			//cout<<"BoxTest="<<BoxTest(q, r,
				//par.e[ne1].pos_min, par.e[ne1].pos_max)<<endl;
			if (BoxTest(q, r,
				par.e[ne1].pos_min, par.e[ne1].pos_max)==1)
			{
				mark_ray_seg=SegTriInt(par.e[ne1], q, r);
				//cout<<"mark_ray_seg="<<mark_ray_seg<<endl;
				if (mark_ray_seg=='i')
				{
					crossing++;
				}
				else if (mark_ray_seg=='d')
				{
					mark_ray_poly='d';
					break;
				}
			}
		}							
	}
	if (crossing%2==0)
	{
		return 'o';
	}
	else
	{
		return 'i';
	}	
						
		
}


















/*						
						pos_flowpoint[0]=i;
						pos_flowpoint[1]=j;
						pos_flowpoint[2]=k+0.5;
						dmin=d_point_element_cal(pos_flowpoint, 
								par.e[1].pos[0], par.e[1].pos[1], par.e[1].pos[2], 
									par.e[1].vector_outernormal);
						for (ne1=2;ne1<=par.e_num;ne1++) //最外层循环用过ne了，所以不能再用，故这里用ne1
						{
							d_element=d_point_element_cal(pos_flowpoint, 
								par.e[ne1].pos[0], par.e[ne1].pos[1], par.e[ne1].pos[2], 
									par.e[ne1].vector_outernormal);
							
							if (fabs(d_element)<fabs(dmin))
							{
								dmin=d_element;
							}
						}
						cout<<"i="<<i<<' '<<"j="<<j<<' '<<"k="<<k<<' '<<"dmin="<<dmin<<endl;
						
						//更新粘性
						if (fabs(dmin)<thickness)
						{
							theta=heaviside(dmin,thickness);
							f.vis[(i+NX)%NX][(j+NY)%NY][k]=vis_out-(vis_out-vis_in)*theta;
						}
						
						
						//标记，意味着该点已经考察过了
						f.mark[(i+NX)%NX][(j+NY)%NY][k]=1;
						*/
