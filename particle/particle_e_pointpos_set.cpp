#include <iostream>
using namespace std;
#include "particle.h"

void particle::e_pointpos_set()
{
	int ne,i,j;
	for (ne=1;ne<=e_num;ne++)
	{
		for (i=0;i<=2;i++)
		{
			for (j=0;j<=2;j++)
			{
				e[ne].pos[i][j]=p[e[ne].p_no[i]].pos[j];
			}
		}
	}
}
