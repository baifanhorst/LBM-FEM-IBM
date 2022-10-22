#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>

void particle::parameter_init()
{
	
	parameter_cal();
	
	int ne;
	for (ne=1;ne<=e_num;ne++)
	{
		e[ne].l0=e[ne].l;
		e[ne].l0_=e[ne].l_;
		e[ne].fi0=e[ne].fi; 
		e[ne].A0=e[ne].A; 
	}
	A0=A;
	V0=V;
	int nl;
	for (nl=1;nl<=l_num;nl++)
	{
		l[nl].theta0=l[nl].theta;
	}
	
}
