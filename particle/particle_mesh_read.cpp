#include <iostream>
using namespace std;
#include "particle.h"
#include <fstream>

void particle::mesh_read()
{
	ifstream infile;
	infile.open("./mesh/mesh_RBC.cal",ios::in);

	
	infile>>p_num>>l_num>>e_num>>p_e_num_maxconnect;
	
	p=new point [p_num+1]; //第一个不用，节点编号从1开始，为了和输出的文件对应	
	int i;
	for (i=1;i<=p_num;i++)
	{
		infile>>p[i].pos[0]>>p[i].pos[1]>>p[i].pos[2]; //读入节点坐标
	}
	
	int j;
	for (i=1;i<=p_num;i++)
	{
		infile>>p[i].e_num; //读入节点连接单元数
		p[i].e_no=new int [p[i].e_num]; 
		for (j=0;j<=p[i].e_num-1;j++) //读入节点连接的单元编号
		{
			infile>>p[i].e_no[j];	//p[i].e_no[j]与(p[i].e_no)[j]一个意思
		}
	}	
	
	l=new line [l_num+1];
	for (i=1;i<=l_num;i++)
	{
		infile>>l[i].p_no[0]>>l[i].p_no[1]>>l[i].e_no[0]>>l[i].e_no[1];	//读入边连接的节点号，单元号
	}
	
	e=new element [e_num+1];
	for (i=1;i<=e_num;i++)
	{
		infile>>e[i].p_no[0]>>e[i].p_no[1]>>e[i].p_no[2];	//读入单元的节点号，相邻单元号
		infile>>e[i].e_no[0]>>e[i].e_no[1]>>e[i].e_no[2];
	}
	
	
	infile.close();
	
	
}
