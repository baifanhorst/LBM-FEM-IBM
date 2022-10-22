#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include "../particle/element.h"
//点到particle的最小距离
double d_p_element_cal(double *pos, element &e);

double d_p_particle_cal(double *pos, particle &par)
{
	double d;
	double d_temp;
	d=d_p_element_cal(pos, par.e[1]);
	//cout<<"p-e1="<<d<<endl;
	int ne;
	for (ne=2;ne<=par.e_num;ne++)
	{
		//cout<<"p-e"<<ne<<"="<<d_temp<<endl;
		d_temp=d_p_element_cal(pos, par.e[ne]);
		if (d_temp<d)
		{
			d=d_temp;
		}
	}
	return d;
}
