#ifndef point_h
#define point_h

#include <iostream>
using namespace std;

class point
{
	public:
		double pos[3]; 	//节点坐标 0->x 1->y 2->z
		double vel[3]; //节点速度
		double vel_old[3]; //上一步节点速度
	
		int mark_contact; //标志该点是否接触

		//这两个可能没用
		int e_num; //连接的单元个数
		int *e_no; //连接的单元编号 e_no[i] i=0->e_num-1
};


#endif
