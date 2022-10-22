#include <iostream>
using namespace std;
#include "../particle/particle.h"
#include <fstream>

void input_particle(int N_par, particle *par)
{
	ifstream infile;
	infile.open("./result/particle/result_particle_pos_vel.txt",ios::in);
	int i,j;
	for (i=0;i<=N_par-1;i++)
	{
		for (j=1;j<=par[i].p_num;j++)
		{
			infile>>par[i].p[j].pos[0]>>par[i].p[j].pos[1]>>par[i].p[j].pos[2];
			infile>>par[i].p[j].vel[0]>>par[i].p[j].vel[1]>>par[i].p[j].vel[2];
		}
	}
	infile.close();
}
