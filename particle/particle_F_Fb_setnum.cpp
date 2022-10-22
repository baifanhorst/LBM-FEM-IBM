#include <iostream>
using namespace std;
#include "particle.h"

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);

int ordernumber(int n, int *a);

void particle::F_Fb_setnum()
{
	int nl; //边编号
	int no_temp[3]; //为了使用逆序数函数，临时存放节点编号
	int n1,n2,n3,n4;
	int ni,nj;
	int i,j;
	int temp;
	int order,order0; //当前逆序数，初始外法线的逆序数
	for (nl=1;nl<=l_num;nl++)
	{
		//先临时设置n1,n3
		n1=l[nl].p_no[0];
		n3=l[nl].p_no[1];
		//暂时认为l[nl].e_no[0]为i单元，l[nl].e_no[1]为j单元
		//设置i,j平面编号
		ni=l[nl].e_no[0];   
		nj=l[nl].e_no[1];   
		//设置n2,n4
		for (i=0;i<=2;i++)
		{
			temp=e[l[nl].e_no[0]].p_no[i];
			if ((temp!=n1)&&(temp!=n3))
			{
				n2=temp;
				break;
			}
		}			
		for (i=0;i<=2;i++)
		{
			temp=e[l[nl].e_no[1]].p_no[i];
			if ((temp!=n1)&&(temp!=n3))
			{
				n4=temp;
				break;
			}
		}
		//求当前设置逆序数
		no_temp[0]=n1; no_temp[1]=n2; no_temp[2]=n3;
		order=ordernumber(3,no_temp);
		//求外法线逆序数
		for (i=0;i<=2;i++)
		{
			no_temp[i]=e[l[nl].e_no[0]].p_no[i];
		}
		order0=ordernumber(3,no_temp);
		//若之前的设置不对，则交换
		if (order%2!=order0%2)
		{
			temp=n4;
			n4=n2;
			n2=temp;
			
			temp=ni;
			ni=nj;
			nj=temp;
		}
		
		l[nl].p_n1=n1;
		l[nl].p_n2=n2;
		l[nl].p_n3=n3;
		l[nl].p_n4=n4;
		l[nl].e_ni=ni;
		l[nl].e_nj=nj;

		
		
	}
}
