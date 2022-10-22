#include <iostream>
using namespace std;
#include <fstream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
using namespace Eigen;

#include "particle.h"

void particle::inertia_output()
{
	ofstream fout;
	fout.open("./result/inertia/inertia.txt",ios::out);
	int a,b;
	for (a=0;a<=2;a++)
	{
		for (b=0;b<=2;b++)
		{
			fout<<I[a][b]<<' ';	
		}
		fout<<endl;
	}
	MatrixXd A(3,3);
	for (a=0;a<=2;a++)
	{
		for (b=0;b<=2;b++)
		{
			A(a,b)=I[a][b];	
		}
	}
	EigenSolver<MatrixXd> es(A);
	fout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
	fout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;

	
		
	
	fout.close();
}
