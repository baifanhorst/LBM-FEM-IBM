#include <iostream>
using namespace std;
#include "particle.h"

void particle::F_cal()
{
	//先置零
	F_setzero();
	//更新单元节点坐标
	e_pointpos_set();
	//更新几何参数
	parameter_cal();
	//计算Fs
	F_Fs_cal();
	
	//计算Fb
	//F_Fb_cal();

	//计算Fa
	//F_Fa_cal();

	//计算Fv
	//F_Fv_cal();
	
}
