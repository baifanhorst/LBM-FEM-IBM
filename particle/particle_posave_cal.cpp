#include <iostream>
using namespace std;
#include "particle.h"

void particle::avepos_cal()
{
	int np,j;
	for (j=0;j<=2;j++)
	{
		pos_ave[j]=0;
	}
	for (np=1;np<=p_num;np++)
	{
		for (j=0;j<=2;j++)
		{
			pos_ave[j]=pos_ave[j]+p[np].pos[j];
		}	
	}
	for (j=0;j<=2;j++)
	{
		pos_ave[j]=pos_ave[j]/p_num;
	}
}
