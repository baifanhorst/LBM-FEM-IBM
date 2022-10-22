#include <iostream>
using namespace std;
#include "element.h"
#include <cmath>

void element::parameter_Fs_init_cal()
{
	parameter_Fs_cal();
	area_cal();
	l0=l;
	l0_=l_;
	fi0=fi;
	A0=A;
}
