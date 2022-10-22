#include "../particle/particle.h"

void IBM_vel_old_set(particle &par)
{
	int np;
	int i;
	for (np=1;np<=par.p_num;np++)
	{
		for (i=0;i<=2;i++)
		{
			par.p[np].vel_old[i]=par.p[np].vel[i];
		}
	} 
}
