#include <iostream>
using namespace std;
#include "particle.h"
void particle::mesh_PMN_convert()
{
	int ip;
	double temp;
	for (ip=1;ip<=p_num;ip++)
	{
		temp=p[ip].pos[0];
		p[ip].pos[0]=p[ip].pos[2];
		p[ip].pos[2]=-temp;
	}
}
