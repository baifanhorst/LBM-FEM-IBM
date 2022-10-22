#include <iostream>
using namespace std;
#include "flow.h"
#include <omp.h>

void flow::streaming()
{
	int i,j,k,q;
	int ip,jp,kp;
	//除了上下边界的其它节点
	#pragma omp parallel for private(i,j,k,q,ip,jp,kp)
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=1;k<=NZ-2;k++)
				for (q=0;q<=Q-1;q++)
				{
					ip=(i+NX-e[q][0])%NX; 
					jp=(j+NY-e[q][1])%NY;
					kp=(k+NZ-e[q][2])%NZ;
					f[i][j][k][q]=fc[ip][jp][kp][q];
				}
	
	//处理上下边界	
	int q_contr;
	//上边界	
	k=NZ-1;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
		{
			for (q=0;q<=Q-1;q++)
			{
				if (e[q][2]==-1)
				{
					q_contr=q_contrast(q);
					f[i][j][k][q]=fc[i][j][k][q_contr]-6*w[q_contr]*den[i][j][k]*Uw_top*e[q_contr][0];
				}
				else
				{
					ip=(i+NX-e[q][0])%NX; 
					jp=(j+NY-e[q][1])%NY;
					kp=(k+NZ-e[q][2])%NZ;
					f[i][j][k][q]=fc[ip][jp][kp][q];
				}
				
			}
		}
	/*
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
		{
			f[i][j][k][6]= f[i][j][k][5] -6*w[5] *den[i][j][k]*Uw_top*e[5][0];
			f[i][j][k][12]=f[i][j][k][11]-6*w[11]*den[i][j][k]*Uw_top*e[11][0];
			f[i][j][k][13]=f[i][j][k][14]-6*w[14]*den[i][j][k]*Uw_top*e[14][0];
			f[i][j][k][16]=f[i][j][k][15]-6*w[15]*den[i][j][k]*Uw_top*e[15][0];
			f[i][j][k][17]=f[i][j][k][18]-6*w[18]*den[i][j][k]*Uw_top*e[18][0];
			for (q=0;q<=Q-1;q++)
			{
				if (e[q][2]!=-1)
				{
					ip=(i+NX-e[q][0])%NX; 
					jp=(j+NY-e[q][1])%NY;
					kp=(k+NZ-e[q][2])%NZ;
					f[i][j][k][q]=fc[ip][jp][kp][q];
				}
				
			}
		}
	*/

	//下边界
	k=0;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
		{
			for (q=0;q<=Q-1;q++)
			{
				if (e[q][2]==1)
				{
					q_contr=q_contrast(q);
					f[i][j][k][q]=fc[i][j][k][q_contr]-6*w[q_contr]*den[i][j][k]*Uw_bottom*e[q_contr][0];
				}
				else
				{
					ip=(i+NX-e[q][0])%NX; 
					jp=(j+NY-e[q][1])%NY;
					kp=(k+NZ-e[q][2])%NZ;
					f[i][j][k][q]=fc[ip][jp][kp][q];
				}
				
			}
			
		}


}















