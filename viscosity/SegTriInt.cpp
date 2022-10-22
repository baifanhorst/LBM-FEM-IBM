#include <iostream>
using namespace std;
#include "../particle/element.h"

char SegPlaneInt(element &ele, double *q, double *r, double *p);
char PointTriInt(double *p, element &ele);

char SegTriInt(element &ele, double *q, double *r)
{
	double p[3]={0,0,0};
	char mark;
	mark=SegPlaneInt(ele, q, r, p);
	if (mark=='o')
	{
		return 'o';
	}
	else if (mark=='i')
	{
		return PointTriInt(p, ele);
	}
	else
	{
		return 'd';
	}
}
