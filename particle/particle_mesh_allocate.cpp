#include <iostream>
using namespace std;
#include "particle.h"
#include <fstream>


void particle::mesh_allocate()
{
	
	//为四面体分配空间
	p=new point [p_num+1]; //第一个不用，节点编号从1开始，为了和输出的文件对应
	p[1].e_num=3; p[2].e_num=3; p[3].e_num=3; p[4].e_num=3;
	int ip;
	for (ip=1;ip<=p_num;ip++)
	{
		p[ip].e_no=new int [p[ip].e_num];
	}	
	
	
	
	
	l=new line [l_num+1];

	
	e=new element [e_num+1];

	
	
	
	
	
}
