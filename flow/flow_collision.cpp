#include <iostream>
#include <stdio.h>
using namespace std;
#include "flow.h"
#include <omp.h>

void flow::collision()
{
	int i,j,k,q;
	double F_Guo=0;
	double ef=0,uf=0,eu=0;
	double tau;
	
	#pragma omp parallel for private(i,j,k,q,F_Guo, ef, uf, eu, tau)
	for (i=0;i<=NX-1;i++)
	{
		for (j=0;j<=NY-1;j++)
		{
			
			for (k=0;k<=NZ-1;k++)
			{
				tau=3*vis[i][j][k]+0.5;	
							
				for (q=0;q<=Q-1;q++)
				{
					ef=innerproduct(e[q],bodyforce[i][j][k]);
					uf=innerproduct(vel[i][j][k],bodyforce[i][j][k]);
					eu=innerproduct(e[q],vel[i][j][k]);
		
					F_Guo=(1-1/(2*tau))*w[q]*(3*ef-3*uf+9*eu*ef);	//Guo forcing term			
					fc[i][j][k][q]=f[i][j][k][q]+(feq[i][j][k][q]-f[i][j][k][q])/tau+F_Guo;
				}	
			}
		}
	}
}

