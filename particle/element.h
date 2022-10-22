#ifndef element_h

#define element_h





#include <iostream>
using namespace std;

class element
{
	public:
		double pos[3][3]; //三个节点坐标
		int p_no[3]; //3个节点编号
		int e_no[3]; //三个相邻单元编号
		double A,A0; //单元面积,初始面积
		double l0, l0_, l, l_, fi0, fi; //计算Fs所需参数
		double vector_outernormal[3]; //外法线方向
		double V; //单元对应的代数体积
		double pos_center[3]; //计算转动惯量时为相对于平均位置的单元中心坐标
		double pos_center_abs[3]; //绝对中心位置
		double pos_max[3];
		double pos_min[3]; //单元最大最小坐标

		int mark_contact; //计算接触面积时的标志
		
		void parameter_Fs_cal(); //计算l l_ fi
		void parameter_Fs_init_cal(); //计算l0 l0_ fi0 这个函数利用了parameter_Fs_cal()，从而必须在开始时间步迭代前进行
		void area_cal(); //计算面积
		void area_init_cal(); //计算初始面积，使用了area_cal();
		void vector_outernormal_cal(); //计算外法线方向
		void V_cal(); //计算体积（代数值）
		void pos_center_abs_cal(); //计算绝对中心坐标
		void pos_range_cal(); //计算最大最小坐标
};


#endif
