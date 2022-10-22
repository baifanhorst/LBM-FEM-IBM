#include <iostream>
using namespace std;
#include "../particle/element.h"
#include <cmath>

double innerproduct(double *a, double *b);
void linear(double *result, double x1, double *v1, double x2, double *v2);
void equal(double *result, double *a);
char PointTriInt(double *p, element &ele);
double min3(double &a, double &b, double &c);
double dmin_point_line_cal(double *P, double *A, double *B);


double d_p_element_cal(double *pos, element &e)
{
	double d;
	//求投影
	double *q, *r;
	q=pos;
	r=e.pos[0];
	double d_proj;
	double qr[3];
	linear(qr,1,r,-1,q);
	d_proj=innerproduct(qr, e.vector_outernormal);
	//cout<<"d_proj="<<d_proj<<endl;
	//cout<<"outernormal="<<e.vector_outernormal[0]<<' '<<e.vector_outernormal[1]<<' '<<e.vector_outernormal[2]<<endl;
	double proj[3];
	linear(proj, 1, q, d_proj, e.vector_outernormal);
	//cout<<"proj="<<proj[0]<<' '<<proj[1]<<' '<<proj[2]<<endl;	
	
	char p_tri_int=PointTriInt(proj, e);
	if ((p_tri_int=='i')||(p_tri_int=='d'))
	{
		//cout<<"i or d"<<endl;
		d=fabs(d_proj);
	}
	else
	{
		//cout<<"else"<<endl;
		double d01,d12,d20;
		d01=dmin_point_line_cal(q, e.pos[0], e.pos[1]); //cout<<"d01="<<d01<<endl;
		d12=dmin_point_line_cal(q, e.pos[1], e.pos[2]); //cout<<"d12="<<d12<<endl;
		d20=dmin_point_line_cal(q, e.pos[2], e.pos[0]); //cout<<"d20="<<d20<<endl;
		
		d=min3(d01,d12,d20);
	}
	return d;
	
	
	
}
