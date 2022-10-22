#include <iostream>
using namespace std;
#include "particle.h"

void particle::F_PMN_cal(int np, double k_PMN, double *pos_penalty)
{
	int k;
	for (k=0;k<=2;k++)
	{
		F[np][k]=F[np][k]-k_PMN*(p[np].pos[k]-pos_penalty[k]);
	}
}
