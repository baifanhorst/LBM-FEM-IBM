#include <iostream>
using namespace std;
double area2Dsigned(double *p0, double *p1, double *p2);

char PointTriInt2D(double *p, double *v0, double *v1, double *v2)
{
	double S_p01,S_p12,S_p20;
	S_p01=area2Dsigned(p, v0, v1);
	S_p12=area2Dsigned(p, v1, v2);
	S_p20=area2Dsigned(p, v2, v0);
	
	if (((S_p01>0)&&(S_p12>0)&&(S_p20>0))||((S_p01<0)&&(S_p12<0)&&(S_p20<0)))
	{
		return 'i';
	}
	else if (((S_p01==0)&&(S_p12>0)&&(S_p20>0))||
		 ((S_p01==0)&&(S_p12<0)&&(S_p20<0))||
		 ((S_p01>0)&&(S_p12==0)&&(S_p20>0))||
		 ((S_p01<0)&&(S_p12==0)&&(S_p20<0))||
		 ((S_p01>0)&&(S_p12>0)&&(S_p20==0))||
		 ((S_p01<0)&&(S_p12<0)&&(S_p20==0))||
		 ((S_p01==0)&&(S_p12==0))||
		 ((S_p12==0)&&(S_p20==0))||
		 ((S_p20==0)&&(S_p01==0)))
	{
		return 'd'; //p在边上或者角点上，一律算作d（degeneracy）
	}
	else
	{
		return 'o';
	}
}
