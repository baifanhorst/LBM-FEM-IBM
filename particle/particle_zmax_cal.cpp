#include "particle.h"

void particle::zmax_cal()
{
	int np;
	zmax=p[1].pos[2];
	for (np=2;np<=p_num;np++)
	{
		if (p[np].pos[2]>zmax)
		{
			zmax=p[np].pos[2];
		}
	}
}
