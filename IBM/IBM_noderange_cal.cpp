#include <iostream>
using namespace std;
#include <cmath>

void noderange_cal(int *noderange, double h, double pos)
{
	noderange[0]=ceil(pos-h);
	noderange[1]=floor(pos+h);
}
