#include <iostream>
using namespace std;

#include <fstream>

void output_t(int t)
{
	ofstream outfile;
	outfile.open("./result/time/result_t.cpp", ios::out);
	outfile<<t;
	outfile.close();
}
