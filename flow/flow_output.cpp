#include <iostream>
#include <fstream>
using namespace std;
#include "flow.h"

void flow::output()
{
	ofstream outfile("./result/flow/result_flow_f.txt",ios::out); //a.out在3D下，结果文件夹为result，其中流场结果放在3D/result/flow中	
	int i,j,k,q;
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				for (q=0;q<=Q-1;q++)
				{
					outfile<<f[i][j][k][q]<<' ';				
				}
				outfile<<'\n';
			}
	outfile.close();
	outfile.open("./result/flow/result_flow_macro.txt",ios::out);
	for (i=0;i<=NX-1;i++)
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				outfile<<den[i][j][k]<<' '<<vis[i][j][k]<<' '
					<<vel[i][j][k][0]<<' '<<vel[i][j][k][1]<<' '<<vel[i][j][k][2]<<'\n';				
			}
	outfile.close(); //以上两个文件用于读取
	outfile.open("./result/flow/result_flow_vel_plot.txt",ios::out);
	double x,y,z;
	for (i=0;i<=NX-1;i++) 
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				x=i; y=j; z=k+0.5;			
				outfile<<x<<' '<<y<<' '<<z<<' '<<vel[i][j][k][0]<<' '<<vel[i][j][k][1]<<' '<<vel[i][j][k][2]<<'\n';
			}
	outfile.close();
	//粘性场
	outfile.open("./result/flow/result_flow_vis_plot.txt",ios::out);
	for (i=0;i<=NX-1;i++) 
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				x=i; y=j; z=k+0.5;			
				outfile<<x<<' '<<y<<' '<<z<<' '<<vis[i][j][k]<<'\n';
			}
	outfile.close();
	//输出mark
	outfile.open("./result/flow/result_flow_mark_plot.txt",ios::out);
	for (i=0;i<=NX-1;i++) 
		for (j=0;j<=NY-1;j++)
			for (k=0;k<=NZ-1;k++)
			{
				x=i; y=j; z=k+0.5;			
				outfile<<x<<' '<<y<<' '<<z<<' '<<mark[i][j][k]<<'\n';
			}
	outfile.close();
	
}

void flow::output_2Dvector(int j) //输出j所在的xz平面的速度场
{
	ofstream outfile("./result/flow/result_flow_2Dvector.txt",ios::out);
	outfile<<"## The vector field for j="<<j<<"##"<<endl;
	int i,k;
	double x,z;
	for (i=0;i<=NX-1;i++)
		for (k=0;k<=NZ-1;k++)
		{
			x=i; z=k+0.5;
			outfile<<x<<' '<<z<<' '<<vel[i][j][k][0]<<' '<<vel[i][j][k][2]<<endl;
		}
}

