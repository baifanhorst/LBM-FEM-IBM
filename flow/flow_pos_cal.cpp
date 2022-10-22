#include <iostream>
using namespace std;
#include "flow.h"

void flow::pos_cal()
{
	int i,j,k;
	for (i=0;i<=NX-1;i++)
	{
		for (j=0;j<=NY-1;j++)
		{
			for (k=0;k<=NZ-1;k++)
			{
				pos[i][j][k][0]=i;
				pos[i][j][k][1]=j;
				pos[i][j][k][2]=k+0.5;
			}
		}
	}
}
