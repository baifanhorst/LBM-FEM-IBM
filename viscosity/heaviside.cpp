#include <iostream>
using namespace std;
#include <cmath>
double heaviside(double &d, double &thickness)
{
	double theta;
	const double pi=3.141592653;
	if (d<=-thickness)
	{
		theta=0;
	}
	else if ((d>-thickness)&&(d<thickness))
	{
		theta=0.5*(1+d/thickness+1/pi*sin(pi*d/thickness));
	}
	else
	{
		theta=1;
	}
	return theta;
}
