#include <iostream>
using namespace std;
#include "particle.h"



//求力时各种所需的几何参数
//单元的三个节点的坐标专门有一个函数来设置，故不在这里设置，但要注意下面所有计算都依赖于单元的节点坐标
//一共所需的参数有：(1)单元：l0 l0_ l l_ fi0 fi A A0 V V0(这个是为了计算总体体积) vector_outernormal (2)边：theta theta0 (3)总体: A A0 V V0
//其中所有带0的参数均在初始化中计算 剩下的每个总时间步会计算一次  


void particle::parameter_cal()
{
	int ne;
	A=0; V=0;
	for (ne=1;ne<=e_num;ne++)
	{
		e[ne].parameter_Fs_cal(); //计算单元中的l,l_,fi
		e[ne].area_cal(); //计算单元面积
		e[ne].vector_outernormal_cal(); //计算外法线向量
		e[ne].V_cal(); //计算每个单元的代数体积		
		A=A+e[ne].A; //计算总面积
		V=V+e[ne].V; //计算总体积
	}
	l_theta_cal(); //计算每个边对应的theta
}
