#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"
	
void IBM_LBM_particle_pos_update(particle &par)
{
	int np;
	int i;
	for (np=1;np<=par.p_num;np++)
	{
		for (i=0;i<=2;i++)
		{
			par.p[np].pos[i]=par.p[np].pos[i]+1.5*par.p[np].vel[i]-0.5*par.p[np].vel_old[i];
		}
	}
}
