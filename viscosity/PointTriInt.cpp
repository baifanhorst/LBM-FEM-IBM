#include <iostream>
using namespace std;
#include "../particle/element.h"
#include <cmath>
char PointTriInt2D(double *p, double *v0, double *v1, double *v2);
//仅限于判断p与ele共面的情况
char PointTriInt(double *p, element &ele)
{
	//投影
	int m=0; //ele法向量最大分量的方向
	double max_outnorm_component=ele.vector_outernormal[0]; //最大外法向分量
	int k;
	for (k=1;k<=2;k++) //找到最大外法线分量的方向
	{
		if (fabs(ele.vector_outernormal[k])>fabs(max_outnorm_component))
		{
			m=k;
			max_outnorm_component=ele.vector_outernormal[k];
		}
	}
	double p_proj2D[2], v_proj2D[3][2];
	int j=0;
	int i;
	for (k=0;k<=2;k++)
	{
		if (k!=m)
		{
			p_proj2D[j]=p[k];
			for (i=0;i<=2;i++)
			{
				v_proj2D[i][j]=ele.pos[i][k];
			}
			j++;
		}
	}
	//用投影后的2D情形判断
	return PointTriInt2D(p_proj2D, v_proj2D[0], v_proj2D[1], v_proj2D[2]);
	
}
