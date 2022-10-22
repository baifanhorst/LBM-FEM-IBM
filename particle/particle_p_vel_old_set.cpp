#include "particle.h"

void particle::p_vel_old_set()
{
	int np;
	int i;
	for (np=1;np<=p_num;np++)
	{
		for (i=0;i<=2;i++)
		{
			p[np].vel_old[i]=p[np].vel[i];
		}
	} 
}
