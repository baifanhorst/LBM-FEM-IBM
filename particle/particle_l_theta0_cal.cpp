#include <iostream>
using namespace std;
#include "particle.h"

void particle::l_theta0_cal()
{
	l_theta_cal();
	int nl;
	for (nl=1;nl<=l_num;nl++)
	{
		l[nl].theta0=l[nl].theta;
		cout<<l[nl].theta0<<endl;
	}
}
