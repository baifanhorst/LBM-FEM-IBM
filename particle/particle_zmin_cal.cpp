#include "particle.h"

void particle::zmin_cal()
{
	int np;
	zmin=p[1].pos[2];
	for (np=2;np<=p_num;np++)
	{
		if (p[np].pos[2]<zmin)
		{
			zmin=p[np].pos[2];
		}
	}
}
