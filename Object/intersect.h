#ifndef _INTERSECT_H_ 
#define _INTERSECT_H_ 

#include "export.h"
#include <vector>

namespace dlhml{

class Point;
class Line;
class RArc;
class Circle;
class Rect;

////����
OBJECT_API bool is_disjoint(const Rect& rc1, const Rect& rc2);


////����ֵ��ʾ����������û�н��㷵��0.
////����д��pt����.

////ֱ����ֱ�ߡ����ߡ��߶��ཻ
int intersect2d_l_l(const Line& lline1, const Line& lline2, Point& pt);
int intersect2d_l_r(const Line& lline, const Line& rline, Point& pt);
int intersect2d_l_s(const Line& lline, const Line& sline, Point& pt);
////���������ߡ��߶��ཻ
int intersect2d_r_r(const Line& rline1, const Line& rline2, Point& pt);
int intersect2d_r_s(const Line& rline, const Line& sline, Point& pt);
////�߶����߶��ཻ
int intersect2d_s_s(const Line& sline1, const Line& sline2, Point& pt);
////Բ��ֱ�ߡ����ߡ��߶Ρ�Բ�ཻ
int intersect2d_c_l(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2);
int intersect2d_c_r(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2);
int intersect2d_c_s(const Circle& lhs, const Line & rhs, Point& pt1, Point& pt2);
int intersect2d_c_c(const Circle& lhs, const Circle& rhs, Point& pt1, Point& pt2);
////����ֱ�ߡ����ߡ��߶Ρ�Բ�����ཻ
int intersect2d_a_l(const RArc& lhs, const Line & lline, Point& pt1, Point& pt2);
int intersect2d_a_r(const RArc& lhs, const Line & rline, Point& pt1, Point& pt2);
int intersect2d_a_s(const RArc& lhs, const Line & sline, Point& pt1, Point& pt2);
int intersect2d_a_c(const RArc& lhs, const Circle& rhs, Point& pt1, Point& pt2);
int intersect2d_a_a(const RArc& lhs, const RArc & rhs, Point& pt1, Point& pt2);
////�������߶Ρ�Բ�����ཻ
void intersect2d_rt_s(const Rect & rect, const Line & sline, std::vector<Point>& pts);
void intersect2d_rt_c(const Rect & rect, const Circle & c, std::vector<Point> & pts);
void intersect2d_rt_a(const Rect & rect, const RArc & arc, std::vector<Point> & pts);

//  �ѽ������pts��xpt_countΪ��������
void push_xpt(int xpt_count, const Point& pt1, const Point& pt2, std::vector<Point>& pts);


}

#endif 
 
