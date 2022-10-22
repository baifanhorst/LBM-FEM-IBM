#include <iostream>
using namespace std;
#include "element.h"
#include <cmath>

void element::parameter_Fs_cal()
{
	int j;
	//计算l
	l=0;
	for (j=0;j<=2;j++)
	{
		l=l+(pos[0][j]-pos[2][j])*(pos[0][j]-pos[2][j]);
	}
	l=sqrt(l);
	//计算l_
	l_=0;
	for (j=0;j<=2;j++)
	{
		l_=l_+(pos[0][j]-pos[1][j])*(pos[0][j]-pos[1][j]);
	}
	l_=sqrt(l_);
	//计算fi
	double inner=0; //01 02内积
	for (j=0;j<=2;j++)
	{
		inner=inner+(pos[1][j]-pos[0][j])*(pos[2][j]-pos[0][j]);
	}
	fi=acos(inner/(l*l_));
	
	//注意A0也是计算Fs所需的，但是它不必在这里重复计算
}
