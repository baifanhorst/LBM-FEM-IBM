#include <iostream>
using namespace std;

int ordernumber(int n, int *a)
{
	int ordernumber=0;
	int i,j;
	for (i=0;i<=n-2;i++)
	{
		for (j=i+1;j<=n-1;j++)
		{
			if (a[i]>a[j])
			{
				ordernumber++;
			}
		}
	}
	return ordernumber;
}
