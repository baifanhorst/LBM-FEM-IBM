#include <iostream>
using namespace std;
#include "flow.h"
#include <omp.h>

void flow::macro()
{
	int i,j,k,q;
	#pragma omp parallel for private(i,j,k,q)
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{				
				den[i][j][k]=0;
				vel[i][j][k][0]=0;
				vel[i][j][k][1]=0;
				vel[i][j][k][2]=0;
				for (q=0;q<=Q-1;q++)
				{
					den[i][j][k]=den[i][j][k]+f[i][j][k][q];
					vel[i][j][k][0]=vel[i][j][k][0]+f[i][j][k][q]*e[q][0];
					vel[i][j][k][1]=vel[i][j][k][1]+f[i][j][k][q]*e[q][1];
					vel[i][j][k][2]=vel[i][j][k][2]+f[i][j][k][q]*e[q][2];
				}		
				vel[i][j][k][0]=(vel[i][j][k][0]+bodyforce[i][j][k][0]/2)/den[i][j][k]; //Shan-Doolen or Guo
				vel[i][j][k][1]=(vel[i][j][k][1]+bodyforce[i][j][k][1]/2)/den[i][j][k];
				vel[i][j][k][2]=(vel[i][j][k][2]+bodyforce[i][j][k][2]/2)/den[i][j][k];
			}
}

