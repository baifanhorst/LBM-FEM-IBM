#include <iostream>
using namespace std;
#include "../flow/flow.h"
#include "../particle/particle.h"
#include <cmath>
void repulse_wall(flow &f, particle &par, double k_repulse, double exponent_repulse, double R_repulse)
{
	par.zmin_cal();
	par.zmax_cal();
	int np;
	double d;
	double F_repulse;
	if (par.zmin<R_repulse)
	{
		for (np=1;np<=par.p_num;np++)
		{
			d=par.p[np].pos[2];
			if (d<R_repulse)
			{
				F_repulse=k_repulse*(1.0/pow(d,exponent_repulse)-1.0/pow(R_repulse,exponent_repulse));
				par.F[np][2]=par.F[np][2]+F_repulse;
				
			}
		} 		
	}
	
	if (f.LZ-par.zmax<R_repulse)
	{
		for (np=1;np<=par.p_num;np++)
		{
			d=f.LZ-par.zmax;
			if (d<R_repulse)
			{
				F_repulse=k_repulse*(1.0/pow(d,exponent_repulse)-1.0/pow(R_repulse,exponent_repulse));
				par.F[np][2]=par.F[np][2]-F_repulse;
			}
		} 	
	}
}
