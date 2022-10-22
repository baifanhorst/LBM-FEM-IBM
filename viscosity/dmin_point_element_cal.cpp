#include <iostream>
using namespace std;
#include <cmath>

double dmin_point_line_cal(double *P, double *A, double *B);
double length(double *a);
double innerproduct(double *a, double *b);

double min3(double &a, double &b, double &c);
int in_projection_determine(double *x, double *a, double *b, double *c);

double d_point_element_cal(double *P, double *A, double *B, double *C, double *norm) //求P到三角形ABC的有向距离，所以得提供外法线方向
{
	//先求垂足
	double vPA[3];
	int k;
	double pos_proj[3];
	double d_proj; //P到ABP平面的有向距离
	int in_ABC; //投影点是否在三角形ABC内的标志，1为在，0为不在
	double d_P_ABC; //最终结果
	double d_P_AB, d_P_AC, d_P_BC; //P到三条边的距离
	double sign_side; //看P在ABC哪一边
	for (k=0;k<=2;k++)
	{
		vPA[k]=A[k]-P[k];
	}
	d_proj=innerproduct(vPA, norm);
	for (k=0;k<=2;k++)
	{
		pos_proj[k]=P[k]+d_proj*norm[k];
	}
	in_ABC=in_projection_determine(pos_proj, A, B, C);
	if (in_ABC==1)
	{
		d_P_ABC=d_proj;	
	}
	else
	{
		d_P_AB=dmin_point_line_cal(P,A,B);
		d_P_AC=dmin_point_line_cal(P,A,C);
		d_P_BC=dmin_point_line_cal(P,B,C);
		if (d_proj>1e-12)
		{
			sign_side=1;
		}
		else
		{
			sign_side=-1;
		}
		d_P_ABC=min3(d_P_AB, d_P_AC, d_P_BC)*sign_side;
	}
	return d_P_ABC;
	
	
}
