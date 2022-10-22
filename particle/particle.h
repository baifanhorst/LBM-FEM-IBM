#include <iostream>
using namespace std;

#include "point.h"
#include "line.h"
#include "element.h"

class particle
{
	public:
		int p_num, l_num, e_num; //节点个数 边个数 单元个数
		int p_e_num_maxconnect; //每个节点所能连接的最大单元数
		point *p; //节点 p[p_num+1]
		line *l; //边 l[l_num+1]
		element *e; //单元 e[e_num+1]
		
		double pos_ave[3]; //平均位置
		double R; //初始半径
		
		double ks,k_alpha; //剪切模量
		double kb; //弯曲模量
		double ka; //面积模量
		double kv; //体积模量
		
		double **F; //节点力 F[p_num+1][3]
		
		double A, V, A0, V0; //总面积总体积, 初始总面积总体积
				
		double zmin,zmax; //z方向最小，最大坐标，用于处理wall repulse
		double pos_min[3], pos_max[3]; //三个方向的最大最小值，用于更新粘性时生成射线，和上面的zmin，zmax有点重复
		double I[3][3]; //转动惯量
		double D; //变形描述
		double inclination_angle; //倾角
		
		double d_average_node; //平均节点间距
		
		double pos_center[3]; //型心
		double contact_area; //接触面积
		
		
		//int count_pos_adjust_x; //位置调整的次数可正可负，用于计算真实位置
		
		
		void mesh_read(); //读入网格数据，并分配空间
		void mesh_allocate(); //测试程序，给定节点、边、单元编号分配空间
		void mesh_write(); //测试函数，输出读入的数据
		void pos_init(double x_ave, double y_ave, double z_ave, double R); //计算初始位置，初始边长，初始单元面积
		void avepos_cal();
		void p_vel_old_set(); //存储上一步速度
		void e_pointpos_set(); //设置单元三个节点的坐标
		void e_parameter_Fs_init(); //设置计算Fs2D时所需的l0,l0_,fi0
		void F_allocate(); //为F分配空间
		void F_deallocate(); //释放F空间
		void F_setzero(); //将F置零
		
		void F_Fs2D_cal(double **Fs_2D, double l0, double l0_, double l, double l_, double fi0, double fi, double A0); //将单元放置在平面中计算三个节点的剪切力
		void F_Fs3D_convert(double **Fs2D, int ne); //将Fs2D转换成Fs3D 需要输入Fs2D的结果F，以及单元编号		
		void F_Fs_cal(); //计算Fs
		
		void F_cal();
		
		void e_outernormalvector(); //计算外法线向量
		
		void F_Fb_setnum(); //设置计算弯曲力时1,2,3,4节点分别对应哪些节点
		void F_Fb_cal(); //计算弯曲力
		void l_theta_cal(); //计算边对应的两个单元的夹角
		void l_theta0_cal(); //计算边对应的两个单元的初始夹角
		
		void parameter_cal(); //计算单元中的l,l_,fi,A,vector_outernormal 边中的theta
		void parameter_init(); //计算l0,l0_,fi0,A0,theta0;
	
		void F_Fa_cal(); //计算面积力
		void F_Fv_cal(); //计算体积力
		
		void output_vtk(); //输出用于paraview显示的vtk文件
		void output_vtk_multiple(int i_cell); //用于多个cell时的输出，i_cell为第几个cell（从0开始）
		void output(); //输出，用于续算
	
		void zmin_cal(); //获得最低节点位置 用于处理wall repulse
		void zmax_cal(); //获得最高节点位置 用于处理wall repulse
		
		void translate_posx(double x); //将整体沿x方向移动x距离

		void inertia_cal(); //求转动惯量，用于验证程序正确性
		void inertia_output(); //输出转动惯量
		void inertia_D_inclination(); //计算变形D，inclination倾角
	
		void pos_rangebox_cal(); //获得particle所在box的范围，用于更新内外粘性时生成射线
	
		void mesh_PMN_convert(); //将所有点的坐标以x轴为基准向顺时针旋转90度
		void F_PMN_cal(int np, double k_PMN, double *pos_penalty); //计算固定PMN所需的penalty force

		void mesh_average_node_distance_cal(); //计算节点平均间距
		
		void pos_center_cal(); //计算型心
	
		
};
