#include <iostream>
using namespace std;

class flow
{
	public:
		//数据		
		int NX,NY,NZ; //节点个数
		int Q; //D3Q19中的Q
		double *w; //平衡态分布中的权系数
		int **e; //微观速度			这个是int类型，一定要注意！！！！！！  由于要用来计算streaming时的节点位置，所以为int
		double ****f; //分布函数
		double ****fc; //碰撞后分布函数
		double ****feq; //平衡态分布
		double ****vel; //宏观速度
		double ****vel_old; //上一时间步宏观速度
		double ***den; //宏观密度
		double ***vis; //宏观粘性
		double ****bodyforce; //宏观体力，包含了原本的水平驱动力以及物体产生的力
		
		double ****pos; //节点所在位置

		int ***mark; //辅助标志场，用于更新内外粘性和密度
		
		double LX,LY,LZ; //流场长宽
		double Re; //Reynolds数
		double gx,gy,gz; //水平驱动力,用于Poiseuille流

		double den0, vis0, umax; //粘性 密度 最大(入口)速度，最大入口速度仅在泊肃叶流动中有意义
		double Uw_top; //上下壁面速度，用于库埃特流动
		double Uw_bottom;


		//函数
		//给数组分配空间,参数初始化留在子类中
		flow(int nx=100, int ny=50, int nz=50); 
		~flow(); //释放空间
		
		void init(double gx, double gy, double gz, double uw_top, double uw_bottom, double den0_, double vis0_);
		//void init(double gx=0.00002, double gy=0.0, double gz=0.0, double re=3);
		//init1与init2是将tao固定为1后Poiseuille和Couette流动的初始化		
		void init1(double Re);
		void init2(double Re);
	
		void output();
		void output_2Dvector(int j);
		void eq();
		void collision();
		void streaming();
		void macro();
		void set_bodyforce();

		int q_contrast(int q); //求反向格子速度对应的标号
		
		double innerproduct(double *a, double *b); //辅助函数，用于求内积
		double innerproduct(int *a, double *b); //重载一下，以为有eu

		void input(); //读入数据，便于继续计算
		
		void pos_cal(); //计算节点位置
		
		void output_vis2D_y(int ny);
		
};
