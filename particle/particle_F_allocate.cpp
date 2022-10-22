#include <iostream>
using namespace std;
#include "particle.h"

void particle::F_allocate()
{
	
	int i,j;
	F=new double *[p_num+1];
	for (i=1;i<=p_num;i++)
	{
		F[i]=new double [3];
		//分配空间后顺便置零
		for (j=0;j<=2;j++)
		{
			F[i][j]=0;
		}
	}
}
