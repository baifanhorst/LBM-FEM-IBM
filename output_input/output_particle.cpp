#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include <fstream>

//考虑到可能有多个particle，输出程序不在particle类当中
//N_par为particle个数，par[N_par]为particle数组
void output_particle(int N_par, particle *par)
{
	ofstream outfile;
	outfile.open("./result/particle/result_particle_pos_vel.txt",ios::out);
	int i,j;
	for (i=0;i<=N_par-1;i++)
	{
		for (j=1;j<=par[i].p_num;j++)
		{
			outfile<<par[i].p[j].pos[0]<<' '<<par[i].p[j].pos[1]<<' '<<par[i].p[j].pos[2]<<' ';
			outfile<<par[i].p[j].vel[0]<<' '<<par[i].p[j].vel[1]<<' '<<par[i].p[j].vel[2]<<endl;
		}
		outfile<<endl;
	}
	outfile.close();
}
