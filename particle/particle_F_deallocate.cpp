#include <iostream>
using namespace std;
#include "particle.h"

void particle::F_deallocate()
{
	int i;
	for (i=1;i<=p_num;i++)
	{
		delete [] F[i];
	}
	delete [] F;
}
