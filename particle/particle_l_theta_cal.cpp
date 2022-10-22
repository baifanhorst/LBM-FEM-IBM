#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);

void particle::l_theta_cal()
{
	int nl;
	double ninj; //边相邻两个单元外法线向量的内积
	for (nl=1;nl<=l_num;nl++)
	{
		ninj=innerproduct(e[l[nl].e_no[0]].vector_outernormal, e[l[nl].e_no[1]].vector_outernormal);
		l[nl].theta=acos(ninj); 
	}
}
