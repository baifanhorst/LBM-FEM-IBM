#include <iostream>
using namespace std;
#include "particle.h"
#include <cmath>

void particle::F_Fs_cal()
{
	int i,j;

	//为Fs_2D分配空间
	double **Fs2D;
	Fs2D=new double *[3];
	for (i=0;i<=2;i++)
	{
		Fs2D[i]=new double [2];
		//分配后顺便置零
		for (j=0;j<=1;j++)
		{
			Fs2D[i][j]=0;
		}
	}


	//单元编号
	int ne;
	//计算每个单元的Fs
	for (ne=1;ne<=e_num;ne++)
	{	//计算Fs2D所需的l l_ fi
		//e[ne].parameter_Fs_cal();
		//计算Fs2D
		//cout<<e[ne].A0<<endl;
		F_Fs2D_cal(Fs2D, e[ne].l0, e[ne].l0_, e[ne].l, e[ne].l_, e[ne].fi0, e[ne].fi, e[ne].A0);
		//cout<<e[ne].l<<' '<<e[ne].l_<<' '<<e[ne].fi<<endl;
		//cout<<e[ne].l0<<' '<<e[ne].l0_<<' '<<e[ne].l<<' '<<e[ne].l_<<' '<<e[ne].fi0<<' '<<e[ne].fi<<' '<<e[ne].A0;
		//cout<<Fs2D[0][0]<<' '<<Fs2D[0][1]<<"    "<<Fs2D[1][0]<<' '<<Fs2D[1][1]<<"    "<<Fs2D[2][0]<<' '<<Fs2D[2][1]<<endl;
		//转换成Fs3D
		F_Fs3D_convert(Fs2D, ne);
	}
	
	
	
	//释放Fs_2D空间
	for (i=0;i<=2;i++)
	{
		delete [] Fs2D[i];
	}
	delete [] Fs2D;
}
