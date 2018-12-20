#ifndef _AP_RPT_STEEL_H_
#define _AP_RPT_STEEL_H_


struct Rpt_Steel
{
	int obj;					// 1:member, 2:plate, 3:bolt, 4:joint
	int id;						// ����
	int parent;				// ����������(-1��������)
	int count;		//����
	int color;		//��ɫ
	int selected;	//ѡ��
	int node;

	int type;				// 1:����
	int kind;				// 1:������
	char group[32];	// ����
	char name[32];
	char no[32];
	char part_no[16];
	char mat[10];
	char section[30];	//���	1:����, 2:���, 3:ֱ��, 4:��Ч
	double length;		//member:length, pl:�ϳ��ı�(mm)
	double area;			//Ϳװ(mm2)
	double weight;		//(kg)
};

///BETTER-Rpt_Steel
#define RSteel struct Rpt_Steel




#endif//FILE
