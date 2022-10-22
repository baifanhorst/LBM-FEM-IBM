#include <iostream>
using namespace std;
#include "element.h"

double innerproduct(double *a, double *b);


void element::V_cal()
{
	double h;
	h=innerproduct(pos[0], vector_outernormal);
	V=A*h/3.0;
}
