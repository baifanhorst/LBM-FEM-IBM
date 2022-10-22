#include <iostream>
#include <fstream>
using namespace std;
#include "flow.h"


//y截面输出粘性
void flow::output_vis2D_y(int ny)
{
	ofstream outfile;
	outfile.open("./result/result_vis2D_y.vtk",ios::out);
	int i,k;
	for (i=0;i<=NX-1;i++)
	{
		for (k=0;k<=NZ-1;k++)
		{
			outfile<<i<<' '<<k+0.5<<' '<<vis[i][ny][k]<<endl;
		}
		outfile<<endl;
	}
	outfile.close();
}
