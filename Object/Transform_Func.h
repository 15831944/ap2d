// Transform_Func.h: interface for the Transform_Func class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_
#define AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_

#include "export.h"
#include <vector>
#include "../afc/counter.h"

namespace dlhml{

class Point;
typedef std::vector<Point> CPt3DVector;

class Normal;
class Matrix;
class OBJECT_API Transform_Func  
{
public:
	Transform_Func();
	~Transform_Func();

	//��ֻ�Ϊ�߶�
	void divide_arc(const Point& center, const Point &start,
		const Point &end,const Normal& normal,int flatnum,CPt3DVector& dest);
	//�õ����ϵ���һ����
	void next_arc_pt(const Point &center, const Point &pos, 
						Point &next, const Normal& normal,Float angle);

	Float sin(Float x);
	Float cos(Float x);

	//�õ�ƽ�淨������
	Normal get_plane_normal(const Point& pt1,const Point& pt2, const Point& pt3);

	//�����Ƿ���һֱ����
	bool pt_in_line(const Point& pt1,const Point& pt2, const Point& pt3);

	//Բ���ļн�
	Float arc_angle(const Point& center, const Point &start,
		const Point &end,const Normal& normal);


	//��Բ��Ϊ��㣬�յ���y���������ϵ���������x-alpha,y-beta��ת��normal
	void rotation_normal_angle(const Normal& normal, Float& alpha, Float& beta);
	//ȷ���������ı任�������
	void normal_matrix(const Normal& normal, Matrix& mat);
	//�����������ı任����
	void noraml_to_normal_matrix(const Normal& src, const Normal& dest, Matrix& mat);

	//����ϵת������
	void coord_transform_mat(Matrix& mat,const Point& destO,
		const Normal& destOX,const Normal& destOY,const Normal& destOZ);

	
private:
	MCT_DEF
};
}
#endif // !defined(AFX_TRANSFORM_FUNC_H__E01FF186_0B33_4D6D_8DCE_19919DC5B359__INCLUDED_)
