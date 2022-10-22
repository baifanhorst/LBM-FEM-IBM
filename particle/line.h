#ifndef line_h

#define line_h




#include <iostream>
using namespace std;

class line
{
	public:
		int p_no[2]; //2个节点编号
		int e_no[2]; //2个单元编号
		int p_n1,p_n2,p_n3,p_n4; //计算弯曲力时1,2,3,4节点对应的节点编号
		int e_ni,e_nj; //计算弯曲力时 i,j两个单元的编号
		double theta0,theta; //相邻两个单元的初始夹角 当前夹角
};




#endif
