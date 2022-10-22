#include <iostream>
using namespace std;

void crossproduct(double *p, double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);
double length(double *a);

double tri_area_cal(double *a, double *b, double *c)
{
	double ab[3],ac[3];
	linear(ab, -1, a, 1, b);
	linear(ac, -1, a, 1, c);
	double ab_cross_ac[3];
	crossproduct(ab_cross_ac, ab, ac);
	double area;
	area=0.5*length(ab_cross_ac);
	return area;
}
