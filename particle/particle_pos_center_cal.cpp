#include <iostream>
using namespace std;
#include "particle.h"
#include <stdio.h>


void particle::pos_center_cal()
{
	
	int ne,k;
	//计算三个方向的型心
	double xk,nk,dA;
	for (k=0;k<=2;k++)
	{
		pos_center[k]=0;
		//#pragma omp parallel for private(ne,xk,nk,dA)
		for (ne=1;ne<=e_num;ne++)
		{
			e[ne].pos_center_abs[k]=(e[ne].pos[0][k]+e[ne].pos[1][k]+e[ne].pos[2][k])/3.0;
			xk=e[ne].pos_center_abs[k];
			nk=e[ne].vector_outernormal[k];
			dA=e[ne].A;
			pos_center[k]=pos_center[k]+0.5*xk*xk*nk*dA;
		}
		pos_center[k]=pos_center[k]/V;
	}
}
