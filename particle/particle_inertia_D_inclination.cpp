#include <iostream>
using namespace std;
#include <fstream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <cmath>
using namespace Eigen;

#include "particle.h"

void particle::inertia_D_inclination()
{
	int a,b;
	MatrixXd A(3,3);
	for (a=0;a<=2;a++)
	{
		for (b=0;b<=2;b++)
		{
			A(a,b)=I[a][b];	
		}
	}
	
	EigenSolver<MatrixXd> es(A);	
	
	VectorXcd eigen_I(3),l(3);
	eigen_I=A.eigenvalues();
	
	l(0)=sqrt(2.5*(-eigen_I(0)+eigen_I(1)+eigen_I(2))/V);
	l(1)=sqrt(2.5*(-eigen_I(1)+eigen_I(2)+eigen_I(0))/V);
	l(2)=sqrt(2.5*(-eigen_I(2)+eigen_I(0)+eigen_I(1))/V);
	
	double r[3];
	int i;
	for (i=0;i<=2;i++)
	{
		r[i]=l(i).real();
	}
	double rmax=r[0],rmin=r[0];
	int imax=0; //最大eigenvalue对应的标号
	for (i=1;i<=2;i++)
	{
		if (r[i]>rmax)
		{
			imax=i;
			rmax=r[i];
		}
		if (r[i]<rmin)
		{
			rmin=r[i];
		}
	}
	D=(rmax-rmin)/(rmax+rmin);
	
	inclination_angle=acos(fabs((es.eigenvectors())(0,imax).real()));
	cout<<inclination_angle<<endl;
	
}
