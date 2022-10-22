#include <iostream>
using namespace std;
double tri_area_cal(double *a, double *b, double *c);


int in_projection_determine(double *x, double *a, double *b, double *c)
{
	double S_abc, S_xab, S_xac, S_xbc;
	S_abc=tri_area_cal(a, b, c);
	S_xab=tri_area_cal(x, a, b);
	S_xac=tri_area_cal(x, a, c);
	S_xbc=tri_area_cal(x, b, c);
	
	if (S_xab+S_xac+S_xbc<S_abc+1e-10)   //计算有误差
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}
