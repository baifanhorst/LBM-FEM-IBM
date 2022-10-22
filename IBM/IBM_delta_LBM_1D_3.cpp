#include <cmath>
double delta_LBM_1D_3(double x)
{
	double result;
	double r=fabs(x);
	if (r<=0.5)
	{
		result=1.0/3.0*(1+sqrt(1-3.0*r*r));
	}
	else if ((r>0.5)&&(r<1.5))
	{
		result=1.0/6.0*(5.0-3.0*r-sqrt(-2.0+6.0*r-3.0*r*r));
	}
	else
	{
		result=0;
	}
	return result;
}
