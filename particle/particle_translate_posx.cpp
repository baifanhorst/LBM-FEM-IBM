#include <iostream>
using namespace std;

#include "particle.h"

void particle::translate_posx(double x)
{
	int ip;
	for (ip=1;ip<=p_num;ip++)
	{
		p[ip].pos[0]=p[ip].pos[0]+x;
	}
	pos_ave[0]=pos_ave[0]+x;
}

