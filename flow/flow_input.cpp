#include <iostream>
#include <fstream>
using namespace std;
#include "flow.h"

void flow::input()
{
	ifstream infile;
	infile.open("./result/flow/result_flow_f.txt",ios::in);
	int i,j,k,q;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				for (q=0;q<=Q-1;q++)
				{
					infile>>f[i][j][k][q];
				}
			}
	infile.close();
	double x,y,z;
	infile.open("./result/flow/result_flow_macro.txt",ios::in);
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				infile>>den[i][j][k]>>vis[i][j][k]>>vel[i][j][k][0]>>vel[i][j][k][1]>>vel[i][j][k][2];
			}
	infile.close();
}
