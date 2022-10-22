#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>



void particle::F_Fs2D_cal(double **F, double l0, double l0_, double l, double l_, double fi0, double fi, double A0)
{
	double a[3],b[3];
	a[0]=-l0*sin(fi0)/(2*A0);
	a[1]=l0*sin(fi0)/(2*A0);
	a[2]=0;
	
	b[0]=(l0*cos(fi0)-l0_)/(2*A0);
	b[1]=-l0*cos(fi0)/(2*A0);
	b[2]=l0_/(2*A0);
	
	double DXX,DXY,DYX,DYY;
	DXX=l_/l0_;
	DXY=(l/l0*cos(fi)-l_/l0_*cos(fi0))/sin(fi0);
	DYX=0;
	DYY=l/l0*sin(fi)/sin(fi0);
	
	double GXX,GXY,GYY;
	GXX=DXX*DXX+DYX*DYX;
	GXY=DXX*DXY+DYX*DYY;
	GYY=DXY*DXY+DYY*DYY;
	
	double I1,I2;
	I1=GXX+GYY-2;
	I2=GXX*GYY-GXY*GXY-1;
	
	double pEpI1,pEpI2;
	//这里改用Neo-Hookean
	//pEpI1=ks/6*(I1+1); 
	pEpI1=ks/6;
	//pEpI2=-ks/6+k_alpha/6*I2;
	pEpI2=-ks/6/(I2+1)/(I2+1);
	
	double pGXXpV[3][2],pGXYpV[3][2],pGYYpV[3][2];
	int i;
	for (i=0;i<=2;i++)
	{
		pGXXpV[i][0]=2*a[i]*DXX;
		pGXXpV[i][1]=0;
		
		pGXYpV[i][0]=a[i]*DXY+b[i]*DXX;
		pGXYpV[i][1]=a[i]*DYY;
		
		pGYYpV[i][0]=2*b[i]*DXY;
		pGYYpV[i][1]=2*b[i]*DYY;
	}
	
	double pI1pV[3][2], pI2pV[3][2];
	int j;
	for (i=0;i<=2;i++)
		for (j=0;j<=1;j++)
		{
			pI1pV[i][j]=pGXXpV[i][j]+pGYYpV[i][j];
			pI2pV[i][j]=GYY*pGXXpV[i][j]-2*GXY*pGXYpV[i][j]+GXX*pGYYpV[i][j];
		}
	
	for (i=0;i<=2;i++)
		for (j=0;j<=1;j++)
		{
			F[i][j]=-(pEpI1*pI1pV[i][j]+pEpI2*pI2pV[i][j])*A0;
		}
 
}
