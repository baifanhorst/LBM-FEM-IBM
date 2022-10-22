#include <iostream>
using namespace std;
#include "flow.h"

flow::flow(int nx, int ny, int nz)
{
	//节点数，速度种类(D3Q19)	
	NX=nx; NY=ny; NZ=nz; Q=19; 
	//权系数 w[q] q=0->18
	w=new double[Q];          
	w[0]=1.0/3.0;
	int i,j,k;
	for (i=1;i<=6;i++)
		w[i]=1.0/18.0;
	for (i=7;i<=18;i++)
		w[i]=1.0/36.0;
	//微观速度 e[q][direction] direction=0,1,2 (x,y,z)
	e=new int*[Q];           
	for (i=0;i<=Q-1;i++)
		e[i]=new int[3];
	//0
	e[0][0]=0;    e[0][1]=0;   e[0][2]=0;
	//1-6
	e[1][0]=1;    e[1][1]=0;   e[1][2]=0;
	e[2][0]=-1;   e[2][1]=0;   e[2][2]=0;

	e[3][0]=0;    e[3][1]=1;   e[3][2]=0;
	e[4][0]=0;    e[4][1]=-1;  e[4][2]=0;

	e[5][0]=0;    e[5][1]=0;   e[5][2]=1;
	e[6][0]=0;    e[6][1]=0;   e[6][2]=-1;
	//7-19
	e[7][0]=1;    e[7][1]=1;   e[7][2]=0;
	e[8][0]=-1;   e[8][1]=-1;  e[8][2]=0;

	e[9][0]=1;    e[9][1]=-1;  e[9][2]=0;
	e[10][0]=-1;  e[10][1]=1;  e[10][2]=0;

	e[11][0]=1;   e[11][1]=0;  e[11][2]=1;
	e[12][0]=-1;  e[12][1]=0;  e[12][2]=-1;

	e[13][0]=1;   e[13][1]=0;  e[13][2]=-1;
	e[14][0]=-1;  e[14][1]=0;  e[14][2]=1;

	e[15][0]=0;   e[15][1]=1;  e[15][2]=1;
	e[16][0]=0;   e[16][1]=-1; e[16][2]=-1;

	e[17][0]=0;   e[17][1]=1;  e[17][2]=-1;
	e[18][0]=0;   e[18][1]=-1; e[18][2]=1;
	
	//f,fc,feq 分布函数，碰撞后分布函数，平衡态分布函数 f[i][j][k][q] i=0->NX-1 j=0->NY-1 k=0->NZ-1
	f=  new double***[NX];           
	fc= new double***[NX];
	feq=new double***[NX];
		
	
	
	
	for (i=0;i<=NX-1;i++)
	{
		f[i]=  new double**[NY];
		fc[i]= new double**[NY];
		feq[i]=new double**[NY];
		for (j=0;j<=NY-1;j++)
		{
			f[i][j]=  new double*[NZ];
			fc[i][j]= new double*[NZ];
			feq[i][j]=new double*[NZ];
			for (k=0;k<=NZ-1;k++)
			{
				f[i][j][k]=   new double [Q];
				fc[i][j][k]=  new double [Q];
				feq[i][j][k]= new double [Q];
			}
		}
	}
		
	//宏观量
	vel=      new double***[NX];    //vel[i][j][k][direction] direction=0,1,2
	vel_old=  new double***[NX];    
	bodyforce=new double***[NX];	//bodyforce[i][j][k][direction]
	den=new double**[NX];	//den[i][j][k]
	vis=new double**[NX];	//vis[i][j][k]
	//标志场
	mark=new int**[NX];
	
	//节点位置
	pos=new double ***[NX];
	
	for (i=0;i<=NX-1;i++)
	{
		vel[i]=       new double**[NY];
		vel_old[i]=   new double**[NY];
		bodyforce[i]= new double**[NY];
	
		pos[i]=       new double**[NY];		
		
		den[i]=       new double*[NY];
		vis[i]=       new double*[NY];
		//标志场
		mark[i]=new int*[NY];

		for (j=0;j<=NY-1;j++)
		{
			vel[i][j]=      new double*[NZ];
			vel_old[i][j]=  new double*[NZ];
			bodyforce[i][j]=new double*[NZ];
			
			pos[i][j]=      new double*[NZ];			
			
			den[i][j]=      new double [NZ];
			vis[i][j]=      new double [NZ];
			
			mark[i][j]=     new int [NZ];
			for (k=0;k<=NZ-1;k++)
			{
				vel[i][j][k]=      new double [3];
				vel_old[i][j][k]=  new double [3];
				bodyforce[i][j][k]=new double [3];
				pos[i][j][k]=      new double [3];
			}
		}
	}
	
	cout<<"flow construction completed"<<endl;	
}


flow::~flow() //释放空间
{	
	//高维数组必须逐层释放	
	//释放w	
	delete [] w;    
	//释放e
	int i;
	for (i=0;i<=Q-1;i++)
		delete [] e[i];
	delete [] e;   
	
	//释放f,fc,feq,vel,bodyforce,vis,den
	int j,k;
	for (i=0;i<=NX-1;i++)
	{	for (j=0;j<=NY-1;j++)
		{
			for (k=0;k<=NZ-1;k++)
			{
				delete [] f[i][j][k];
				delete [] fc[i][j][k];
				delete [] feq[i][j][k];
				delete [] vel[i][j][k];
				delete [] vel_old[i][j][k];
				delete [] bodyforce[i][j][k];
				delete [] pos[i][j][k];
			}
			delete [] f[i][j];
			delete [] fc[i][j];
			delete [] feq[i][j];
			delete [] vel[i][j];
			delete [] vel_old[i][j];
			delete [] bodyforce[i][j];
			delete [] pos[i][j];
			delete [] vis[i][j];
			delete [] den[i][j];
	
			delete [] mark[i][j];
		}
		delete [] f[i];
		delete [] fc[i];
		delete [] feq[i];
		delete [] vel[i];
		delete [] vel_old[i];
		delete [] bodyforce[i];
		delete [] pos[i];
		delete [] vis[i];
		delete [] den[i];
		
		delete [] mark[i];
	}
	delete [] f;
	delete [] fc;
	delete [] feq;
	delete [] vel;
	delete [] vel_old;
	delete [] bodyforce;
	delete [] pos;
	delete [] vis;
	delete [] den;  
	delete [] mark;
	cout<<"flow destruction completed"<<endl;	
}
