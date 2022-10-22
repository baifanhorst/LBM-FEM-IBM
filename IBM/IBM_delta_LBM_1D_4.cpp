#include <cmath>
double delta_LBM_1D_4(double x)
{
	double result;
	double r=fabs(x);
	if (r<=1)
	{
		result=1.0/8.0*(3.0-2.0*r+sqrt(1.0+4.0*r-4.0*r*r));
	}
	else if ((r>1)&&(r<2))
	{
		result=1.0/8.0*(5.0-2.0*r-sqrt(-7.0+12.0*r-4.0*r*r));
	}
	else
	{
		result=0;
	}
	return result;
}
