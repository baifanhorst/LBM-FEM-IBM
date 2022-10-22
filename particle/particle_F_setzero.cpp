#include <iostream>
using namespace std;
#include "particle.h"


//每一个时间步计算F时均要先将F置零
void particle::F_setzero()
{
	int i,j;
	for (i=1;i<=p_num;i++)
	{
		for (j=0;j<=2;j++)
		{
			F[i][j]=0;
		}
	}
}
