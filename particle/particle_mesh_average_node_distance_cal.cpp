#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>
#include <fstream>

double length(double *a);
void particle::mesh_average_node_distance_cal()
{
	d_average_node=0;
	double d_edge; //边长度
	int i,k;
	int a,b; //边两节点标号
	double ab[3]; //边向量
	for (i=1;i<=l_num;i++)
	{
		a=l[i].p_no[0];
		b=l[i].p_no[1];
		for (k=0;k<=2;k++)
		{
			ab[k]=p[b].pos[k]-p[a].pos[k];
		}
		d_edge=length(ab);
		d_average_node=d_average_node+d_edge;
	}
	d_average_node=d_average_node/l_num;
	cout<<"average edge distance "<<d_average_node<<endl;
	
	ofstream fout;
	fout.open("./result/mesh_average_edge_distance.txt",ios::out);
	fout<<d_average_node<<endl;
	fout.close();
}
