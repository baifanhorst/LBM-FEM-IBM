#include <iostream>
using namespace std;
#include "element.h"

void element::pos_center_abs_cal() //计算绝对中心坐标
{
	int k;
	for (k=0;k<=2;k++)
	{
		pos_center_abs[k]=(pos[0][k]+pos[1][k]+pos[2][k])/3.0;
	}
}
