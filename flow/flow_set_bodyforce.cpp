#include <iostream>
using namespace std;
#include "flow.h"

void flow::set_bodyforce()
{
	int i,j,k;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				bodyforce[i][j][k][0]=gx;
				bodyforce[i][j][k][1]=gy;
				bodyforce[i][j][k][2]=gz;
			}
}
