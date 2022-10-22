#include <iostream>
using namespace std;

#include <fstream>

int input_t()
{
	ifstream infile;
	infile.open("./result/time/result_t.cpp", ios::in);
	int result;
	infile>>result;
	return result;	
	
}
