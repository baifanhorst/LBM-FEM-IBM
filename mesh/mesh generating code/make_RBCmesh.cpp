#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

#define GNN 80
#define UNN (40*GNN*GNN)

//////////////////
//Prototype
//////////////////

//Init
void Param();
void Init();
void Init_Sub(int,int,int,int,int,double [],double [],double []);

//Data
void Dat_Write();

//Make_Grid
void Make_Grid();
void Solve(double *,double *,double *,double,double,double,double,double,
	   double,double,double,double,double,double);

//Unstructured_Grid Info
void Unst_Info();
void Bd_Sub(int,int,int,int,int,int [],int [],int [],int []);
void Ve_Sub(int,double [],double [],double [],double,double,double);
void ElVe_Sub(int,int,int,int []);
void ElEl_Sub(int,int,int,int);

//Biconcave
void Biconcave();
void rotate(double,double,double,double &,double &,double &);

//////////////////
//Variable
//////////////////

//Grid
int Ndiv,nd;
double x[11][GNN][GNN],y[11][GNN][GNN],z[11][GNN][GNN];

//Unstructured Grid & Info
int non,nos,noe;
int Pnum[UNN],Pne[7][UNN];
int Lb[UNN],Lf[UNN],Nb[UNN],Nf[UNN];
int Ve[5][UNN],Su[4][UNN],El[4][UNN];
double xu[UNN],yu[UNN],zu[UNN];

//////////////////
//Main
//////////////////
main()
{
  Param();
  Init();

  Make_Grid();
  Unst_Info();
  Biconcave();

  Dat_Write();

  cout << "Ndiv=" << Ndiv << endl;
  cout << " The number of Vertex=" << non << ", Surface=" << nos << ", Element=" << noe << endl;
}

//////////////////
//Init
//////////////////

//Param
void Param()
{
  Ndiv=10;  Ndiv=4;
  nd=Ndiv+1;
}

//Init_Icosahedral
void Init()
{
  int n;
  double a,b,c,d,e;
  double xp[13],yp[13],zp[13];

  //Vertex_Pt
  a=1.0/sqrt(5.0);
  b=0.5*(1.0-a);
  c=0.5*(1.0+a);
  d=sqrt(b);
  e=sqrt(c);

  xp[1]=0.0;
  yp[1]=0.0;
  zp[1]=1.0;
  xp[2]=2.0*a;
  yp[2]=0.0;
  zp[2]=a;
  xp[3]=b;
  yp[3]=e;
  zp[3]=a;
  xp[4]=-c;
  yp[4]=d;
  zp[4]=a;
  xp[5]=-c;
  yp[5]=-d;
  zp[5]=a;
  xp[6]=b; 
  yp[6]=-e;
  zp[6]=a;
  xp[7]=0.0;
  yp[7]=0.0;
  zp[7]=-1.0;
  xp[8]=c;
  yp[8]=d;
  zp[8]=-a;
  xp[9]=-b;
  yp[9]=e;
  zp[9]=-a;
  xp[10]=-2.0*a;
  yp[10]=0.0;
  zp[10]=-a;
  xp[11]=-b;
  yp[11]=-e;
  zp[11]=-a;
  xp[12]=c;
  yp[12]=-d;
  zp[12]=-a;

  //Top
  Init_Sub(1,2,8,1,3,xp,yp,zp);
  Init_Sub(2,3,9,1,4,xp,yp,zp);
  Init_Sub(3,4,10,1,5,xp,yp,zp);
  Init_Sub(4,5,11,1,6,xp,yp,zp);
  Init_Sub(5,6,12,1,2,xp,yp,zp);

  //Bottom
  Init_Sub(6,8,7,3,9,xp,yp,zp);
  Init_Sub(7,9,7,4,10,xp,yp,zp);
  Init_Sub(8,10,7,5,11,xp,yp,zp);
  Init_Sub(9,11,7,6,12,xp,yp,zp);
  Init_Sub(10,12,7,2,8,xp,yp,zp);
}

//Init_Sub
void Init_Sub(int n,int p1,int p2,int p3,int p4,double xp[],double yp[],double zp[])
{
  x[n][1][1]=xp[p1];
  y[n][1][1]=yp[p1];
  z[n][1][1]=zp[p1];
  x[n][nd][1]=xp[p2];
  y[n][nd][1]=yp[p2];
  z[n][nd][1]=zp[p2];
  x[n][1][nd]=xp[p3];
  y[n][1][nd]=yp[p3];
  z[n][1][nd]=zp[p3];
  x[n][nd][nd]=xp[p4];
  y[n][nd][nd]=yp[p4];
  z[n][nd][nd]=zp[p4];
}

//////////////////
//Data
//////////////////
void Dat_Write()
{
  ofstream fout;
  double xa,ya,za,xb,yb,zb,rx,ry,rz,ds;

  //Unst_Data
  fout.open("mesh_RBC.cal");
  fout << non << ' ' << nos << ' ' << noe << ' ' << 6 << endl;	//点 边 单元 每个节点连接的最大单元个数:：6
  for(int n=1;n<=non;n++){
    fout << xu[n] << ' ' << yu[n] << ' ' << zu[n] << endl; //结点坐标
  }
  for(int n=1;n<=non;n++){
    fout << Pnum[n] << endl;	//结点连接有多少个单元：5或者6
    for(int i=1;i<=Pnum[n];i++){
      fout << Pne[i][n] << endl;	//每个单元的编号
    }
  }
  for(int n=1;n<=nos;n++){
    fout << Lb[n] << ' ' << Lf[n] << ' ' << Nb[n] << ' ' << Nf[n] << endl;  //结点编号 单元编号
  }
  for(int n=1;n<=noe;n++){	
    fout << Ve[1][n] << ' ' << Ve[2][n] << ' ' << Ve[3][n] << ' '	//3个结点编号
         << El[1][n] << ' ' << El[2][n] << ' ' << El[3][n] << endl;	//3个相邻单元编号？
  }
  fout.close();

  
  //check
  fout.open("check.vtk");
  fout << "# vtk DataFile Version 2.0" << endl;
  fout << "t=" << 0.0 << endl;
  fout << "ASCII" << endl;
  fout << "DATASET UNSTRUCTURED_GRID" << endl;
  fout << "POINTS " << non << " float" << endl;
  for(int n=1;n<=non;n++){
    fout << (float)xu[n] << ' ' << (float)yu[n] << ' ' << (float)zu[n] << endl;
  }
  fout << "CELLS " << noe << " " << 4*noe << endl;
  for(int n=1;n<=noe;n++){
    fout << 3 << ' ' << Ve[1][n]-1 << ' ' << Ve[2][n]-1 << ' ' << Ve[3][n]-1 << endl;
  }
  fout << "CELL_TYPES " << noe << endl;
  for(int n=1;n<=noe;n++){
    fout << 5 << endl;
  }
  fout << "CELL_DATA " << noe << endl;
  fout << "SCALARS ds float" << endl;
  fout << "LOOKUP_TABLE default" << endl;
  for(int n=1;n<=noe;n++){
    xa=xu[Ve[2][n]]-xu[Ve[1][n]];
    ya=yu[Ve[2][n]]-yu[Ve[1][n]];
    za=zu[Ve[2][n]]-zu[Ve[1][n]];
    xb=xu[Ve[3][n]]-xu[Ve[1][n]];
    yb=yu[Ve[3][n]]-yu[Ve[1][n]];
    zb=zu[Ve[3][n]]-zu[Ve[1][n]];
    rx=ya*zb-za*yb;
    ry=za*xb-xa*zb;
    rz=xa*yb-ya*xb;
    ds=0.5*sqrt(rx*rx+ry*ry+rz*rz);
    fout << (float)ds << endl;
  }
  fout.close();
  
}

//////////////////
//Make_Grid
//////////////////
void Make_Grid()
{
  int n,i,j;
  double rr;
  double x1,y1,z1,x2,y2,z2;
  double a1,a2,a3,r1,r2;

  for(n=1;n<=10;n++){

    ///////////////
    //Boundary
    ///////////////

    //1-1 to nd-1
    x1=x[n][1][1];
    y1=y[n][1][1];
    z1=z[n][1][1];
    x2=x[n][nd][1];
    y2=y[n][nd][1];
    z2=z[n][nd][1];
    a1=y1*z2-z1*y2;
    a2=z1*x2-x1*z2;
    a3=x1*y2-y1*x2;
    rr=acos(x1*x2+y1*y2+z1*z2);
    for(i=2;i<=nd-1;i++){
      r1=cos((double)(i-1)/Ndiv*rr);
      r2=cos((1.0-(double)(i-1)/Ndiv)*rr);
      Solve(&x[n][i][1],&y[n][i][1],&z[n][i][1],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
    }

    //1-nd to nd-nd
    x1=x[n][1][nd];
    y1=y[n][1][nd];
    z1=z[n][1][nd];
    x2=x[n][nd][nd];
    y2=y[n][nd][nd];
    z2=z[n][nd][nd];
    a1=y1*z2-z1*y2;
    a2=z1*x2-x1*z2;
    a3=x1*y2-y1*x2;
    rr=acos(x1*x2+y1*y2+z1*z2);
    for(i=2;i<=nd-1;i++){
      r1=cos((double)(i-1)/Ndiv*rr);
      r2=cos((1.0-(double)(i-1)/Ndiv)*rr);
      Solve(&x[n][i][nd],&y[n][i][nd],&z[n][i][nd],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
    }

    //1-1 to 1-nd
    x1=x[n][1][1];
    y1=y[n][1][1];
    z1=z[n][1][1];
    x2=x[n][1][nd];
    y2=y[n][1][nd];
    z2=z[n][1][nd];
    a1=y1*z2-z1*y2;
    a2=z1*x2-x1*z2;
    a3=x1*y2-y1*x2;
    rr=acos(x1*x2+y1*y2+z1*z2);
    for(j=2;j<=nd-1;j++){
      r1=cos((double)(j-1)/Ndiv*rr);
      r2=cos((1.0-(double)(j-1)/Ndiv)*rr);
      Solve(&x[n][1][j],&y[n][1][j],&z[n][1][j],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
    }

    //nd-1 to nd-nd
    x1=x[n][nd][1];
    y1=y[n][nd][1];
    z1=z[n][nd][1];
    x2=x[n][nd][nd];
    y2=y[n][nd][nd];
    z2=z[n][nd][nd];
    a1=y1*z2-z1*y2;
    a2=z1*x2-x1*z2;
    a3=x1*y2-y1*x2;
    rr=acos(x1*x2+y1*y2+z1*z2);
    for(j=2;j<=nd-1;j++){
      r1=cos((double)(j-1)/Ndiv*rr);
      r2=cos((1.0-(double)(j-1)/Ndiv)*rr);
      Solve(&x[n][nd][j],&y[n][nd][j],&z[n][nd][j],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
    }

    //1-1 to nd-nd
    x1=x[n][1][1];
    y1=y[n][1][1];
    z1=z[n][1][1];
    x2=x[n][nd][nd];
    y2=y[n][nd][nd];
    z2=z[n][nd][nd];
    a1=y1*z2-z1*y2;
    a2=z1*x2-x1*z2;
    a3=x1*y2-y1*x2;
    rr=acos(x1*x2+y1*y2+z1*z2);
    for(i=2;i<=nd-1;i++){
      r1=cos((double)(i-1)/Ndiv*rr);
      r2=cos((1.0-(double)(i-1)/Ndiv)*rr);
      Solve(&x[n][i][i],&y[n][i][i],&z[n][i][i],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
    }

    ///////////////
    //Interior
    ///////////////

    //Tri1
    for(i=2;i<=nd-1;i++){
      x1=x[n][i][i];
      y1=y[n][i][i];
      z1=z[n][i][i];
      x2=x[n][i][nd];
      y2=y[n][i][nd];
      z2=z[n][i][nd];
      a1=y1*z2-z1*y2;
      a2=z1*x2-x1*z2;
      a3=x1*y2-y1*x2;
      rr=acos(x1*x2+y1*y2+z1*z2);
      for(j=i+1;j<=nd-1;j++){
	r1=cos((double)(j-i)/(nd-i)*rr);
	r2=cos((1.0-(double)(j-i)/(nd-i))*rr);
	Solve(&x[n][i][j],&y[n][i][j],&z[n][i][j],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
      }
    }

    //Tri2
    for(i=2;i<=nd-1;i++){
      x1=x[n][i][1];
      y1=y[n][i][1];
      z1=z[n][i][1];
      x2=x[n][i][i];
      y2=y[n][i][i];
      z2=z[n][i][i];
      a1=y1*z2-z1*y2;;
      a2=z1*x2-x1*z2;
      a3=x1*y2-y1*x2;
      rr=acos(x1*x2+y1*y2+z1*z2);
      for(j=2;j<=i-1;j++){
	r1=cos((double)(j-1)/(i-1)*rr);
	r2=cos((1.0-(double)(j-1)/(i-1))*rr);
	Solve(&x[n][i][j],&y[n][i][j],&z[n][i][j],r1,r2,x1,y1,z1,x2,y2,z2,a1,a2,a3);
      }
    }
  }
}

//Matrix_Solve
void Solve(double *xx,double *yy,double *zz,double r1,double r2,
	   double a1,double b1,double c1,double a2,double b2,double c2,
	   double a3,double b3,double c3)
{
  double d;

  d=1.0/(-a3*b2*c1+a3*b1*c2+b2*a1*c3+a2*b3*c1-a1*b3*c2-b1*a2*c3);

  *xx=-(c2*b3*r1-r2*b3*c1+c3*b1*r2-c3*b2*r1)*d;
  *yy=(-c3*r1*a2+a3*c2*r1+c3*a1*r2-a3*r2*c1)*d;
  *zz=-(-a2*b3*r1-a3*b1*r2+a3*b2*r1+a1*b3*r2)*d;
}

//////////////////
//Unstruct_Info
//////////////////
void Unst_Info()
{
  int ct,n,k,i,j;
  int bL[11],bR[11],bB[11],bT[11];
  int VeCh[UNN],ElCh[UNN];
  double volume;

  //Total_Number
  non=10*Ndiv*Ndiv+2;
  nos=30*Ndiv*Ndiv;
  noe=20*Ndiv*Ndiv;

  //Boundary_Negih
  Bd_Sub(1,5,6,10,2,bL,bR,bB,bT);
  Bd_Sub(2,1,7,6,3,bL,bR,bB,bT);
  Bd_Sub(3,2,8,7,4,bL,bR,bB,bT);
  Bd_Sub(4,3,9,8,5,bL,bR,bB,bT);
  Bd_Sub(5,4,10,9,1,bL,bR,bB,bT);
  Bd_Sub(6,1,7,10,2,bL,bR,bB,bT);
  Bd_Sub(7,2,8,6,3,bL,bR,bB,bT);
  Bd_Sub(8,3,9,7,4,bL,bR,bB,bT);
  Bd_Sub(9,4,10,8,5,bL,bR,bB,bT);
  Bd_Sub(10,5,6,9,1,bL,bR,bB,bT);

  //Init
  for(n=1;n<=noe;n++){
    VeCh[n]=0;
  }

  ////////////////
  //Vertex
  ////////////////

  //Singular_Pt
  Pnum[1]=5;
  Ve_Sub(1,xu,yu,zu,x[1][1][nd],y[1][1][nd],z[1][1][nd]);
  for(k=1;k<=5;k++){
    ElVe_Sub(1,k,2*Ndiv*Ndiv*(k-1)+2*Ndiv,VeCh);
  }

  for(n=1;n<=5;n++){
    Pnum[n+1]=5;
    Ve_Sub(n+1,xu,yu,zu,x[n][1][1],y[n][1][1],z[n][1][1]);
    ElVe_Sub(n+1,1,2*Ndiv*Ndiv*(n-1)+1,VeCh);
    ElVe_Sub(n+1,2,2*Ndiv*Ndiv*(n-1)+2,VeCh);
    ElVe_Sub(n+1,3,2*Ndiv*Ndiv*bL[n],VeCh);
    ElVe_Sub(n+1,4,2*Ndiv*Ndiv*bL[n]-1,VeCh);
    ElVe_Sub(n+1,5,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv,VeCh);
  }

  Pnum[7]=5;
  Ve_Sub(7,xu,yu,zu,x[6][nd][1],y[6][nd][1],z[6][nd][1]);
  for(k=1;k<=5;k++){
    ElVe_Sub(7,k,2*Ndiv*Ndiv*(k+4)+2*Ndiv*(Ndiv-1)+1,VeCh);
  }

  for(n=1;n<=5;n++){
    Pnum[n+7]=5;
    Ve_Sub(n+7,xu,yu,zu,x[n+5][1][1],y[n+5][1][1],z[n+5][1][1]);
    ElVe_Sub(n+7,1,2*Ndiv*Ndiv*(n+4)+1,VeCh);
    ElVe_Sub(n+7,2,2*Ndiv*Ndiv*(n+4)+2,VeCh);
    ElVe_Sub(n+7,3,2*Ndiv*Ndiv*(bL[n+5]-1)+2*Ndiv*(Ndiv-1)+1,VeCh);
    ElVe_Sub(n+7,4,2*Ndiv*Ndiv*bB[n+5],VeCh);
    ElVe_Sub(n+7,5,2*Ndiv*Ndiv*bB[n+5]-1,VeCh);
  }

  //Boundary_Pt
  ct=12;
  for(n=1;n<=5;n++){
    for(j=2;j<=nd-1;j++){
      ct++;
      Pnum[ct]=6;
      Ve_Sub(ct,xu,yu,zu,x[n][1][j],y[n][1][j],z[n][1][j]);
      ElVe_Sub(ct,1,2*Ndiv*Ndiv*(n-1)+2*(j-1),VeCh);
      ElVe_Sub(ct,2,2*Ndiv*Ndiv*(n-1)+2*(j-1)+1,VeCh);
      ElVe_Sub(ct,3,2*Ndiv*Ndiv*(n-1)+2*(j-1)+2,VeCh);
      ElVe_Sub(ct,4,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(nd-j),VeCh);
      ElVe_Sub(ct,5,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(nd-j)-1,VeCh);
      ElVe_Sub(ct,6,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(nd+1-j),VeCh);
    }
    for(i=2;i<=nd-1;i++){
      ct++;
      Pnum[ct]=6;
      Ve_Sub(ct,xu,yu,zu,x[n][i][1],y[n][i][1],z[n][i][1]);
      ElVe_Sub(ct,1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+1,VeCh);
      ElVe_Sub(ct,2,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2,VeCh);
      ElVe_Sub(ct,3,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+1,VeCh);
      ElVe_Sub(ct,4,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(i-1),VeCh);
      ElVe_Sub(ct,5,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(i-1)-1,VeCh);
      ElVe_Sub(ct,6,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*i,VeCh);
    }
  }

  for(n=6;n<=10;n++){
    for(j=2;j<=nd-1;j++){
      ct++;
      Pnum[ct]=6;
      Ve_Sub(ct,xu,yu,zu,x[n][1][j],y[n][1][j],z[n][1][j]);
      ElVe_Sub(ct,1,2*Ndiv*Ndiv*(n-1)+2*(j-1),VeCh);
      ElVe_Sub(ct,2,2*Ndiv*Ndiv*(n-1)+2*(j-1)+1,VeCh);
      ElVe_Sub(ct,3,2*Ndiv*Ndiv*(n-1)+2*(j-1)+2,VeCh);
      ElVe_Sub(ct,4,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(Ndiv-1)+2*(j-1)+1,VeCh);
      ElVe_Sub(ct,5,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(Ndiv-1)+2*(j-1),VeCh);
      ElVe_Sub(ct,6,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(Ndiv-1)+2*(j-1)-1,VeCh);
    }
    for(i=2;i<=nd-1;i++){
      ct++;
      Pnum[ct]=6;
      Ve_Sub(ct,xu,yu,zu,x[n][i][1],y[n][i][1],z[n][i][1]);
      ElVe_Sub(ct,1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+1,VeCh);
      ElVe_Sub(ct,2,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2,VeCh);
      ElVe_Sub(ct,3,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+1,VeCh);
      ElVe_Sub(ct,4,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(Ndiv-1)+2*(nd-i)+1,VeCh);
      ElVe_Sub(ct,5,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(Ndiv-1)+2*(nd-i),VeCh);
      ElVe_Sub(ct,6,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(Ndiv-1)+2*(nd-i)-1,VeCh);
    }
  }

  //Interior_Pt
  for(n=1;n<=10;n++){
    for(i=2;i<=nd-1;i++){
      for(j=2;j<=nd-1;j++){
	ct++;
	Pnum[ct]=6;
	Ve_Sub(ct,xu,yu,zu,x[n][i][j],y[n][i][j],z[n][i][j]);
	ElVe_Sub(ct,1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*(j-1),VeCh);
	ElVe_Sub(ct,2,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*(j-1)+1,VeCh);
	ElVe_Sub(ct,3,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*(j-1)+2,VeCh);
	ElVe_Sub(ct,4,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+2*(j-1)+1,VeCh);
	ElVe_Sub(ct,5,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+2*(j-1),VeCh);
	ElVe_Sub(ct,6,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+2*(j-1)-1,VeCh);
      }
    }
  }

  ////////////////
  //Element
  ////////////////

  //Singular_El
  for(n=1;n<=5;n++){
    ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv,2*Ndiv*Ndiv*(n-1)+2*Ndiv-1,
	     2*Ndiv*Ndiv*(bT[n]-1)+2*Ndiv,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv);
    ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2,
	     2*Ndiv*Ndiv*bB[n],2*Ndiv*Ndiv*(bR[n]-1)+2);
  }
  for(n=6;n<=10;n++){
    ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv,2*Ndiv*Ndiv*(n-1)+2*Ndiv-1,
	     2*Ndiv*Ndiv*(bT[n]-1)+1,2*Ndiv*Ndiv*bL[n]-1);
    ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2,
	     2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(Ndiv-1)+1,2*Ndiv*Ndiv*(bR[n]-1)+2*Ndiv*(Ndiv-1)+1);
  }

  //Boundary_El
  for(n=1;n<=5;n++){
    for(j=1;j<=nd-2;j++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*j,2*Ndiv*Ndiv*(n-1)+2*j-1,
	       2*Ndiv*Ndiv*(n-1)+2*j+1,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(nd-j));
    }
    for(j=2;j<=nd-1;j++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1)+1,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1)+2,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1),
	       2*Ndiv*Ndiv*(bR[n]-1)+2*(j-1)+2);
    }
    for(i=1;i<=nd-2;i++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*i+2,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2,2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*i);
    }
    for(i=2;i<=nd-1;i++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*i,2*Ndiv*Ndiv*(n-1)+2*Ndiv*i-1,
	       2*Ndiv*Ndiv*(bT[n]-1)+2*(nd-i),2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)-1);
    }
  }

  for(n=6;n<=10;n++){
    for(j=1;j<=nd-2;j++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*j,2*Ndiv*Ndiv*(n-1)+2*j-1,
	       2*Ndiv*Ndiv*(n-1)+2*j+1,2*Ndiv*Ndiv*(bL[n]-1)+2*Ndiv*(Ndiv-1)+2*j-1);
    }
    for(j=2;j<=nd-1;j++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1)+1,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1)+2,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(Ndiv-1)+2*(j-1),
	       2*Ndiv*Ndiv*(bR[n]-1)+2*Ndiv*(nd-j-1)+1);
    }
    for(i=1;i<=nd-2;i++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*i+2,
	       2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2,
	       2*Ndiv*Ndiv*(bB[n]-1)+2*Ndiv*(Ndiv-1)+2*(nd-i)-1);
    }
    for(i=2;i<=nd-1;i++){
      ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*i,2*Ndiv*Ndiv*(n-1)+2*Ndiv*i-1,
	       2*Ndiv*Ndiv*(bT[n]-1)+2*Ndiv*(i-1)+1,2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)-1);
    }
  }

  //Interior_El
  for(n=1;n<=10;n++){
    for(i=1;i<=nd-2;i++){
      for(j=2;j<=nd-1;j++){
	ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*(j-1)+1,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*i+2*j,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*j,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*(j-1));
      }
    }
    for(i=2;i<=nd-1;i++){
      for(j=1;j<=nd-2;j++){
	ElEl_Sub(2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*j,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*j-1,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-1)+2*j+1,
		 2*Ndiv*Ndiv*(n-1)+2*Ndiv*(i-2)+2*j-1);
      }
    }
  }

  ////////////////////
  //Element_Arrange
  ////////////////////

  //Vertex
  double nlp[4],nl[4];
  for(n=1;n<=noe;n++){
    nlp[1]=(xu[Ve[1][n]]+xu[Ve[2][n]]+xu[Ve[3][n]])/3.0;
    nlp[2]=(yu[Ve[1][n]]+yu[Ve[2][n]]+yu[Ve[3][n]])/3.0;
    nlp[3]=(zu[Ve[1][n]]+zu[Ve[2][n]]+zu[Ve[3][n]])/3.0;

    nl[1]=(yu[Ve[2][n]]-yu[Ve[1][n]])*(zu[Ve[3][n]]-zu[Ve[1][n]])
      -(zu[Ve[2][n]]-zu[Ve[1][n]])*(yu[Ve[3][n]]-yu[Ve[1][n]]);
    nl[2]=(zu[Ve[2][n]]-zu[Ve[1][n]])*(xu[Ve[3][n]]-xu[Ve[1][n]])
      -(xu[Ve[2][n]]-xu[Ve[1][n]])*(zu[Ve[3][n]]-zu[Ve[1][n]]);
    nl[3]=(xu[Ve[2][n]]-xu[Ve[1][n]])*(yu[Ve[3][n]]-yu[Ve[1][n]])
      -(yu[Ve[2][n]]-yu[Ve[1][n]])*(xu[Ve[3][n]]-xu[Ve[1][n]]);

    if(nlp[1]*nl[1]+nlp[2]*nl[2]+nlp[3]*nl[3]<0.0){
      k=Ve[2][n];
      Ve[2][n]=Ve[3][n];
      Ve[3][n]=k;
    }

    /*
    volume=(yu[Ve[2][n]]*zu[Ve[3][n]]-zu[Ve[2][n]]*yu[Ve[3][n]])*xu[Ve[1][n]]
      +(zu[Ve[2][n]]*xu[Ve[3][n]]-xu[Ve[2][n]]*zu[Ve[3][n]])*yu[Ve[1][n]]
      +(xu[Ve[2][n]]*yu[Ve[3][n]]-yu[Ve[2][n]]*xu[Ve[3][n]])*zu[Ve[1][n]];
    if(volume<0.0){
      k=Ve[2][n];
      Ve[2][n]=Ve[3][n];
      Ve[3][n]=k;
    }
    */
  }

  //Element
  int ii[3];
  for(n=1;n<=noe;n++){
    k=0;
    for(i=1;i<=3;i++){
      for(j=1;j<=3;j++){
	if(Ve[i][n]==Ve[j][El[1][n]]){
	  k++;
	  ii[k]=i;
	}
      }
    }
    if(ii[1]==2&&ii[2]==3){
      i=Ve[1][n];
      j=Ve[2][n];
      k=Ve[3][n];
      Ve[1][n]=j;
      Ve[2][n]=k;
      Ve[3][n]=i;
    }
    else if(ii[1]==1&&ii[2]==3){
      i=Ve[1][n];
      j=Ve[2][n];
      k=Ve[3][n];
      Ve[1][n]=k;
      Ve[2][n]=i;
      Ve[3][n]=j;
    }
  }

  ////////////////////
  //Surface
  ////////////////////

  //Init
  for(n=1;n<=noe;n++){
    ElCh[n]=0;
    Ve[4][n]=Ve[1][n];
  }

  //Surface
  ct=0;
  for(n=1;n<=noe;n++){
    for(i=1;i<=3;i++){
      if(ElCh[El[i][n]]==0){
	ct++;
	ElCh[n]=1;
	Lb[ct]=Ve[i][n];
	Lf[ct]=Ve[i+1][n];
	Nb[ct]=n;
	Nf[ct]=El[i][n];
	Su[i][n]=ct;
      }
      else{
	for(j=1;j<=3;j++){
	  if(El[j][El[i][n]]==n)
	    Su[i][n]=Su[j][El[i][n]];
	}
      }
    }
  }
}

//Boundary_Sub
void Bd_Sub(int n,int p1,int p2,int p3,int p4,int q1[],int q2[],int q3[],int q4[])
{
  q1[n]=p1;
  q2[n]=p2;
  q3[n]=p3;
  q4[n]=p4;
}

//Vertex_Sub
void Ve_Sub(int n,double q1[],double q2[],double q3[],double qp1,double qp2,double qp3)
{
  q1[n]=qp1;
  q2[n]=qp2;
  q3[n]=qp3;
}

//Element-Vertex_Sub
void ElVe_Sub(int n,int k,int el,int VeCh[])
{
  VeCh[el]++;
  Pne[k][n]=el;
  Ve[VeCh[el]][el]=n;
}

//Element-Element_Sub
void ElEl_Sub(int el,int p1,int p2,int p3)
{
  El[1][el]=p1;
  El[2][el]=p2;
  El[3][el]=p3;
}

//////////////////
//Biconcave
//////////////////
void Biconcave()
{
  double rad,c1,c2,c3;
  double rr,sgn;

  rad=1.0;
  c1=0.207;
  c2=2.003;
  c3=-1.123;

  for(int n=1;n<=non;n++){
    rr=xu[n]*xu[n]+yu[n]*yu[n];
    xu[n]=rad*xu[n];
    yu[n]=rad*yu[n];
    zu[n]=rad*zu[n];
//    if (zu[n]<0.0) zu[n]=0.0;
  }

  for(int n=1;n<=non;n++){
    //rotate(0.25*M_PI,0.0,0.0,xu[n],yu[n],zu[n]);
    //rotate(0.0,-0.25*M_PI,0.0,xu[n],yu[n],zu[n]);
    rotate(0.0,0.5*M_PI,0.0,xu[n],yu[n],zu[n]);
  }
}

void rotate(double thx,double thy,double thz,double &xp,double &yp,double &zp)
{
  double rp[5],rpn[5];
  double Ax[5][5],Ay[5][5],Az[5][5];

  rpn[1]=xp;
  rpn[2]=yp;
  rpn[3]=zp;
  rpn[4]=1.0;

  for(int i=1;i<=4;i++){
    for(int j=1;j<=4;j++){
      Ax[i][j]=0.0;
      Ay[i][j]=0.0;
      Az[i][j]=0.0;
    }
  }
  for(int i=1;i<=4;i++){
    Ax[i][i]=1.0;
    Ay[i][i]=1.0;
    Az[i][i]=1.0;
  }

  Ax[2][2]=cos(thx);
  Ax[2][3]=-sin(thx);
  Ax[3][2]=sin(thx);
  Ax[3][3]=cos(thx);
  Ay[1][1]=cos(thy);
  Ay[1][3]=sin(thy);
  Ay[3][1]=-sin(thy);
  Ay[3][3]=cos(thy);
  Az[1][1]=cos(thz);
  Az[1][2]=-sin(thz);
  Az[2][1]=sin(thz);
  Az[2][2]=cos(thz);

  //x
  for(int i=1;i<=4;i++){
    rp[i]=rpn[i];
  }
  for(int i=1;i<=4;i++){
    rpn[i]=Ax[i][1]*rp[1]+Ax[i][2]*rp[2]+Ax[i][3]*rp[3]+Ax[i][4]*rp[4];
  }

  //y
  for(int i=1;i<=4;i++){
    rp[i]=rpn[i];
  }
  for(int i=1;i<=4;i++){
    rpn[i]=Ay[i][1]*rp[1]+Ay[i][2]*rp[2]+Ay[i][3]*rp[3]+Ay[i][4]*rp[4];
  }

  //z
  for(int i=1;i<=4;i++){
    rp[i]=rpn[i];
  }
  for(int i=1;i<=4;i++){
    rpn[i]=Az[i][1]*rp[1]+Az[i][2]*rp[2]+Az[i][3]*rp[3]+Az[i][4]*rp[4];
  }

  xp=rpn[1];
  yp=rpn[2];
  zp=rpn[3];
}
