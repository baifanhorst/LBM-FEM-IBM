
#include <iostream>
using namespace std;
#include "element.h"

double max3(double &a, double &b, double &c);
double min3(double &a, double &b, double &c);

void element::pos_range_cal()
{
	int k;
	for (k=0;k<=2;k++)
	{
		pos_min[k]=min3(pos[0][k],pos[1][k],pos[2][k]);
		pos_max[k]=max3(pos[0][k],pos[1][k],pos[2][k]);
	}
}
