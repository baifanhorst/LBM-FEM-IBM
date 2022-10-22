#include <iostream>
using namespace std;
#include "flow.h"
#include <omp.h>

void flow::eq()
{
	int i,j,k,q;
	double eu,uu; //eu是e与u的点积，uu为u与u的点积
	#pragma omp parallel for private(i,j,k,q,eu,uu)
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
				for (q=0;q<=Q-1;q++)			
				{
					eu=innerproduct(e[q],vel[i][j][k]);
					uu=innerproduct(vel[i][j][k],vel[i][j][k]);
					feq[i][j][k][q]=w[q]*den[i][j][k]*(1.0+3.0*eu+4.5*eu*eu-1.5*uu);
				}
}
