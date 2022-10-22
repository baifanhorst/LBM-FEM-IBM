#include <iostream>
using namespace std;
#include "flow.h"


//求反向格子速度对应的标号
int flow::q_contrast(int q)
{
	int q_contr;
	if (q==0)
		q_contr=0;
	else if (q%2==1)
		q_contr=q+1;
	else
		q_contr=q-1;
	return q_contr;
}
