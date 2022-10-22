#include <iostream>
using namespace std;
#include "particle.h"

void particle::pos_rangebox_cal()
{
	int np;
	int k;
	for (k=0;k<=2;k++)
	{
		pos_min[k]=p[1].pos[k];
		pos_max[k]=p[1].pos[k];
	}
	for (np=2;np<=p_num;np++)
	{
		for (k=0;k<=2;k++)
		{
			if (p[np].pos[k]<pos_min[k])
			{
				pos_min[k]=p[np].pos[k];
			}
			else if (p[np].pos[k]>pos_max[k])
			{
				pos_max[k]=p[np].pos[k];
			}
		}
	}
}
