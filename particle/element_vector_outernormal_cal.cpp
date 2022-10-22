#include <iostream>
using namespace std;

#include "element.h"
void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);

void element::vector_outernormal_cal()
{
	double x01[3], x02[3];
	linear(x01, 1.0, pos[1], -1.0, pos[0]);
	linear(x02, 1.0, pos[2], -1.0, pos[0]);
	double N[3]; //未归一的外法线
	crossproduct(N, x01, x02);
	normalize(vector_outernormal, N);
}
