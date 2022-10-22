#include <iostream>
using namespace std;

//一个粗略的seg是否在box外面的判断
int BoxTest(double *q,double *r, double *pos_min, double *pos_max)
{
	int k;
	for (k=0;k<=2;k++)
	{
		if ((q[k]<pos_min[k])&&(r[k]<pos_min[k]))
		{
			return 0;
		}
		if ((q[k]>pos_max[k])&&(r[k]>pos_max[k]))
		{
			return 0;
		}
		
	}
	return 1;
}
