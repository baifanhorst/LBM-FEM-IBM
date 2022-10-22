#include <iostream>
using namespace std;
#include "particle.h"
#include <fstream>


void particle::output_vtk()
{
	ofstream outfile;
	outfile.open("./result/result_particle.vtk",ios::out); //这个路径是a.out所在当前目录下的result文件夹，不是本函数所在当前路径下的result
	outfile << "# vtk DataFile Version 2.0" << endl;
  	outfile << "t=" << 0.0 << endl;
 	outfile << "ASCII" << endl;
  	outfile << "DATASET UNSTRUCTURED_GRID" << endl;
  	outfile << "POINTS " << p_num << " float" << endl;
	int n;
	for(n=1;n<=p_num;n++)
	{
    		outfile << (float)(p[n].pos[0]) << ' ' << (float)(p[n].pos[1]) << ' ' << (float)(p[n].pos[2]) << endl;
  	}
	outfile << "CELLS " << e_num << " " << 4*e_num << endl;
	for(n=1;n<=e_num;n++)
	{
    		outfile << 3 << ' ' << e[n].p_no[0]-1 << ' ' << e[n].p_no[1]-1 << ' ' << e[n].p_no[2]-1 << endl;
  	}
	outfile << "CELL_TYPES " << e_num << endl;
	for(n=1;n<=e_num;n++)
	{
    		outfile << 5 << endl;
  	}	
	outfile << "CELL_DATA " << e_num << endl;
  	outfile << "SCALARS ds float" << endl;
  	outfile << "LOOKUP_TABLE default" << endl;
	for(int n=1;n<=e_num;n++)
	{
		e[n].parameter_Fs_cal();
		e[n].area_cal();
    		outfile << (float)e[n].A << endl;
  	}
	
	outfile.close();
}
