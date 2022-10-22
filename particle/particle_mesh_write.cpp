#include <iostream>
using namespace std;
#include "particle.h"
#include <fstream>

void particle::mesh_write()
{
	ofstream outfile;
	outfile.open("./result/mesh/test_writemesh.txt",ios::out);
	outfile<<p_num<<' '<<l_num<<' '<<e_num<<' '<<p_e_num_maxconnect<<endl;
	
	int i;
	for (i=1;i<=p_num;i++)
	{
		outfile<<p[i].pos[0]<<' '<<p[i].pos[1]<<' '<<p[i].pos[2]<<endl;		
	}

	
	int j;
	for (i=1;i<=p_num;i++)
	{
		outfile<<p[i].e_num<<endl;
		for (j=0;j<=p[i].e_num-1;j++)
		{
			outfile<<(p[i].e_no)[j]<<endl;	///////////////
		}
	}	
	
	for (i=1;i<=l_num;i++)
	{
		outfile<<(l[i].p_no)[0]<<' '<<(l[i].p_no)[1]<<' '<<(l[i].e_no)[0]<<' '<<(l[i].e_no)[1]<<endl;		
	}
	
	for (i=1;i<=e_num;i++)
	{
		outfile<<e[i].p_no[0]<<' '<<e[i].p_no[1]<<' '<<e[i].p_no[2]<<' ';
		outfile<<e[i].e_no[0]<<' '<<e[i].e_no[1]<<' '<<e[i].e_no[2]<<endl;
	}
	outfile.close();
}
