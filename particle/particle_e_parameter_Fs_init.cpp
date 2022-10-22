#include <iostream>
using namespace std;
#include "particle.h"

void particle::e_parameter_Fs_init()
{
	int ne;
	for (ne=1;ne<=e_num;ne++)
	{
		e[ne].parameter_Fs_init_cal();
	}
}
