#include <iostream>
using namespace std;
#include "../particle/element.h"


double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);

//源代码中有计算外法线方向最大分量的code，这里没有
//i:相交  o：不相交  d：degeneracy（这里对应seg在plane上）
char SegPlaneInt(element &ele, double *q, double *r, double *p)
{
	double D;
	D=innerproduct(ele.pos[0], ele.vector_outernormal);
	double num, denom;
	double qr[3]; //q指向r的向量
	linear(qr,1,r,-1,q);
	denom=innerproduct(qr, ele.vector_outernormal);
	num=D-innerproduct(q, ele.vector_outernormal);	
	double t;
		
	if (denom==0.0)
	{
		if (num==0.0)
		{
			return 'd';
		}
		else
		{
			return 'o';
		}
	}
	else
	{
		t=num/denom;
	}	
	linear(p,1,q,t,qr);
	if ((t>0.0)&&(t<1.0))
	{
		return 'i';
	}
	else
	{
		return 'o';
	}
}
