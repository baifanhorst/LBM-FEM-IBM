#include <iostream>
using namespace std;
#include "particle.h"

void crossproduct(double *p, double *a, double *b);
void normalize(double *e, double *a);
double innerproduct(double *a, double *b);
int main()
{
	/*
	particle par;
	par.mesh_read();
	par.mesh_write();
	double xave=1,yave=1,zave=1,R=1;
	par.pos_init(xave,yave,zave,R);
	par.avepos_cal();
	par.e_pointpos_set();
	par.parameter_init(); 
	par.F_allocate();
	
	par.F_Fb_setnum();
	par.ks=1; par.k_alpha=1; par.kb=1; par.ka=1; par.kv=1;

	par.p[1].pos[0]=par.p[1].pos[0]+0.2;
	
	
	
	//cout<<par.F[1][2]<<endl;
	par.F_cal();	
	//cout<<par.F[1][2]<<endl;
	cout<<par.V0<<' '<<par.V<<endl;
	*/
	
	particle par;
	par.p_num=4; par.l_num=6; par.e_num=4;
	par.mesh_allocate();
	par.p[1].pos[0]=0; par.p[1].pos[1]=0; par.p[1].pos[2]=0;
	par.p[2].pos[0]=1; par.p[2].pos[1]=0; par.p[2].pos[2]=0; 
	par.p[3].pos[0]=0; par.p[3].pos[1]=1; par.p[3].pos[2]=0; 
	par.p[4].pos[0]=0; par.p[4].pos[1]=0; par.p[4].pos[2]=1;
	
	par.l[1].p_no[0]=1; par.l[1].p_no[1]=2;
	par.l[2].p_no[0]=1; par.l[2].p_no[1]=3;
	par.l[3].p_no[0]=1; par.l[3].p_no[1]=4;
	par.l[4].p_no[0]=2; par.l[4].p_no[1]=3;
	par.l[5].p_no[0]=3; par.l[5].p_no[1]=4;
	par.l[6].p_no[0]=4; par.l[6].p_no[1]=2;
	
	par.l[1].e_no[0]=1; par.l[1].e_no[1]=3;
	par.l[2].e_no[0]=1; par.l[2].e_no[1]=2;
	par.l[3].e_no[0]=2; par.l[3].e_no[1]=3;
	par.l[4].e_no[0]=1; par.l[4].e_no[1]=4;
	par.l[5].e_no[0]=2; par.l[5].e_no[1]=4;
	par.l[6].e_no[0]=3; par.l[6].e_no[1]=4;
	
	par.e[1].p_no[0]=1; par.e[1].p_no[1]=3; par.e[1].p_no[2]=2;
	par.e[2].p_no[0]=1; par.e[2].p_no[1]=4; par.e[2].p_no[2]=3;
	par.e[3].p_no[0]=1; par.e[3].p_no[1]=2; par.e[3].p_no[2]=4;
	par.e[4].p_no[0]=2; par.e[4].p_no[1]=3; par.e[4].p_no[2]=4;
	
	par.e_pointpos_set();
	par.parameter_init(); 
	par.F_allocate();
	
	par.F_Fb_setnum();
	par.ks=1; par.k_alpha=1; par.kb=1; par.ka=1; par.kv=1;
	
	par.p[3].pos[0]=0.1;
	//par.p[1].pos[0]=-0.1; par.p[1].pos[1]=-0.1; par.p[1].pos[2]=-0.1;
	par.F_cal();
	//cout<<par.F[1][0]<<' '<<par.F[1][1]<<' '<<par.F[1][2]<<endl;
	cout<<par.F[3][0]<<' '<<par.F[3][1]<<' '<<par.F[3][2]<<endl;
	
	
	/*
	cout<<par.e[1].vector_outernormal[0]<<' '<<par.e[1].vector_outernormal[1]<<' '<<par.e[1].vector_outernormal[2]<<endl;
	cout<<par.e[2].vector_outernormal[0]<<' '<<par.e[2].vector_outernormal[1]<<' '<<par.e[2].vector_outernormal[2]<<endl;
	cout<<par.e[3].vector_outernormal[0]<<' '<<par.e[3].vector_outernormal[1]<<' '<<par.e[3].vector_outernormal[2]<<endl;
	cout<<par.e[4].vector_outernormal[0]<<' '<<par.e[4].vector_outernormal[1]<<' '<<par.e[4].vector_outernormal[2]<<endl;
	*/
	/*
	cout<<par.l[1].p_n1<<' '<<par.l[1].p_n2<<' '<<par.l[1].p_n3<<' '<<par.l[1].p_n4<<endl;
	cout<<par.l[2].p_n1<<' '<<par.l[2].p_n2<<' '<<par.l[2].p_n3<<' '<<par.l[2].p_n4<<endl;
	cout<<par.l[3].p_n1<<' '<<par.l[3].p_n2<<' '<<par.l[3].p_n3<<' '<<par.l[3].p_n4<<endl;
	cout<<par.l[4].p_n1<<' '<<par.l[4].p_n2<<' '<<par.l[4].p_n3<<' '<<par.l[4].p_n4<<endl;
	cout<<par.l[5].p_n1<<' '<<par.l[5].p_n2<<' '<<par.l[5].p_n3<<' '<<par.l[5].p_n4<<endl;
	cout<<par.l[6].p_n1<<' '<<par.l[6].p_n2<<' '<<par.l[6].p_n3<<' '<<par.l[6].p_n4<<endl;
	*/
	/*
	cout<<par.l[1].e_ni<<' '<<par.l[1].e_nj<<endl;
	cout<<par.l[2].e_ni<<' '<<par.l[2].e_nj<<endl;
	cout<<par.l[3].e_ni<<' '<<par.l[3].e_nj<<endl;
	cout<<par.l[4].e_ni<<' '<<par.l[4].e_nj<<endl;
	cout<<par.l[5].e_ni<<' '<<par.l[5].e_nj<<endl;
	cout<<par.l[6].e_ni<<' '<<par.l[6].e_nj<<endl;
	*/
	/*
	int ne;
	for (ne=1;ne<=par.e_num;ne++)
	{
		//cout<<par.e[ne].l0<<' '<<par.e[ne].l0_<<' '<<par.e[ne].fi0<<endl;
		//cout<<par.e[ne].A<<' '<<par.e[ne].A0<<endl;
		//cout<<par.e[ne].V<<endl;
		//cout<<par.V<<endl;
	}
	*/
	

	return 0;
}
