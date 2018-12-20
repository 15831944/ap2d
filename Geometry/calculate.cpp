#include "StdAfx.h"
#include "calculate.h" 
#include "Point.h"
#include "Normal.h"
#include "global.h"
#include "Plane.h"

#include "LLine.h"
#include "SLine.h"
#include "RLine.h"
#include "Circle.h"
#include "Arc.h"
#include "GETRACE.h"
#define LIMIT		0.05

namespace geo{
const Plane xoy(0,0,1,0);		////xoyƽ��
const Point O(0,0,0);		////ԭ������
const Point ox(1,0,0);		////x��ĵ�λ����
const Point oy(0,1,0);		////y��ĵ�λ����
const Point oz(0,0,1);		////z��ĵ�λ����

Point project(const Point &pt)
//�ռ����xoyƽ���ϵ�ͶӰ
{
	Point ph(pt.x,pt.y,0);
	return ph;
}

Point operator * (const Point &vec1,const Point &vec2)
//����������άʸ����ʸ����
{
	Point vec_mul;
	vec_mul.x = (vec1.y) * (vec2.z) - (vec2.y) * (vec1.z);
	vec_mul.y = (vec2.x) * (vec1.z) - (vec1.x) * (vec2.z);
	vec_mul.z = (vec1.x) * (vec2.y) - (vec2.x) * (vec1.y);
	return vec_mul;
}

//������άʸ������ά�������Ӧ�������֮��
Float multiply(const Point &vec1,const Point &vec2)
{
	Float num = (vec1.x) * (vec2.x) + (vec1.y) * (vec2.y) + (vec1.z) * (vec2.z);
	return num;
}

////���������߶���ȫ��ȣ�����ȫ�غϣ�
////��������Ϊͬһ�㣬�յ����յ�Ϊͬһ��
////����������յ�Ϊͬһ�㣬�յ������Ϊͬһ�㣩
bool operator == (const LLine &ln1,const LLine &ln2)
{
	bool flag1 = (ln1.pt1 == ln2.pt1) && (ln1.pt2 == ln2.pt2);
	bool flag2 = (ln1.pt1 == ln2.pt2) && (ln1.pt2 == ln2.pt1);
	return flag1 || flag2;
}

////�������ҳ������������������������
Point operator * (const Point &vec_o,Float d)  //����������ά����
{
	Point vec_n;
	vec_n.x = (vec_o.x) * (d);
	vec_n.y = (vec_o.y) * (d);
	vec_n.z = (vec_o.z) * (d);
	return vec_n;
}

////��������������������������������
Point operator * (Float d,const Point &vec_o)  //����������ά����
{
	Point vec_n;
	vec_n.x = (vec_o.x) * (d);
	vec_n.y = (vec_o.y) * (d);
	vec_n.z = (vec_o.z) * (d);
	return vec_n;
}

//��ά������ģ������ԭ�㵽��������ĳ���
Float mos(const Point &vec)
{
	if(vec == O)
		return 0;
	return sqrt(multiply(vec,vec));
}

Point get_nor(const Plane &pla)  //ȡ��ƽ��ķ�����
{
	Point nor;
	nor.x = pla.a;
	nor.y = pla.b;
	nor.z = pla.c;
	return nor;
}

Point normalize(const Point &vec)  //��ά������λ��
{
	if(vec == O)
		return vec;
	Float m = mos(vec);
	return vec * (1/m);
}

Float angle(const Point &vec1,const Point &vec2)  //���������ļн�
{
	Float angle = acos( multiply(vec1,vec2) / (mos(vec1) * mos(vec2)) );
	return angle;
}

//����һ��������������һ��ƽ�棬d��ƽ��ĵ��ĸ�����
Plane make_plane(const Point &nor,Float d)
{
	Plane pla;
	pla.a = nor.x;
	pla.b = nor.y;
	pla.c = nor.z;
	pla.d = d;
	return pla;
}

Plane make_plane(const Point &p1,const Point &p2,const Point &p3)
//����������ȷ��������ƽ��
{
	Point po1 = p2 - p1;
	Point po2 = p3 - p2;
	Point nor = po1 * po2;
	Float d = -multiply(nor,p2);
	return make_plane(nor,d);
}

Plane make_plane(const Point &pt,const Point &nor)
//ͨ��ƽ��ķ�����������һ����ƽ��
{
	Plane pla(nor.x,nor.y,nor.z,-multiply(pt,nor));
	return pla;
}

Plane make_plane(const LLine &ln1,const LLine &ln2)
//����������ֱ��ȷ����ƽ��
{
	if( !relation(ln1,ln2))
		return make_plane(ln1.pt1,ln1.pt2,ln2.pt1);
	else{
		Point nor1 = ln1.pt2 - ln1.pt1;
		Point nor2 = ln2.pt2 - ln2.pt1;
		Point nor = nor1 * nor2;
		return make_plane(ln1.pt1,nor);
	}
}

SLine create_sline(const Point &pt1,const Point &pt2)
//�������߶�
{
	SLine sl;
	sl.pt1 = pt1;
	sl.pt2 = pt2;
	return sl;
}

LLine create_line(const Point &pt1,const Point &pt2)
//������ֱ��
{
	LLine ln;
	ln.pt1 = pt1;
	ln.pt2 = pt2;
	return ln;
}

LLine make_line(const Point &pt,const Point &vec)
//��ֱ֪�ߵķ�������������һ�㣬��ֱ��
{
	LLine ln;
	ln.pt1 = pt;
	ln.pt2 = pt +  normalize(vec) * 10;
	return ln;
}

Float distance(const Point &p1,const Point &p2)  //�ռ�����֮��ľ���
{
	return mos(p1 - p2);
}

Float distance2d(const Point &pt1,const Point &pt2)
//��ά�ռ�������֮��ľ���
{
	Point ph1 = project(pt1);
	Point ph2 = project(pt2);
	return mos(ph1 - ph2);
}

LLine project(const LLine &ln)
//ֱ����xoyƽ���ϵ�ͶӰ
{
	LLine lh;
	lh.pt1 = project(ln.pt1);
	lh.pt2 = project(ln.pt2);
	return lh;
}

RLine project(const RLine &rl)
//������xoyƽ���ϵ�ͶӰ
{
	RLine rh;
	rh.pt1 = project(rl.pt1);
	rh.pt2 = project(rl.pt2);
	return rh;
}

SLine project(const SLine &sl)
//�߶���xoyƽ���ϵ�ͶӰ
{
	SLine sh;
	sh.pt1 = project(sl.pt1);
	sh.pt2 = project(sl.pt2);
	return sh;
}

LLine make_line(const RLine &rl)
//������ֱ��
{
	LLine ln;
	ln.pt1 = rl.pt1;
	ln.pt2 = rl.pt2;
	return ln;
}

LLine make_line(const SLine &sl)
//�߶���ֱ��
{
	LLine ln;
	ln.pt1 = sl.pt1;
	ln.pt2 = sl.pt2;
	return ln;
}

bool relation(const Point &pt,const RLine &ray)
//�жϵ��������ϣ��������Ϸ����棬���򷵻ؼ�
{
	if(pt == ray.pt1)
		return true;
	else
		return normalize(pt - ray.pt1) == normalize(ray.pt2 - ray.pt1);
}

bool relation(const Point &pt,const SLine &sl)
//�жϵ����߶��ϣ����߶��Ϸ����棬���򷵻ؼ�
{
	if(pt == sl.pt1 || pt == sl.pt2)
		return true;
	else{
		Point vec1 = normalize(sl.pt1 - pt);
		Point vec2 = normalize(sl.pt2 - pt);
		return vec1 == (vec2 * (-1));
	}
}

bool operator > (const Point &p1,const Point &p2)
//ֱ���϶Ե��������ص�p1 > p2
{
	if (more_than(p1.x,p2.x))
		return true;
	else if (less_than(p1.x,p2.x))
		 return false;
	else if (more_than(p1.y,p2.y))
		 return true;
	else if (less_than(p1.y,p2.y))
		 return false;
	else if (more_than(p1.z,p2.z))
		return true;
	else
		return false;
}

bool operator < (const Point &p1,const Point &p2)
//ֱ���϶Ե��������ص�p1 < p2
{
	if (less_than(p1.x,p2.x))
		return true;
	else if (more_than(p1.x,p2.x))
		return false;
	else if (less_than(p1.y,p2.y))
		return true;
	else if (more_than(p1.y,p2.y))
		return false;
	else if (less_than(p1.z,p2.z))
		return true;
	else
		return false;
}

Float distance(const Point &p,const LLine &ln)  //�㵽�ռ�ֱ�ߵľ���
{
	Point direction_vector = ln.pt2 - ln.pt1;
	Point p_p1 = ln.pt1 - p;
	Point vector_mul = p_p1 * direction_vector;
	Float dis = mos(vector_mul) / mos(direction_vector); 
	return dis;
}

Float distance2d(const Point &p,const LLine &ln)
//��ά�ռ��ڵ㵽ֱ�ߵľ���
{
	Point ph = project(p);
	LLine lnh = project(ln);
	return distance(ph,lnh);
}

Float distance(const Point &p,const Plane &pla)  //�㵽ƽ��ľ���
{
	Point nor = get_nor(pla);
	Float dis = fabs(multiply(p,nor) + pla.d) / mos(nor);
	return dis;
}

Point project(const Point &p,const LLine &ln)
//������ڿռ�ֱ���ϵ�ͶӰ����
{
	Float h = distance(p,ln);
	if(equ(h,0))
		return p;
	else{
		Point vecl = ln.pt2 - ln.pt1;
		Point vechs = p - ln.pt1;
		if(equ(multiply(vecl,vechs),0))
			return ln.pt1;
		else{
			Point veche = p - ln.pt2;
			if(equ(multiply(vecl,veche),0))
				return ln.pt2;
			else{
				Float pp1 =  mos(vechs);
				Float dis = sqrt(pp1 * pp1 - h * h);
				Point vec =  normalize(vecl);
				Point p1 = ln.pt1 + vec * dis;
				Point p2 = ln.pt1 - vec * dis;
				Point vec1 = p1 - p;
				return ( equ(multiply(vecl,vec1),0)) ? p1 : p2;
			}
		}
	}
}

Point project2d(const Point &pt,const LLine &ln)
//��ά�ռ�����㵽ֱ�ߵ�ͶӰ
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	return project(pth,lnh);
}

////���溯��ר�ã���������ֱ��б��ʱ�󽻵�pt
////sign������ֱ���ڵ�ǰ�������Ƿ����
static void intersect(const LLine &ln1,const LLine &ln2,int sign,Point &pt)
{
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	if(!sign){
		if(equ(dis1,0))
			pt = ln1.pt1;
		else if(equ(dis2,0))
			pt = ln1.pt2;
		else if(equ(distance(ln2.pt1,ln1),0))
			pt = ln2.pt1;
		else
			pt = ln2.pt2;
	}
	else{
		Float num = (sign == -1) ? (dis1 - dis2) : (dis1 + dis2);
		Float d = distance(ln1.pt1,ln1.pt2);
		Float dis = dis1 * d / num;
		Point pp = normalize(ln1.pt2 - ln1.pt1) * dis;
		pt = pp + ln1.pt1;
	} 
}

//�ռ�����ֱ�ߵĽ���,�޽��㷵�ؼ٣��н�����д�����3
bool intersect(const LLine &ln1,const LLine &ln2,Point &pt)
{
	int flag = relation(ln1,ln2);
	if(flag < 1 || flag > 2)
		return 0;
	else if(flag == 2){
		int sign = dline_leave(make_sline(ln1),make_sline(ln2));
		intersect(ln1,ln2,sign,pt);
		return 1;
	}
	else if(flag == 1){
		pt = project(ln1.pt1,ln2);
		return 1;
	}
	return 0;
}

//�ж�������ά�����Ĺ�ϵ��ƽ�з���0����ֱ����1����������2
int relation(const Point &vec1,const Point &vec2)  
{
	Point vec1_normalize = normalize(vec1);
	Point vec2_normalize = normalize(vec2);
	Point reverse = vec2_normalize * (-1);
	bool vec1_vec2 = (vec1_normalize == vec2_normalize);
	bool vec1_rev = (vec1_normalize == reverse);
	if( vec1 == vec2 || vec1_vec2 || vec1_rev )
		return 0;
	else
		return (equ(multiply(vec1,vec2),0)) ? 1 : 2;
}

//�жϿռ������ϵ�����غϻ��߷��ؼ٣������������򷵻���
bool relation(const Point &p1,const Point &p2,const Point &p3)
{
	if(p1 == p2 || p2 == p3 || p1 == p3)
	  return false;
	else{
		Point vec1 = p2 - p1;
		Point vec2 = p2 - p3;
		return (relation(vec1,vec2)) ? true : false;
	}
}

//�����������ƽ���ϵ�ͶӰ����
Point project(const Point &pt,const Plane &pla)
{
	double h = distance(pt,pla);	
	if(equ(h,0))
		return pt;
	else{
		Point vec = get_nor(pla);
		Point nor = normalize(vec);
		Point pt1 = pt + nor * h;
		Point pt2 = pt - nor * h;
		double num = multiply(pt1,vec) + pla.d;
		return (equ(num,0)) ? pt1 : pt2;
	}
}

//�ж�����ƽ���λ�ù�ϵ���غϷ���-1��ƽ�з���0����ֱ����1����������2
int relation(const Plane &pla1,const Plane &pla2)
{
	Point nor1 = get_nor(pla1);
	Point nor2 = get_nor(pla2);
	Point norh = project(nor1,pla1);
	double num1 = distance(norh,pla2);
	double num2 = multiply(nor1,nor2);
	if( !relation(nor1,nor2) )
		return equ(num1,0) ? -1 : 0;
	else
		return equ(num2,0) ? 1 : 2;
}

//ֱ�ߺ�ƽ���λ�ù�ϵ��ֱ����ƽ���Ϸ���-1��ֱ��ƽ����ƽ�淵��0
//ֱ�ߴ�ֱƽ�淵��1����������2
int relation(const LLine &ln,const Plane &pla)  
{
	Point nor = get_nor(pla);
	Point vec = ln.pt2 - ln.pt1;
	Float num1 = multiply(ln.pt1,nor) + pla.d;
	Float num2 = multiply(ln.pt2,nor) + pla.d;
	bool flag = equ(num1,0);
	if(flag && equ(num2,0))
		return -1;
	else if( !flag && equ(multiply(nor,vec),0))
		return 0;
	else
		return relation(nor,vec) ? 2 : 1;
}

//��ռ�ֱ�ߺ�ƽ��Ľ��㣬û�н����򷵻ؼ٣��н�����д�����3
bool intersect(const LLine &ln,const Plane &pla,Point &pt)
{
	int flag = relation(ln,pla);
	if(flag < 1)
		return false;
	Point ph1 = project(ln.pt1,pla);
	if(flag == 1){
		pt = ph1;
		return true;
	}
	Point ph2 = project(ln.pt2,pla);
	LLine lnh(ph1,ph2);
	return intersect(ln,lnh,pt);
}

//������ƽ������һ�㣬���������ߺ�������
static Point get_separate_pt(const Plane &pla1,const Plane &pla2,const Point &nor1)
{
	Point pt = nor1,pt1,pt2;
	pt1 = nor1 * 2;
	pt2 = nor1 * 3;
	if(equ(distance(pt,pla1),0))
		return equ(distance(pt1,pla2),0) ? pt2 : pt1;
	else if(equ(distance(pt,pla2),0))
		return equ(distance(pt1,pla1),0) ? pt2 : pt1;
	else
		return pt;
}

/*
bool intersect(const Plane &pla1,const Plane &pla2,LLine &ln)
//������ƽ��Ľ��ߣ���ƽ��ƽ�л��غ�ʱ���ؼ�
{
	if(relation(pla1,pla2) < 1)
		return false;
	Point nor1 = get_nor(pla1);
	Point nor2 = get_nor(pla2);
	Point vec = nor1 * nor2;
	Point pt = get_separate_pt(pla1,pla2,nor1);
	Point ph1 = project(pt,pla1);
	Point ph2 = project(pt,pla2);
	Point nor = (pt - ph1) * (pt - ph2);
	Point vec1 = nor * nor1;
	Point vec2 = nor * nor2;
	LLine ln1 = make_line(ph1,vec1);
	LLine ln2 = make_line(ph2,vec2);
	Point cross;
	intersect(ln1,ln2,cross);
	ln = make_line(cross,vec);
	return true;
}*/

//��ռ���������ƽ��Ľ��ߣ���ƽ��ƽ�л��غ�ʱ���ؼ�
bool intersect(const Plane &pla1,const Plane &pla2,LLine &line)
{
	if(relation(pla1,pla2) < 1)
		return false;
	else{
		Point vec = get_nor(pla1) * get_nor(pla2);
		bool cs1 = equ(vec.x,0);
		bool cs2 = equ(vec.y,0);
		bool cs3 = equ(vec.z,0);
		Float a1 = pla1.a, b1 = pla1.b, c1 = pla1.c, d1 = pla1.d;
		Float a2 = pla2.a, b2 = pla2.b, c2 = pla2.c, d2 = pla2.d;
		Float x0, y0, z0;
		Point pt;
		if( (cs1 && !(cs2 || cs3)) || (!cs2 && cs1 && cs3) ){
			x0 = (c1*d2 - c2*d1) / (a1*c2 - a2*c1);
			z0 = (a2*d1 - a1*d2) / (a1*c2 - a2*c1);
			pt.set(x0,0,z0);
		}
		else if( (cs2 && !(cs1 || cs3)) || (cs3 && !(cs1 || cs2)) || (!cs1 && cs2 && cs3) ){
			y0 = (c1*d2 - c2*d1) / (b1*c2 - b2*c1);
			z0 = (b2*d1 - b1*d2) / (b1*c2 - b2*c1);
			pt.set(0,y0,z0);
		}
		else if( (!cs3 && cs1 && cs2) || !(cs1 || c2 || cs3) ){
			x0 = (b1*d2 - b2*d1) / (a1*b2 - a2*b1);
			y0 = (a2*d1 - a1*d2) / (a1*b2 - a2*b1);
			pt.set(x0,y0,0);
		}
		line = make_line(pt,vec);
		return true;
	}
}

//�жϿռ�����ֱ���Ƿ��غ�,�غϷ����棬����Ϊ��
bool superposition(const LLine &ln1,const LLine &ln2)
{
	Float d1 = distance(ln2.pt1,ln1);
	Float d2 = distance(ln2.pt2,ln1);
	return equ(d1,0) && equ(d2,0);
}

//�ж϶�ά�ռ�����ֱ���Ƿ��غ�,�غϷ����棬����Ϊ��
bool superposition2d(const LLine &ln1,const LLine &ln2)
{
	LLine lnh1 = project(ln1);
	LLine lnh2 = project(ln2);
	return superposition(lnh1,lnh2);
}

//�жϿռ�����ֱ���Ƿ�ƽ��,ƽ�з����棬����Ϊ��
bool parallel(const LLine &ln1,const LLine &ln2)
{
	Point vec1 = ln1.pt2 - ln1.pt1;
	Point vec2 = ln2.pt2 - ln2.pt1;
	int parallel = relation(vec1,vec2);
	bool superposit = superposition(ln1,ln2);
	return !superposit && !parallel;
}

//�жϿռ������߶��Ƿ�ƽ��,ƽ�з����棬����Ϊ��
bool parallel(const SLine &sl1,const SLine &sl2)
{
	Point vec1 = sl1.pt2 - sl1.pt1;
	Point vec2 = sl2.pt2 - sl2.pt1;
	int parallel = relation(vec1,vec2);
	bool superposit = superposition(make_line(sl1),make_line(sl2));
	return !superposit && !parallel;
}

//�жϿռ�����ֱ���Ƿ��ཻ,�ཻ�����棬����Ϊ��
bool intersection(const LLine &ln1,const LLine &ln2)
{
	bool superposit = superposition(ln1,ln2);
	bool para = parallel(ln1,ln2);
	if(superposit || para)
		return false;
	else{
		bool jug1 = relation(ln1.pt1,ln1.pt2,ln2.pt1);
		bool jug2 = relation(ln1.pt1,ln1.pt2,ln2.pt2);
		if(!jug1 || !jug2)
			return true;
		else{
			Plane pla1 = make_plane(ln1.pt1,ln1.pt2,ln2.pt1);
			Plane pla2 = make_plane(ln1.pt1,ln1.pt2,ln2.pt2);
			Point nor1 = get_nor(pla1);
			Point nor2 = get_nor(pla2);
			int nor = relation(nor1,nor2);
			return (nor) ? false : true;
		}
	}
}

//�ռ�����ֱ�ߵ�λ�ù�ϵ
//�غϷ���-1��ƽ�з���0���ཻʱ��ֱ����1��б������2
//���淵��3
int relation(const LLine &ln1,const LLine &ln2)
{
	Point vec1 = ln1.pt2 - ln1.pt1;
	Point vec2 = ln2.pt2 - ln2.pt1;
	Float num_vec = multiply(vec1,vec2);
	bool superposit = superposition(ln1,ln2);
	bool intersect = intersection(ln1,ln2);
	bool parall = parallel(ln1,ln2);
	if(superposit)
		return -1;
	else if(parall)
		return 0;
	else if(intersect)
		return (equ(num_vec,0)) ? 1 : 2;
	else
		return 3;
}

//ֱ��ln��һ����xoy���ϵ�ͶӰ��ph,�ָ�ph��ln�ϵĵ�
Point resume_point(const Point &ph,const LLine &ln)
{
	bool flag_x = equ(ln.pt1.x,ln.pt2.x);
	bool flag_y = equ(ln.pt1.y,ln.pt2.y);
	if(flag_x && flag_y)
		return ln.pt1;
	Point pt = ph;
	Float num = ln.pt2.z - ln.pt1.z;
	Float z1 = (ph.x - ln.pt1.x) * num / (ln.pt2.x - ln.pt1.x) + ln.pt1.z;
	Float z2 = (ph.y - ln.pt1.y) * num / (ln.pt2.y - ln.pt1.y) + ln.pt1.z;
	pt.z = (flag_x) ? z2 : z1;
	return pt;
}

//ƽ��pla��һ����xoy���ϵ�ͶӰ��ph,�ָ�ph��pla�ϵĵ�
Point resume_point(const Point &ph,const Plane &pla)
{
	if(equ(distance(ph,pla),0))
		return ph;
	Float z = (pla.a * ph.x + pla.b * ph.y + pla.d) / (-pla.c);
	Point pt(ph.x,ph.y,z);
	return pt;
}

//LhΪpla��ֱ����xoyƽ���ϵ�ͶӰ���ָ�Lh��pla�ϵ�ֱ��
LLine resume_line(const LLine &lh,const Plane &pla)
{
	LLine ln;
	ln.pt1 = resume_point(lh.pt1,pla);
	ln.pt2 = resume_point(lh.pt2,pla);
	return ln;
}

SLine make_sline(const LLine &ln)  //ֱ�����߶�
{
	SLine sl;
	sl.pt1 = ln.pt1;
	sl.pt2 = ln.pt2;
	return sl;
}

//�����߶ε��ཻ��ϵ
//�޴�͸�ཻ����0����ͬһ�෵��-1����������1
int dline_leave(const SLine &sl1,const SLine &sl2)
{
	LLine ln1 = make_line(sl1);
	LLine ln2 = make_line(sl2);
	Float dis1 = distance(sl1.pt1,ln2);
	Float dis2 = distance(sl1.pt2,ln2);
	Float dis3 = distance(sl2.pt1,ln1);
	Float dis4 = distance(sl2.pt2,ln1);
	bool flag1 = equ(dis1,0) || equ(dis2,0);
	bool flag2 = equ(dis3,0) || equ(dis4,0);
	if(flag1 || flag2)
		return 0;
	else{
		Point ph1 = project(sl1.pt1,ln2);
		Point ph2 = project(sl1.pt2,ln2);
		Point vec1 = normalize(ph1 - sl1.pt1);
		Point vec2 = normalize(ph2 - sl1.pt2);
		return (vec1 == vec2) ? -1 : 1;
	}
}

Point make_point(const Normal &nor) //Normal תPoint
{
	Point pt;
	pt.set(nor.x,nor.y,nor.z);
	return pt;
}

//�ռ乲���ֱ�ߺ�Բ�Ľ��㣬���ؽ������
//����������ʱ����д��cross1��cross2����һ������ʱ����д��cross1
int intersect(const LLine &ln,const Circle &c,Point &cross1,Point &cross2)
{
	Float d = distance(c.center,ln);
	Point ch = project(c.center,ln);
	Point vec = normalize(ln.pt2 - ln.pt1);
	if(more_than(c.radius,d)){
		Float h = sqrt(pow(c.radius,2) - d * d);
		cross1 = ch + vec * h;
		cross2 = ch - vec * h;
		return 2;
	}
	else if(equ(d,c.radius)){
		cross1 = ch;
		return 1;
	}
	else
		return 0;
}

Normal make_nor(const Point &pt) //��ת��Normal
{
	Normal nor;
	nor.set(pt.x,pt.y,pt.z);
	return nor;
}

void resume_circle(const Arc &arc,Circle &c)  //�ָ�Բ����Ӧ��Բ
{
	Plane pla = make_plane(arc.start,arc.end,arc.path);
	Point nor = get_nor(pla);
	c.nor = make_nor(nor);
	Point mid1 = (arc.start + arc.path) * 0.5;
	Point mid2 = (arc.end + arc.path) * 0.5;
	Point vec1 = (arc.path - arc.start) * nor;
	Point vec2 = (arc.path - arc.end) * nor;
	LLine ln1 = make_line(mid1,vec1);
	LLine ln2 = make_line(mid2,vec2);
	Point pt;
	intersect(ln1,ln2,pt);
	c.center = pt;
	c.radius = distance(c.center,arc.start);
}

//�жϵ���Բ���ϣ�����Բ���Ϸ��ؼ٣����򷵻���
bool relation(const Point &pt,const Arc &arc)
{
	Plane pla = make_plane(arc.start,arc.end,arc.path);
	if(!equ(distance(pt,pla),0))
		return false;
	Circle c;
	resume_circle(arc,c);
	if(relation(pt,c))
		return false;
	if(pt == arc.start || pt == arc.end)
		return true;
	SLine sl1 = create_sline(arc.start,arc.end);
	SLine sl2 = create_sline(pt,arc.path);
	Point cross;
	return !intersect(sl1,sl2,cross);
}

//��Բ���ڵ�ƽ��
Plane make_plane(const Circle &c)
{
	Point nor = make_point(c.nor);
	return make_plane(c.center,nor);
}

//���Բ��λ�ù�ϵ,�㲻��Բ���ڵ�ƽ���Ϸ���-2
//����Բ�Ϸ���0����Բ�ⷵ��1����԰�ڷ���-1
int relation(const Point &pt,const Circle &c)
{
	Plane pla = make_plane(c);
	Float dis1 = distance(pt,pla);
	if(!equ(dis1,0))
		return -2;
	Float dis2 = distance(pt,c.center);
	if(equ(dis2,c.radius))
		return 0;
	else
		return more_than(dis2,c.radius) ? 1 : -1;
}

//�������ε����Բ
Circle make_circle(const Point &pt1,const Point &pt2,const Point &pt3)
{
	Arc arc(pt1,pt2,pt3);
	Circle c;
	resume_circle(arc,c);
	return c;
}

//�ռ乲���ֱ�ߺ�Բ���Ľ��㣬���ؽ������
//����������ʱ����д��cross1��cross2����һ������ʱ����д��cross1
int intersect(const LLine &ln,const Arc &arc,Point &cross1,Point &cross2)
{
	Circle c;
	resume_circle(arc,c);
	Point p1,p2;
	int n = intersect(ln,c,p1,p2);
	int i = 0,j = 0;
	if(n == 2){
		if(relation(p1,arc))
			i++;
		if(relation(p2,arc))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;
			cross2 = p2;
		}
		return i + j;
	}
	else if(n == 1){
		if(relation(p1,arc)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

/////������߶κ�ֱ�ߵĽ��㣬����д�����pt���޽��㷵�ؼ�
bool intersect(const SLine &sl,const LLine &ln,Point &pt)
{
	LLine lnx = make_line(sl);
	Point px;
	bool flag = intersect(lnx,ln,px);
	if(!flag)
		return false;
	else if(relation(px,sl)){
		pt = px;
		return true;
	}
	else
		return false;
}

////��������߶εĽ��㣬����д�����pt���޽��㷵�ؼ�
bool intersect(const SLine& sl1, const SLine& sl2, Point& pt)
{
	LLine slh1 = make_line(sl1);
	LLine slh2 = make_line(sl2);
	Point ph;
	bool flag = intersect(slh1,slh2,ph);
	if(!flag)
		return false;
	else if(relation(ph,sl1) && relation(ph,sl2)){
		pt = ph;
		return true;
	}
	else
		return false;
}

////������߶κ�Բ���Ľ��㣬���ؽ������
//����������ʱ����д��cross1��cross2����һ������ʱ����д��cross1
int intersect(const SLine &sl,const Arc &arc,Point &cross1,Point &cross2)
{
	LLine ln = make_line(sl);
	Point p1,p2;
	int flag = intersect(ln,arc,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){ 
		if(relation(p1,sl))
			i++;
		if(relation(p2,sl))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;cross2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sl)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

////������߶κ�Բ�Ľ��㣬���ؽ������
//����������ʱ����д��cross1��cross2����һ������ʱ����д��cross1
int intersect(const SLine &sl,const Circle &c,Point &cross1,Point &cross2)
{
	LLine ln = make_line(sl);
	Point p1,p2;
	int flag = intersect(ln,c,p1,p2);
	int i = 0,j = 0;
	if(flag == 2){ 
		if(relation(p1,sl))
			i++;
		if(relation(p2,sl))
			j++;
		if(i + j == 1)
			cross1 = (i == 1) ? p1 : p2;
		if(i + j == 2){
			cross1 = p1;cross2 = p2;
		}
		return i + j;
	}
	else if(flag == 1){
		if(relation(p1,sl)){
			cross1 = p1;
			i++;
		}
		return i;
	}
	else
		return 0;
}

//�ж�����Բ�Ƿ��棬�����淵�ؼ�
bool is_conplane(const Circle &c1,const Circle &c2)
{
	Plane pla1 = make_plane(c1);
	Plane pla2 = make_plane(c2);
	Point nor1 = normalize(get_nor(pla1));
	Point nor2 = normalize(get_nor(pla2));
	bool flag = (nor1 == nor2) || (nor1 == (nor2 * (-1)));
	if(!flag)
		return false;
	Float dis = distance(c1.center,pla2);
	return equ(dis,0);
}

//����Բ��λ�ù�ϵ,������ʱ����-1
//��ȫ���뷵��0�����з���1�����в��غϷ���2����ȫ�ڰ�������3
//��ȫ�غϷ���4��һ���ཻ����5
int relation(const Circle &c1,const Circle &c2)
{
	bool flag = is_conplane(c1,c2);
	if(!flag)
		return -1;
	Float dis = distance(c1.center,c2.center);
	Float dsum = c1.radius + c2.radius;
	Float dif = fabs(c1.radius - c2.radius);
	if(more_than(dis,dsum))
		return 0;
	else if(equ(dis,dsum))
		return 1;
	else if(equ(dis,dif) && !(c1.center == c2.center))
		return 2;
	else if( less_than(dis,dif) )
		return 3;
	else
		return (c1.center == c2.center) && equ(c1.radius,c2.radius) ? 4 : 5;
}

//�ж�Բc1�Ƿ��ڹ����Բc2����
bool dcircle_in(const Circle &c1,const Circle &c2)
{
	int flag = relation(c1,c2);
	if(flag == 2 || flag == 3)
		return less_than(c1.radius,c2.radius);
	return false;
}

//ԲcͶӰ��xoyƽ���ϣ�phΪͶӰ��Բ��һ�㣬�ָ�ph��Բc�ϵĵ�
Point resume_point(const Point &ph,const Circle &c)
{
	Plane pla = make_plane(c.center,make_point(c.nor));
	return resume_point(ph,pla);
}

//�Ƕ�ת������
Float convert_degree(const Float &degree)
{
  return degree * geo::pi() / 180.0;
}

//����ת���Ƕ�
Float convert_radian(const Float &radian)
{
	return radian*180.0 / geo::pi();
}

//��ά�ռ��ڵ�pl�ͷ���vec����ֱ��L,��pl��pt��L�ϵ�ͶӰ�ľ���
//����vec��������ĸ���
Float dis2d(const Point &pl,const Point &pt,const Normal &vec)
{
	Point direction = make_point(vec);
	Point plh = project(pl);
	Point pth = project(pt);
	Point vech = project(direction);
	LLine lnh = make_line(plh,vech);
	Point phh = project(pth,lnh);
	Float dis = distance(plh,phh);
	return (normalize(vech) == normalize(phh - plh)) ? dis : (-dis);
}

//��ά�ռ��ڵ�pt��ֱ��ln�ϵ�ͶӰ�ͷ���vec����ֱ��L
//��ͶӰ�㵽pt��L�ϵ�ͶӰ�ľ��룬����vec��������ĸ���
Float dis2d(const Point &pt,const LLine &ln,const Normal &vec)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point direction = make_point(vec);
	Point vech = project(direction);
	Point phh = project(pth,lnh);
	LLine newh = make_line(phh,vech);
	Point pthh = project(pth,newh);
	Float dis = distance(phh,pthh);
	return (normalize(vech) == normalize(pthh - phh)) ? dis : (-dis);
}

//��ά�ռ��������pt��ƽ����ֱ��ln��ֱ��
LLine offset2d(const Point &pt,const LLine &ln)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point vech = lnh.pt2 - lnh.pt1;
	return make_line(pth,vech);
}

//��ά�ռ�����ֱ��lnsourse��pt����ƽ��dis������ֱ��
LLine offset2d(const LLine &lnsourse,const Point &pt,Float dis)
{
	Point pth = project(pt);
	LLine lnh = project(lnsourse);
	Point pthh = project(pth,lnh);
	if(pth == pthh)
		return lnh;
	else{
		Point vech = normalize(pth - pthh);
		Point pxh = pthh + vech*dis;
		Point vecl = lnh.pt2 - lnh.pt1;
		return make_line(pxh,vecl);
	}
}

//��ά�ռ��������ⴹֱ��ln��ֱ��
LLine erect2d(const LLine &ln)
{
	LLine lnh = project(ln);
	Point vec = lnh.pt2 - lnh.pt1;
	Point vech;
	vech.set(-vec.y,vec.x,0);
	return make_line(lnh.pt1,vech);
}

//��ά�ռ�������㴹ֱ��ln��ֱ��
LLine erect2d(const Point &pt,const LLine &ln)
{
	Point pth = project(pt);
	LLine lnh = project(ln);
	Point vec = lnh.pt2 - lnh.pt1;
	Point vech;
	vech.set(-vec.y,vec.x,0);
	return make_line(pth,vech);
}

//��ά�ռ������center��pt�ķ�����x���������ʱ���
Float get_angle2d(const Point &pt,const Point &center)
{
	Point vec;
	vec.set(pt.x - center.x,pt.y - center.y,0);
	Float ang = angle(vec,ox);
	if(more_equ(vec.y,0))
		return ang;
	else
		return 2 * geo::pi() - ang;
}

//��ά�ռ�����Բ�����зֽ�
Float bisector_radian2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	Float ang_start = get_angle2d(arc.start,c.center);
	Float ang_end = get_angle2d(arc.end,c.center);
	Float ang = (ang_start + ang_end) / 2;
	if(more_equ(ang_start,ang_end))
		return ang + geo::pi();
	else
		return ang;
}

//��Բ��������֮��Ļ��е㣬����4�Ǹû���Ӧ��Բ
Point middle_point(const Arc &arc,const Point &p1,const Point &p2,const Circle &c)
{
	Point middle = (p1 + p2) * 0.5;
	Point vecl = p1 - p2;
	Point vecn = make_point(c.nor) * vecl;
	Point vec = normalize(vecn);
	Point pt1 = c.center + vec * c.radius;
	Point pt2 = c.center - vec * c.radius;
	SLine sl1 = create_sline(p1,p2),sl2;
	bool flag1 = p1 == arc.start && p2 == arc.end;
	bool flag2 = p1 == arc.end && p2 == arc.start;
	if(flag1 || flag2)
		return (relation(pt1,arc)) ? pt1 : pt2;
	else if(p1 == arc.start && p2 != arc.end)
		sl2 = create_sline(pt1,arc.end);
	else
		sl2 = create_sline(pt1,arc.start);
	Point cross;
	return (intersect(sl1,sl2,cross)) ? pt1 : pt2;
}

//��Բ���Ļ��е�
Point bisector_point2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	return middle_point(arc,arc.start,arc.end,c);
}

//��Բ���Ļ�����
LLine bisector_line2d(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	Point mid = middle_point(arc,arc.start,arc.end,c);
	return create_line(c.center,mid);
}

//��ά�ռ��ڹ���pt��x�������angle�Ƕȵ�ֱ�ߣ���ֱ����ƽ��ptһ����λ
Point polarto2d(const Point &pt,Float angle)
{
	Point px;
	px.set(pt.x + cos(angle),pt.y + sin(angle),0);
	return px;
}

//��ά�ռ��ڹ���pt��x�������angle�Ƕȵ�ֱ��
LLine make_line(const Point &pt,Float angle)
{
	Point pth = project(pt);
	Point pxh = polarto2d(pt,angle);
	return create_line(pth,pxh);
}

//��ά�ռ����󻡶�����Ӧ�ķ���
Normal convert2d(Float angle)
{
	Normal vec;
	vec.set(cos(angle),sin(angle),0);
	return vec;
}

//��ά�ռ��ڹ�ptbase��ƽ����lnbase��ֱ��L����pt��L�ϵ�ͶӰ
Point project2d(const Point &pt,const LLine &lnbase,const Point &ptbase)
{
	LLine lnh = offset2d(ptbase,lnbase);
	Point pth = project(pt);
	return project(pth,lnh);
}

//��ά�ռ�������direction����x�����ʱ���
Float radian2d(const Normal &direction)
{
	Point vec = make_point(direction);
	return get_angle2d(vec,O);
}

//��ά�ռ�����������ȷ���ķ������x�����ʱ���
Float radian2d(const Point &ptend,const Point &ptstart)
{
	Point vec = ptend - ptstart;
	return get_angle2d(vec,O);
}

Float radian2d(const LLine &ln)
//��ά�ռ�����ֱ������Ӧ�Ĺ���x�����ʱ���
{
	Point vec = ln.pt2 - ln.pt1;
	return get_angle2d(vec,O);
}

Float stdradian(Float radian)
//��һ�㻡��Ϊ[0,2*PI)֮��Ļ���
{
	Float result = radian;
	Float pai2 = 2 * geo::pi();
	while(less_than(result,0))
		result += pai2;
	while(more_equ(result,pai2))
		result -= pai2;
	return result;
}

Float stdangle(Float angle)
//��һ��Ƕ�Ϊ[0,360)֮��ĽǶ�
{
	Float result = angle;
	while(less_than(result,0))
		result += 360;
	while(more_equ(result,360))
		result -= 360;
	return result;
}

//���ݲ�ͬ��������ػ��������ڵ�����
//������on_offΪ��ʱ��x��������ڵ�һ���ޣ�y��������ڵڶ����ޣ��Դ����ƣ�
//������on_offΪ��ʱ��x��������ڵ������ޣ�y��������ڵ�һ���ޣ��Դ����ƣ�
int quadrant(Float radian,const bool &on_off)
{
	Float result = stdradian(radian);
	Float pai = geo::pi() / 2;
	int n = result / pai;
	if(on_off)
		return n+1;
	else{
		if(equ(result,0))
			return 4;
		else if(equ(result,pai))
			return 1;
		else if(equ(result,2 * pai))
			return 2;
		else if(equ(result,3 * pai))
			return 3;
		else
			return n + 1;
	}
}
//���ƽ���λ�ù�ϵ
//����ƽ���Ϸ���0��ƽ�洹ֱ��xoy��ʱ����-2������ƽ���Ϸ�����1�����·�����-1
int relation(const Point& pt,const Plane& pla)
{
	Float dis = distance(pt,pla);
	if(equ(dis,0))
		return 0;
	if(equ(pla.c,0))
		return -2;
	Float zh = -(pla.d + pla.a * pt.x + pla.b * pt.y) / pla.c;
	return less_than(zh,pt.z) ? 1 : -1;
}

////////��������С�������Ӿ���////////////////////

////ֱ�ߺͶ���εĴ�͸��ϵ,����͸�����棬��͸���ؼ�
////ֱ��ֻ����ĳ�߽�ʱ��Ϊ����͸
static bool penetrate_relation(const LLine& ln,const std::vector<Point>& pts)
{
	int i,j;
	bool flag = 1;
	Point vec_normalize,ph;
	for(i = 0;i < pts.size();i++){
		if(!equ(distance(pts[i],ln),0)){
			ph = project(pts[i],ln);
			vec_normalize = normalize(pts[i] - ph);
			break;
		}
	}
	for(j = i+1;j < pts.size();j++){
		if(!equ(distance(pts[j],ln),0)){
			Point ph_temp = project(pts[j],ln);
			Point vec_normalize_temp = normalize(pts[j] - ph_temp);
			if(vec_normalize != vec_normalize_temp){
				flag = 0;
				break;
			}
		}
	}
	return flag;
}
////���ÿ������ζ�����͹�㻹�ǰ���
////���ʾ͹�㣬�ٱ�ʾ����
static void get_flags(const std::vector<Point>& pts,std::vector<bool>& flags)
{
	if(pts.size() <2)
		return;
	int i,j;
	LLine ln;
	for(i = 0;i < pts.size()-1;i++){
		j = i;
		ln = create_line(pts[i],pts[++j]);
		flags.push_back(penetrate_relation(ln,pts));
	}
	ln = create_line(pts[pts.size()-1],pts[0]);
	flags.push_back(penetrate_relation(ln,pts));
}

static void get_chimb(const std::vector<Point>& pts,std::vector<Point>& chimb)
////ȡ����ε�͹����������ÿ��͹�㣬˳�򲻱�
{
  if(pts.empty()){
    return;
  }
	std::vector<bool> flags;
	get_flags(pts,flags);
  if(flags.empty()){
    return;
  }
	if(flags[0] || flags[flags.size()-1])
		chimb.push_back(pts[0]);
	int i, n = pts.size();
	for(i = 1;i < n;i++){
		if(flags[i-1] || flags[i])
			chimb.push_back(pts[i]);
	}
}

static Float get_area(const LLine& ln,const std::vector<Point>& pts)
////�õ�͹�������lnΪ���ߵ���Ӿ������
{
	std::set<Point> pro_pts;
	Float max_high = 0,high;
	int i, n = pts.size();
	for(i = 0;i < n;i++){
		pro_pts.insert(project(pts[i],ln));
		high = distance(pts[i],ln);
		if(more_than(high,max_high))
			max_high = high;
	}
	Float len = distance(*(pro_pts.begin()),*(--pro_pts.end()));
	return max_high * len;
}

Float get_min_area(const std::vector<Point>& pts)
////�õ�����ε���С��Ӿ������
{
	if(pts.size() <1)
		return -1;
	std::vector<Point> chimb;
	get_chimb(pts,chimb);
	int n = chimb.size();
	if(n < 3)
		return -1;
	int i,j;
	LLine ln = create_line(chimb[0],chimb[n-1]);
	Float min_area = get_area(ln,chimb);
	Float area;
	for(i = 0;i < n-1;i++){
		j = i;
		ln = create_line(chimb[i],chimb[++j]);
		area = get_area(ln,chimb);
		if(less_than(area,min_area))
			min_area = area;
	}
	return min_area;
}

///// to zhong /////
////��pt�����Ŵ�ֱ��ln�ķ���ƽ��dis����
////sign_pt��ƽ�Ʒ���sign_pt��ֱ������������ƶ������������ƶ�
Point get_pt(const LLine &ln,const Point & pt,const Point & sign_pt,Float dis)
{
	Point ph = project(sign_pt,ln);
	Point vec = sign_pt - ph;
	return pt + normalize(vec) * dis;
}

static bool get_line(const LLine &ln1,const LLine &ln2,
										Float dis,LLine& ln) ////����distance����ר��
{
	Point px;
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	bool flag = more_than(dis1,0);
	Point ph1 = project(ln1.pt1,ln2);
	Point ph2 = project(ln1.pt2,ln2);
	Point normal1 = normalize(ln1.pt1 - ph1);
	Point normal2 = normalize(ln1.pt2 - ph2);
	if(flag && more_than(dis2,0)){
		if(normal1 != normal2)
			return false;////ֱ��ln1����ֱ��ln2��һ�࣬�޷�ȷ���ӳ���
		else
			px = ph1 + normal1 * dis;
	}
	else
		px = flag ? (ph1 + normal1 * dis) : (ph2 + normal2 * dis);
	ln = make_line(px,ln2.pt2 - ln2.pt1);
	return true;
}

static bool get_cross(const LLine &ln1,const LLine &ln2,
											Float dis,Point& cross) ////����distance����ר��
{
	Float dis1 = distance(ln1.pt1,ln2);
	Float dis2 = distance(ln1.pt2,ln2);
	bool flag = more_than(dis1,0);
	Point ph1 = project(ln1.pt1,ln2);
	Point ph2 = project(ln1.pt2,ln2);
	Point normal1 = normalize(ln1.pt1 - ph1);
	Point normal2 = normalize(ln1.pt2 - ph2);
	if(flag && more_than(dis2,0)){
		if(normal1 != normal2)
			return false;////ֱ��ln1����ֱ��ln2��һ�࣬�޷�ȷ���ӳ���
		else
			cross = ph1 + normal1 * dis;
	}
	else
		cross = flag ? (ph1 + normal1 * dis) : (ph2 + normal2 * dis);
	return true;
}

Float distance(const LLine &ln1,const LLine &ln2,Float dis,Point &cross)
{
	int flag = relation(ln1,ln2);
	switch(flag){
		case -1 : return 0;
		case 1 : {
			bool sign = get_cross(ln1,ln2,dis,cross);
			if(!sign)
				return -1;
			return dis;
		}
		case 2 : {
			Point pt;
			intersect(ln1,ln2,pt);
			LLine ln;
			bool sign = get_line(ln1,ln2,dis,ln);
			if(!sign)
				return -1;
			intersect(ln1,ln,cross);
			return distance(pt,cross);
		}
		default : return -1;
	}
}
///// to zhong /////

//������������ƽ��ķ�����
Point get_nor(const Point& pt1,const Point& pt2,const Point& pt3)
{
	Point vec1 = pt1 - pt2;
	Point vec2 = pt1 - pt3;
	return normalize(vec1 * vec2);
}

bool less_arc(const Arc &arc)  //�ж�Բ���Ƿ����Ի���Բ�Ľ�С��180�ȣ�
{
	Circle c;
	resume_circle(arc,c);
	LLine ln1 = create_line(arc.start,arc.end);
	LLine ln2 = create_line(arc.path,c.center);
	Point cross;
	return intersect(make_sline(ln1),make_sline(ln2),cross);
}

Float get_angle(const Arc &arc)  //��Բ����Բ�Ľ�
{
	Circle c;
	resume_circle(arc,c);
	Point vec1 = arc.start - c.center;
	Point vec2 = arc.end - c.center;
	double num = multiply(vec1,vec2) / (mos(vec1) * mos(vec2));
	if(num == -1)
		return pi();
	else if(less_arc(arc))
		return acos(num);
	else
		return 2*pi() - acos(num);
}

////�󾭹��Ի������ϵ����ߵĽ���
Point get_pt(const Arc &arc)
{
	assert(less_arc(arc));
	Circle c;
	resume_circle(arc,c);
	Point normal = make_point(c.nor);
	Point vec1 = normal * (c.center - arc.start);
	Point vec2 = normal * (c.center - arc.end);
	LLine ln1 = make_line(arc.start,vec1);
	LLine ln2 = make_line(arc.end,vec2);
	Point pt;
	intersect(ln1,ln2,pt);
	return pt;
}

//��Բ���뾶
Float get_radius(const Arc &arc)
{
	Circle c;
	resume_circle(arc,c);
	return c.radius;
}

////��Բ�����Ի�ʼ��Ϊ������ת����
////c��Բ����Ӧ��Բ
Point rotate_direction(const Arc &arc,const Circle &c)
{
	Point mid = middle_point(arc,arc.start,arc.end,c);
	LLine ln = make_line(c.center,arc.start);
	Point ph = project(mid,ln);
	return normalize(mid - ph);
}

////Բ��������һ�㵽Բ����ʼ���ͬʱ��ǣ������ƣ�
////center��Բ����ӦԲ��Բ��
Float get_angle(const Arc &arc,const Point &center,
								const Point &rotate_vec,const Point &pt)
{
	if(pt == arc.start)
		return 0;
	Point vec1 = arc.start - center;
	Point vec2 = pt - center;
	if(normalize(vec1) == normalize(vec2 * (-1)))
		return pi();
	LLine ln = make_line(center,arc.start);
	Point ph = project(pt,ln);
	Point vec = normalize(pt - ph);
	Float ang = angle(vec1,vec2);
	return (vec == rotate_vec) ? ang : (2*pi() - ang);
}

////Բ������һ�㵽Բ�ϻ����ͬʱ��ǣ������ƣ�
Float get_angle(const Circle &c,const Point &base,const Point &pt)
{
	LLine ln = make_line(c.center,base);
	Point ph = project(pt,ln);
	if(pt == ph)
		return (pt == base) ? 0 : pi();
	Point vech1 = normalize(pt - ph);
	Point normal = make_point(c.nor);
	Point vecl = base - c.center;
	Point vech2 = normalize(normal * vecl);
	Float ang = angle(vecl, pt - c.center);
	return (vech1 == vech2) ? ang : (2*pi() - ang);
}

static void deal_sort(std::vector<Point> &pts,std::vector<Float> &angs,
									 std::vector<Point> &result)  ////����sort����ר��
{
	int i,sign;
	Point temp_pt;
	Float temp_ang;
	while(pts.size()){
		temp_ang = angs[0];
		sign = 0;
		for(i = 1; i < angs.size(); i++){
			if(less_than(angs[i],temp_ang)){
				temp_ang = angs[i];
				sign = i;
			}
		}
		result.push_back(pts[sign]);
		pts.erase(&pts[sign]);
		angs.erase(&angs[sign]);
	}
}

////��Բ���ϵĵ㼯����(�㼯�в������ظ���)(����Բ��start��)
bool sort(const Arc &arc,const std::vector<Point> &pts,std::vector<Point> &result)
{
	int i,n = pts.size();
	if(n < 2)
		return false;
	Circle c;
	resume_circle(arc,c);
	Point rotate_vec = rotate_direction(arc,c);
	std::vector<Float> angs;
	for(i = 0; i < n; i++)
		angs.push_back(get_angle(arc,c.center,rotate_vec,pts[i]));
	std::vector<Point> temp = pts;
	deal_sort(temp,angs,result);
	return true;
}

////��Բ�ϵĵ㼯����(�㼯�в������ظ���)
bool sort(const Circle &c,const std::vector<Point> &pts,std::vector<Point> &result)
{
	int i,n = pts.size();
	if(n < 3)
		return false;
	result.push_back(pts[0]);
	std::vector<Float> angs;
	for(i = 1; i < n; i++)
		angs.push_back(get_angle(c,pts[0],pts[i]));
	std::vector<Point> temp_pt = pts;
	temp_pt.erase(&temp_pt[0]);
	deal_sort(temp_pt,angs,result);
	return true;
}

///////////////////////merge_arc///////////////////////////
////������������ȣ��������ʾ���
static bool length_equ(Float num1,Float num2)
{
	return fabs(num1 - num2) <= LIMIT;
}

////��������sort_lns���±���j��k֮����߼ӵ�������new_lns��
static void add_line(const std::vector<LLine> &sort_lns,int j,int k,
										 std::vector<LLine> &new_lns)
{
	int i;
	for(i = j; i <= k;i++)
		new_lns.push_back(sort_lns[i]);
}

////�õ�������sort_lns��ÿ���ߵĳ���
static void get_lens(const std::vector<LLine> &sort_lns,std::vector<Float> &lens)
{
	int i;
	for(i = 0; i < sort_lns.size(); i++){
		Float dis = distance(sort_lns[i].pt1,sort_lns[i].pt2);
		lens.push_back(dis);
	}
}

static void add_line(const std::vector<LLine> &sort_lns,int n1,int n2,
										 std::vector<LLine> &new_lns,int s,int e)
////�±�[n1,n2]����[s,e],���±���[n1,s),(e,n2]��ֱ�߷����µ�ֱ��������
{
	int i;
	for(i = n1; i < s; i++)
		new_lns.push_back(sort_lns[i]);
	for(i = e+1; i <= n2; i++)
		new_lns.push_back(sort_lns[i]);
}

////�жϵ��Ƿ���Բ�ϣ�����Բ�Ϸ��ؼ�
static bool is_on_circle(const Point &pt,const Circle &c)
{
	Float dis = distance(pt,c.center);
	return fabs(dis - c.radius) <= LIMIT;
}

////�ж�������sort_lns���±���i��e֮������Ƿ��кϳɻ�����
////����У��򷵻��棬��ʱn2���ܺϳɻ���ĩ�߶��±꣬����n2 <= e
////��û�У���n2����Чֵ�����ؼ�
static bool is_merge_arc(const std::vector<LLine> &sort_lns,
												 int i,int e,int &n2)
{
	if(i + 1 >= e)
		return false;
	Circle c = make_circle(sort_lns[i].pt1,sort_lns[i].pt2,sort_lns[i+1].pt2);
	int j,count = 0;
	for(j = i+2;j <= e; ++j){
		if(is_on_circle(sort_lns[j].pt2,c))
			count++;
		else
			break;
	}
	if(count){
		n2 = i + count + 1;
		return true;
	}
	return false;
}

////�ж�������sort_lns���±���s��e֮������Ƿ��кϳɻ�����
////����У��򷵻��棬��ʱn1��n2��λ��s��e֮���ܺϳɻ���ʼĩ�߶��±�
////������n1 >= s, n2 <= e
////��û�У���n1��n2����Чֵ�����ؼ�
static bool is_merge_arc(const std::vector<LLine> &sort_lns,
												 int s,int e,int &n1,int &n2)
{
	int i;
	for(i = s; i < e; i++){
		bool flag = is_merge_arc(sort_lns,i,e,n2);
		if(flag){
			n1 = i;
			return true;
		}
	}
	return false;
}

////�ú������������sort_lns���±�λ��s,e֮���ܺϳɵĻ���new_arcs��
////���ڼ��������ܺϳɻ����߼ӵ�������new_lns��
////lens��������sort_lns��ÿһ���߶εĳ�������
////���ȳ��ҹ�Բ���ܺϳɻ����߶γ��ȴ��ڳ���range������Щ�߶β��ϳɻ������ɼӵ�������new_lns�У���ʱflag = -1
////���ȳ��ҹ�Բ���ܺϳɻ����߶γ���С�ڳ���range������Щ�߶κϳɻ����ϳɵĻ��ӵ�new_arcs�У���ʱflag = 1
static void add_arc_line(const std::vector<LLine> &sort_lns,std::vector<LLine> &new_lns,
												 std::vector<Arc> &new_arcs,const std::vector<Float> &lens,
												 int s,int e,int &flag,Float range)
{
	int n1, n2;
	bool sign = is_merge_arc(sort_lns,s,e,n1,n2);
	if(!sign)
		add_line(sort_lns,s,e,new_lns);
	else if(more_equ(lens[n1],range)){
		flag = -1;
		add_line(sort_lns,s,e,new_lns);
	}
	else{
		flag = 1;
		add_line(sort_lns,s,e,new_lns,n1,n2);
		Arc arc(sort_lns[n1].pt1,sort_lns[n1].pt2,sort_lns[n2].pt2);
		new_arcs.push_back(arc);
	}
}

////�ڳ�������lens��Ѱ���±��s��ʼ�����ȳ����߶�
////e�������ȳ������һ���߶��±꣬n������lens�ĳ���
////�������ȳ����߶θ������ڵ���2�򷵻��棬���򷵻ؼ�
static bool find_equ_length(const std::vector<Float> &lens,int s,int n,int &e)
{
	int i, count = 0;
	for(i = s+1; i < n; i++){
		if(length_equ(lens[s],lens[i]))
			++count;
		else
			break;
	}
	if(count > 1){
		e = s + count;
		return true;
	}
	return false;
}

////��������sort_lns�п��Ժϳɻ����߶κϳɻ���ӵ�new_arcs��
////����������ӵ�new_lns�У�range�Ǻϳɻ��ļ��޳���
////���ϳ���һ�����򷵻�1���кϳɻ����߶ε����ȴ���range���򷵻�-1�����򷵻�0
static int merge_arc(const std::vector<LLine> &sort_lns,std::vector<LLine> &new_lns,
											std::vector<Arc> &new_arcs,Float range)
{
	int s,e,n = sort_lns.size(),flag = 0;
	std::vector<Float> lens;
	bool sign;
	get_lens(sort_lns,lens);
	for(s = 0; s < n; s++){
		sign = find_equ_length(lens,s,n,e);
		if(sign){
			add_arc_line(sort_lns,new_lns,new_arcs,lens,s,e,flag,range);
			s = e;
		}
		else
			new_lns.push_back(sort_lns[s]);
	}
	if(new_arcs.size())
		return 1;
	return flag;
}

////��������temp_lns��Ѱ�ҵ�һ�����ȴ���range���ߣ������ȶ�С��range�򷵻ؼ�
static bool get_first_line(std::vector<LLine> &temp_lns,
													 Float range,LLine &ln)
{
	int i,flag = 0;
	Float dis;
	for(i = 0; i < temp_lns.size(); i++){
		dis = distance(temp_lns[i].pt1,temp_lns[i].pt2);
		if(less_than(range,dis)){
			flag = 1;
			ln = temp_lns[i];
			temp_lns.erase(&temp_lns[i]);
			break;
		}
	}
	return flag == 1;
}

////���ֱ��temp_ln�ĵ�һ���˵���temp_lns�ĵ�i���ߵ�ĳ�˵�����
////����temp_ln����һ���˵���temp_lns�ĵ�i���ߵ���һ���˵�
////Ȼ���temp_lns��ɾ����i���ߣ����temp_ln��sort_lns���飬������
////��temp_lns�ĵ�i���߲���temp_ln�ĵ�һ���˵��������򷵻ؼ�
static bool link_point(std::vector<LLine> &temp_lns,LLine &temp_ln,
											int i,std::vector<LLine> &sort_lns)
{
	if(temp_ln.pt1 == temp_lns[i].pt1 || temp_ln.pt1 == temp_lns[i].pt2){
		if(temp_ln.pt1 == temp_lns[i].pt1)
			temp_ln.pt2 = temp_lns[i].pt2;
		else
			temp_ln.pt2 = temp_lns[i].pt1;
		sort_lns.push_back(temp_ln);
		temp_lns.erase(&temp_lns[i]);
		return true;
	}
	return false;
}

////��������temp_lns��Ѱ���Ƿ�����temp_ln�����ӵ���
////�������temp_ln�ĵ�һ���˵���Ϊ���ӵĶ˵㣬��һ���˵���Ϊ��֮���ӵ��ߵ���һ���˵�
////Ȼ�����temp_ln��sort_lns�У�Ȼ����temp_ln�ĵ�һ���˵�Ϊ���ĵڶ����˵�
////�����������temp_lns���Ҳ�����temp_ln���ӵ����򷵻ؼ�
static bool link_point(std::vector<LLine> &temp_lns,LLine &temp_ln,
											std::vector<LLine> &sort_lns)
{
	int i,sign = 0;
	bool flag;
	for(i = 0; i < temp_lns.size(); i++){
		flag = link_point(temp_lns,temp_ln,i,sort_lns);
		if(flag){
			sign = 1;
			break;
		}
	}
	if(sign){
		temp_ln.pt1 = temp_ln.pt2;
		return true;
	}
	return false;
}

////��������lns������β������˳�������������������ӵ�sort_lns��
////sort_lns��ǰһ���ߵĵڶ����˵�������Ӻ�һ���ߵĵ�һ���˵�
////sort_lns�еĵ�һ���ߵĳ��ȱ������range
////lns��������е��ߵĳ��ȶ�С�ڵ���range������sort_lns�е��߲��ܹ��ɻ��򷵻ؼ�
static bool sort_line(const std::vector<LLine> &lns,Float range,
											std::vector<LLine> &sort_lns)
{
	std::vector<LLine> temp_lns = lns;
	LLine ln,temp_ln;
	bool flag = get_first_line(temp_lns,range,ln);
	if(!flag)
		return false;
	sort_lns.push_back(ln);
	temp_ln.pt1 = ln.pt2;
	while(temp_lns.size()){
		bool flag = link_point(temp_lns,temp_ln,sort_lns);
		if(!flag)
			return false;
	}
	return true;
}

////ȥ��������lns���غϵ��ߣ�ȥ��֮�������ӽ�news��
static void remove_repeat(const std::vector<LLine> &lns,std::vector<LLine> &news)
{
	int i;
	std::vector<LLine> temp_lns = lns;
	LLine temp;
	while(temp_lns.size()){
		temp = temp_lns[0];
		news.push_back(temp);
		temp_lns.erase(&temp_lns[0]);
		for(i = 0; i < temp_lns.size(); i++)
			if(temp == temp_lns[i]){
				temp_lns.erase(&temp_lns[i]);
				break;
			}
	}
}

////�ж���ln1����ln2�Ƿ��ߣ����������ϲ���һ����д��ln1
////�������򷵻ؼ�
static bool is_conline(LLine &ln1,LLine &ln2)
{
	if(!superposition(ln1,ln2))
		return false;
	ln1.pt2 = ln2.pt2;
	return true;
}

////������sort_lns��һ�����������飨��β�����Ļ����������ڹ��ߵ��ߺϲ�
static void remove_conline(std::vector<LLine> sort_lns)
{
	if(sort_lns.size() < 2)
		return;
	int sign = 1;
	while(sign){
		int i, n = sort_lns.size();
		for(i = 0; i < n-1; i++){
			if(is_conline(sort_lns[i],sort_lns[i+1])){
				sort_lns.erase(&sort_lns[i+1]);
				break;
			}
		}
		if(sort_lns.size() == n)
			sign = 0;
	}
	if(sort_lns.size() < 2)
		return;
	if(is_conline(sort_lns[sort_lns.size()-1],sort_lns[0]))
		sort_lns.erase(&sort_lns[0]);
}

////�ϳɻ������������غϳɵĻ�����
int merge_arc(const std::vector<LLine> &lns,Float range,
							 std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs)
{
	int n = lns.size();
	if(n <= 3){
		add_line(lns,0,n-1,new_lns);
		return 0;
	}
	else{
		std::vector<LLine> sort_lns,news;
		remove_repeat(lns,news);
		bool flag = sort_line(news,range,sort_lns);
		if(!flag){
			new_lns = news;
			return 0;
		}
		remove_conline(sort_lns);
		return merge_arc(sort_lns,new_lns,new_arcs,range);
	}
}

////��������lncsѰ���Ƿ���ĳһ���ߵ�ĳ���˵���temp
////��������������ߣ���ı�temp��ֵΪ���ߵ���һ���˵㣬�����棬���Ҳ����򷵻ؼ�
static bool is_having_link(std::vector<LLine> &lncs,Point &temp,int n)
{
	int i = 0;
	for(; i < n; i++){
		if(temp == lncs[i].pt1 || temp == lncs[i].pt2){
			if(temp == lncs[i].pt1)
				temp = lncs[i].pt2;
			else
				temp = lncs[i].pt1;
			lncs.erase(&lncs[i]);
			return true;
		}
	}
	return false;
}

////��һ������Ѱ�������˵�ĳ���˵㲢д��start���������ɻ��򷵻ؼ�
static bool get_first_point(const std::vector<LLine> &lns,Point &start)
{
	if(lns.size() < 3)
		return false;
	std::vector<LLine> lncs = lns;
	Point temp = lncs[0].pt1, temp_st = lncs[0].pt2;
	lncs.erase(&lncs[0]);
	while (lncs.size()) {
		int n = lncs.size();
		bool flag = is_having_link(lncs,temp,n);
		if(temp == temp_st)
			return false;
		if(!flag || lncs.size() == 0){
			start = temp;
			return true;
		}
	}
	return false;
}

////��һ������Ѱ������ĳ�˵��������ߣ������¸����������е�λ����j
////st�Ǹö˵��Ǹ��ߵĵ�һ���㻹�ǵڶ�����
static bool get_first_line(const std::vector<LLine> &lns,int &j,int &st)
{
	Point start;
	bool flag = get_first_point(lns,start);
	if(!flag)
		return false;
	int i, n = lns.size();
	for(i = 0;i < n;i++){
		if(start == lns[i].pt1 || start == lns[i].pt2){
			j = i;
			if(start == lns[i].pt1)
				st = 1;
			else
				st = 2;
			return true;
		}
	}
	return false;
}

////����lncs�����ӵĸ���˳���д�������sort_pts
////temp�Ǹ�����ĳ���˵㣬n������
static void add_point(std::vector<LLine> &lncs,Point &temp,
											std::vector<Point> &sort_pts,int n)
{
	int i;
	for(i = 0; i < n; i++)
		if(temp == lncs[i].pt1 || temp == lncs[i].pt2){
			sort_pts.push_back(temp);
			if(temp == lncs[i].pt1)
				temp = lncs[i].pt2;
			else
				temp = lncs[i].pt1;
			lncs.erase(&lncs[i]);
			break;
		}
}

////����lncs�����ӵĸ���˳���д�������sort_pts
////temp�Ǹ�����ĳ���˵㣬�������ж���Ĺ��������ӵ����򷵻ؼ�
static bool get_sort_pts(std::vector<LLine> &lncs,Point &temp,
												 std::vector<Point> &sort_pts)
{
	while (lncs.size()){
		int n = lncs.size();
		add_point(lncs,temp,sort_pts,n);
		if(lncs.size() && lncs.size() == n)
			return false;
	}
	return true;
}

////����lns�����ӵĸ���˳���д�������sort_pts
////�������ж���Ĺ��������ӵ����򷵻ؼ�
static bool get_sort_pts(const std::vector<LLine> &lns,std::vector<Point> &sort_pts)
{
	int st,j;
	bool flag = get_first_line(lns,j,st);
	if(!flag)
		return false;
	std::vector<LLine> lncs = lns;
	Point start = (st == 1) ? lncs[j].pt1 : lncs[j].pt2;
	sort_pts.push_back(start);
	Point temp = (st == 1) ? lncs[j].pt2 : lncs[j].pt1;
	lncs.erase(&lncs[j]);
	bool sign = get_sort_pts(lncs,temp,sort_pts);
	if(!sign)
		return false;
	sort_pts.push_back(temp);
	return true;
}

////�����������й���������м��ȥ�����������й��ߵ��ߴ���
static void remove_conline(std::vector<Point> &sort_pts)
{
	if(sort_pts.size() < 3)
		return;
	int sign = 1;
	while(sign){
		int i,n = sort_pts.size();
		if(n < 3)
			break;
		for(i = 0;i < n-2; i++){
			bool flag = relation(sort_pts[i],sort_pts[i+1],sort_pts[i+2]);
			if(!flag){
				sort_pts.erase(&sort_pts[i+1]);
				break;
			}
		}
		if(sort_pts.size() == n)
			sign = 0;
	}
}

////����������i��ʼ�ĵ��ܷ������ĵ�ϳɻ�
////���������ܺϳɻ������һ������±�д��e����������
static bool is_merge_arc(const std::vector<Point> &sort_pts,int i,int n,int &e)
{
	if((i+2) >= (n-1)){
		e = i + 1;
		return false;
	}
	Circle c = make_circle(sort_pts[i],sort_pts[i+1],sort_pts[i+2]);
	int j, count = 0;
	for(j = i+3;j < n; ++j){
		if(is_on_circle(sort_pts[j],c))
			++count;
		else
			break;
	}
	e = count ? (i + count + 2) : (i + 1);
	return count > 0;
}

////������sort_pts���ܺϳɻ��ĵ�ϳɻ�д��new_arcs
////���ܺϳɵ���д��new_lns������ϳɵĻ�������1�򷵻��棬���򷵻ؼ�
static bool merge_arc(std::vector<LLine> &new_lns,std::vector<Arc> &new_arcs,
							 const std::vector<Point> &sort_pts)
{
	if(sort_pts.size() < 4)
		return false;
	int i, n = sort_pts.size();
	for(i = 0; i < n; ++i){
		int e;
		bool flag = is_merge_arc(sort_pts,i,n,e);
		if(flag){
			Arc arc(sort_pts[i],sort_pts[i+1],sort_pts[e]);
			new_arcs.push_back(arc);
		}
		else if(e == n)
			break;
		else{
			LLine ln(sort_pts[i],sort_pts[e]);
			new_lns.push_back(ln);
		}
		i = e - 1;
	}
	return new_arcs.size() == 1;
}

////�����ϳɻ������������ҽ����ϳ�һ����ʱ������
bool merge_arc(const std::vector<LLine> &lns,std::vector<LLine> &new_lns,
							 std::vector<Arc> &new_arcs)
{
	if(lns.size() < 3)
		return false;
	std::vector<Point> sort_pts;
	bool flag = get_sort_pts(lns,sort_pts);
	if(!flag)
		return false;
	remove_conline(sort_pts);
	if(sort_pts.size() < 4)
		return false;
	return merge_arc(new_lns,new_arcs,sort_pts);
}

////�ú���������������ÿ���ߵĳ��Ⱥͳ���״̬
////ÿ������д�볤������lens��ÿ��״̬�涨�����ȴ���range��״̬Ϊ1������Ϊ0
static void get_judge_data(const std::vector<SLine> &sls,Float range,
										 std::vector<int> &flags,std::vector<Float> &lens)
{
	int i, n = sls.size();
	for(i = 0; i < n; i++){
		Float len = distance(sls[i].pt1,sls[i].pt2);
		if(less_equ(len,range))
			flags.push_back(0);
		else
			flags.push_back(1);
		lens.push_back(len);
	}
}

////�ú�������������ĳ��Ⱥ�״̬�����Ƿ�ϳ�Բ
////��һ���ߵĳ��ȴ��ڼ��޳��Ȼ����������ߵĳ��Ȳ�һ��������Ϊ���ܺϳ�Բ�����ؼ�
static bool is_consider_merge(const std::vector<int> &flags,
															const std::vector<Float> &lens)
{
	int i,n = lens.size();
	Float len = lens[0];
	for(i = 0; i < n; i++){
		if((flags[i] == 1) || (!length_equ(lens[i],len)))
			return false;
	}
	return true;
}

////�ж������߶��Ƿ��ߣ������߷��ؼ�
bool is_conline(const SLine &sl1,const SLine &sl2)
{
	LLine ln(sl2.pt1,sl2.pt2);
	Float dis1 = distance(sl1.pt1,ln);
	Float dis2 = distance(sl1.pt2,ln);
	return equ(dis1,0) && equ(dis2,0);
}

////�ϲ�������β�����ҹ��ߵ��߶�Ϊһ���߶Σ�����1����ϲ����߶�
static bool merge_conline(SLine &sl1,const SLine &sl2)
{
	if(!is_conline(sl1,sl2))
		return false;
	bool flag1 = (sl1.pt1 == sl2.pt1) || (sl1.pt1 == sl2.pt2);
	bool flag2 = (sl1.pt2 == sl2.pt1) || (sl1.pt2 == sl2.pt2);
	if(flag1 || flag2){
		SLine sl;
		if(sl1.pt1 == sl2.pt1)
			sl.set(sl1.pt2,sl2.pt2);
		if(sl1.pt1 == sl2.pt2)
			sl.set(sl1.pt2,sl2.pt1);
		if(sl1.pt2 == sl2.pt1)
			sl.set(sl1.pt1,sl2.pt2);
		if(sl1.pt2 == sl2.pt2)
			sl.set(sl1.pt1,sl2.pt1);
		sl1 = sl;
		return true;
	}
	return false;
}

////�ú����ж��������������������Ƿ��й��ߵ��߶�
////�������ϲ�������ɾ��ԭ�����߶Σ�����1�����򷵻�0
static int is_having_conline(std::vector<SLine> &sls)
{
	int i, n = sls.size();
	for(i = 0; i < n-1; i++){
		bool flag = merge_conline(sls[i],sls[i+1]);
		if(flag){
			sls.erase(&sls[i+1]);
			break;
		}
	}
	return (sls.size() == n) ? 0 : 1;
}

////�ϲ��߶������й����������߶�
static void merge_conline(std::vector<SLine> &sls)
{
	int sign = 1;
	while(sign){
		sign = is_having_conline(sls);
	}
	if(sls.size() < 2)
		return;
	if(merge_conline(sls[sls.size()-1],sls[0]))
		sls.erase(&sls[0]);
}

////���߶�����ϲ���һ��Բ�������Ϻϲ��������ؼ�
static bool merge_circle(const std::vector<SLine> &scs,Circle &c)
{
	c = make_circle(scs[0].pt1,scs[0].pt2,scs[2].pt1);
	int i, n = scs.size();
	for(i = 1; i < n; i++){
		bool flag1 = is_on_circle(scs[i].pt1,c);
		bool flag2 = is_on_circle(scs[i].pt2,c);
		if(!(flag1 && flag2))
			return false;
	}
	return true;
}

////�ϲ�Բ������
////���߶�����ϲ���һ��Բ�������Ϻϲ��������ؼ�
bool merge_circle(const std::vector<SLine> &sls,
									Float range,Circle &c)
{
	std::vector<SLine> scs = sls;
	merge_conline(scs);
	std::vector<int> flags;
	std::vector<Float> lens;
	get_judge_data(scs,range,flags,lens);
	bool flag = is_consider_merge(flags,lens);
	if(!flag || scs.size() < 2)
		return false;
	return merge_circle(scs,c);
}
///////////////////////merge_arc///////////////////////////

///////////////////////dis_parallel to zhong///////////////////////////
////��������lns��Ѱ����lnƽ���Ҿ�����С����lx
////����������С���룬��û��ƽ�е����򷵻�0
static Float find_line(const LLine &ln,const std::vector<LLine> &lns,LLine &lx)
{
	int i, j, n = lns.size();
	Float min_dis = 0;
	for(i = 0; i < n; ++i)
		if(!relation(ln,lns[i])){
			min_dis = distance(ln.pt1,lns[i]);
			lx = lns[i];
			break;
		}
	if(equ(min_dis,0))
		return 0;
	for(j = i+1; j < n; ++j){
		if(!relation(ln,lns[j])){
			Float dis = distance(ln.pt1,lns[j]);
			if(less_than(dis,min_dis)){
				min_dis = dis;
				lx = lns[j];
			}
		}
	}
	return min_dis;
}

////����������Ѱ������ln�����һ��ƽ���ߣ��������ǵ���̾���
////����һ��mid_off������ln���е��ش�ֱ��ƽ��
Float dis_parallel(const LLine &ln,const std::vector<LLine> &lns,
									 Float dis,Point &mid_off)
{
	LLine lx;
	Float len = find_line(ln,lns,lx);
	if(equ(len,0))
		return -1;
	Point mid = (ln.pt1 + ln.pt2) * 0.5;
	Point ph = project(mid,lx);
	mid_off = mid + normalize(mid - ph) * dis;
	return len;
}
///////////////////////dis_parallel to zhong///////////////////////////

///////////////////////�������������///////////////////////////
////�������鰴��β���ӵ�˳������д��sort_lns
static void sort_line(const std::vector<LLine> &lns,std::vector<LLine> &sort_lns)
{
	assert(lns.size() > 2);
	std::vector<LLine> temp_lns = lns;
	LLine temp_ln, ln = temp_lns[0];
	sort_lns.push_back(ln);
	temp_lns.erase(&temp_lns[0]);
	temp_ln.pt1 = ln.pt2;
	while(temp_lns.size())
		link_point(temp_lns,temp_ln,sort_lns);
}

////��һ���߰��˵�1���˵�2��˳�����
static Float get_area(const LLine &ln)
{
	if(equ(ln.pt1.x,ln.pt2.x))
		return 0;
	Float k = (ln.pt2.y - ln.pt1.y) / (ln.pt2.x - ln.pt1.x);
	Float b = ln.pt1.y - k * ln.pt1.x;
	Float f2 = 0.5 * k * pow(ln.pt2.x,2) + b * ln.pt2.x;
	Float f1 = 0.5 * k * pow(ln.pt1.x,2) + b * ln.pt1.x;
	return f2 - f1;
}

////�����ε����
Float get_area(const std::vector<Point> &pts)
{
	int i, n = pts.size();
	LLine ln;
	Float sum_area = 0, area;
	for(i = 0; i < n-1; i++){
		ln.set(pts[i],pts[i + 1]);
		area = get_area(ln);
		sum_area += area;
	}
	ln.set(pts[n - 1],pts[0]);
	area = get_area(ln);
	sum_area += area;
	return less_than(sum_area,0.0) ? (-sum_area) : sum_area;
}
///////////////////////�������������///////////////////////////

////�ж��߶��������Ƿ������߶�slƽ�е��߶Σ�n�����鳤�ȣ�����ƽ���򷵻���
static bool is_have_parallel(const SLine &sl,const std::vector<SLine>& refer,int n)
{
	int i, flag = 0;
	bool sign;
	for(i = 0; i < n; i++){
		sign = parallel(sl,refer[i]);
		if(sign){
			flag = 1;
			break;
		}
	}
	return flag == 1;
}

////��src���ҳ���referƽ�е��ߣ�����result�С�
void find_parallel(const std::vector<SLine>& src,
                   const std::vector<SLine>& refer,
                   std::vector<SLine>& result)
{
  int i, ns = src.size(), nr = refer.size();
	bool flag;
	for(i = 0; i < ns; i++){
		flag = is_have_parallel(src[i],refer,nr);
		if(flag)
			result.push_back(src[i]);
	}
}

////��src���ҳ���referƽ�е��ߣ�����paral�У������ķ���other��
////src��refer��paral��other�ж�������߶ε��±꣬ʵ���߶���all��
void find_parallel(const std::vector<SLine>& all, 
                   const std::vector<int>& src,
                   const std::vector<int>& refer,
                   std::vector<int>& paral,
                   std::vector<int>& other)
{
	int i, ns = src.size(), nr = refer.size();
	std::vector<SLine> refer_lns;
	for(i = 0; i < nr; i++)
		refer_lns.push_back(all[refer[i]]);
	bool flag;
	for(i = 0; i < ns; i++){
		flag = is_have_parallel(all[src[i]],refer_lns,nr);
		if(flag)
			paral.push_back(src[i]);
		else
			other.push_back(src[i]);
	}
}

//��pt2_pt1�����ĽǶȣ���x������ļнǣ������ر�׼�Ƕ�
Float get_degree(const Point &pt1,const Point &pt2)
{
	Float num = get_angle2d(pt2,pt1);
	Float ang = convert_radian(num);
	return stdangle(ang);
}
//��һ�����������ĽǶȣ���x������ļнǣ������ر�׼�Ƕ�
Float get_degree(const Point &vec)
{
	return get_degree(O,vec);
}

////����pt0_pt1�뷽��pt0_pt2�ļнǣ����ر�׼�Ƕ�
Float get_degree(const Point &pt0,const Point &pt1,const Point &pt2)
{
	Float num1 = get_degree(pt0,pt1);
	Float num2 = get_degree(pt0,pt2);
	return stdangle(num2 - num1);
}

////���߶��������ҵ��˵���temp���߶Σ�����temp��ֵ��Ϊ���߶ε���һ���˵�
////Ȼ���temp����������У����Ҳ����������߶��򷵻ؼ�
static bool link_point(std::vector<SLine> &scs,Point &temp,
											 std::vector<Point> &pts)
{
	int i, n = scs.size();
	for(i = 0; i < n; i++)
		if(temp == scs[i].pt1 || temp == scs[i].pt2){
			if(temp == scs[i].pt1)
				temp = scs[i].pt2;
			else
				temp = scs[i].pt1;
			pts.push_back(temp);
			scs.erase(&scs[i]);
			return true;
		}
	return false;
}
////ȡ������ε����򶥵�
bool get_points(const std::vector<SLine> &sls,std::vector<Point> &pts)
{
	if(sls.size()<1)
		return false;
	std::vector<SLine> scs = sls;
	Point temp = scs[0].pt1, start = scs[0].pt2;
	pts.push_back(temp);
	scs.erase(&scs[0]);
	while(temp != start){
		bool flag = link_point(scs,temp,pts);
		if(!flag)
			return false;
	}
	return true;
}
//�ж϶�����Ƿ���͹��
bool is_protruding(const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	bool sign = get_points(sls,pts);
	if(!sign)
		return false;
	std::vector<bool> flags;
	get_flags(pts,flags);
	int i, n = flags.size(), flag = 1;
	for(i = 0; i < n; i++){
		if(!flags[i]){
			flag = 0;
			break;
		}
	}
	return flag == 1;
}


///////////////////////rect problem///////////////////////////
////ȡ�����ε������߷Ž��߶�������
void make_line(const Box& box,std::vector<SLine> &sls)
{
	SLine sl;
	Point pt1,pt2;
	pt1.set(box.max_.x,box.max_.y,0.0);
	pt2.set(box.min_.x,box.max_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.min_.x,box.min_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.max_.x,box.min_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
	pt1 = pt2;
	pt2.set(box.max_.x,box.max_.y,0.0);
	sl.set(pt1,pt2);
	sls.push_back(sl);
}

////ȡ�����ε������߷Ž��߶�������
void make_line(const Box& box,SLine sls[])
{
	sls[0].pt1.set(box.max_.x,box.max_.y,0.0);
	sls[0].pt2.set(box.min_.x,box.max_.y,0.0);
	sls[1].pt1 = sls[0].pt2;
	sls[1].pt2.set(box.min_.x,box.min_.y,0.0);
	sls[2].pt1 = sls[1].pt2;
	sls[2].pt2.set(box.max_.x,box.min_.y,0.0);
	sls[3].pt1 = sls[2].pt2;
	sls[3].pt2.set(box.max_.x,box.max_.y,0.0);
}

////���߶�sl�������˵�������߶���������н������set������
////֮������set������vector����ͬһ���߶��ϵĵ���Ҫ�������򣬶��Ҳ������غϵ�
static int intersect(const std::vector<SLine> &sls,
										 const SLine &sl,std::set<Point> &cros)
{
	cros.insert(sl.pt1);
	cros.insert(sl.pt2);
	Point pt;
	bool flag;
	int i, n = sls.size();
	for(i = 0; i < n; i++){
		flag = intersect(sl,sls[i],pt);
		if(flag)
			cros.insert(pt);
	}
	return cros.size();
}

////set����pts�ϵĵ���λ��ͬһ���߶��ϵĵ�
////�����ĵ�j����͵�j+1������һ���߶Σ�����߶ε��е�
static Point get_mid_pt(const std::set<Point> &pts,int j)
{
	std::set<geo::Point>::const_iterator it = pts.begin();
	int count = 0;
	while(count != j){
		it++;
		count++;
	}
	std::set<geo::Point>::const_iterator temp1 = it,temp2 = ++it;
	return (*temp1 + *temp2) * 0.5;
}

////�߶κͶ���εĹ�ϵ�����ڷ���1�����ⷵ��0���ཻ����-1
////ֻ�Ƕ˵��ཻ����Ϊ�ཻ����ȫ��͸����Ϊ�ཻ
int relation(const SLine &sl,const std::vector<SLine> &sls,
						 const std::vector<Point> &pts)
{
	TRACE_OUT("geo::relation :start!\n"); 
	std::set<Point> cros;
	int n = intersect(sls,sl,cros), i, in_n = 0, out_n = 0;
	Point mid;
	for(i = 0;i < n-1; i++){
		mid = get_mid_pt(cros,i);
		if(isin(mid,pts)){
			in_n++;
		}else{
			out_n++;
		}
	}
	TRACE_OUT("geo::relation :ok!\n"); 
	if(in_n == (n - 1))
		return 1;
	else
		return (out_n == (n - 1)) ? 0 : -1;
}

////�жϾ����Ƿ��ڶ������
bool is_in(const Box &box,const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	bool sign = get_points(sls,pts);
	if(!sign)
		return false;
	std::vector<SLine> box_sls;
	make_line(box,box_sls);
	int i;
	for(i = 0; i < 4; ++i){
		if(relation(box_sls[i],sls,pts) != 1){
			return false;
		}
	}
	return true;
}

////ȡ�����ε��ĸ�����Ž���������
static void get_vertexs(const Box &box,Point vertex[])
{
	vertex[0] = box.max_;
	vertex[1].set(box.min_.x,box.max_.y,0.0);
	vertex[2] = box.min_;
	vertex[3].set(box.max_.x,box.min_.y,0.0);
}

//�жϵ��Ƿ��ھ����ڣ��ھ��α�Ե����Ϊ������
static bool is_in(const Point &pt,const Box &box)
{
	bool flag_x1 = more_equ(pt.x,box.max_.x) && less_equ(pt.x,box.min_.x);
	bool flag_x2 = more_equ(pt.x,box.min_.x) && less_equ(pt.x,box.max_.x);
	bool flag_y1 = more_equ(pt.y,box.max_.y) && less_equ(pt.y,box.min_.y);
	bool flag_y2 = more_equ(pt.y,box.min_.y) && less_equ(pt.y,box.max_.y);
	return (flag_x1 || flag_x2) && (flag_y1 || flag_y2);
}

////�жϵ������Ƿ�;����йأ�ֻҪ��һ�����ھ����ھ����йصģ�,�йط�����
static bool is_in(const Point vertex[],const Box &box)
{
	int i;
	bool flag;
	for(i = 0; i < 4; ++i){
		flag = is_in(vertex[i],box);
		if(flag)
			return true;
	}
	return false;
}

////�ж����������Ƿ����ཻ�ģ�ֻ�л��಻��������ȫ�������Ϊ���ཻ���ཻ������
static bool is_cross(const Box &box1,const Box &box2)
{
	Point vertex1[4],vertex2[4];
	get_vertexs(box1,vertex1);
	get_vertexs(box2,vertex2);
	bool flag1 = is_in(vertex1,box2);
	bool flag2 = is_in(vertex2,box1);
	return flag1 || flag2;
}

////�жϾ�������������Ƿ��ཻ���ཻ�򷵻���
bool is_cross(const Box &box,const std::vector<Box> &boxs)
{
	int i, n = boxs.size();
	bool flag;
	for(i = 0; i < n; i++){
		flag = is_cross(box,boxs[i]);
		if(flag)
			return true;
	}
	return false;
}

////Ѱ�Ұ�Χ�㼯�ϵ���С��Χ��
static void get_rect(const std::set<Point> &vertexs,Box &box)
{
	std::set<Point>::const_iterator it = vertexs.begin();
	Point pt = *it;
	box.max_ = box.min_ = pt;
	it++;
	for (;it != vertexs.end();++it){
		pt = *it;
		if(less_than(pt.x,box.max_.x))
			box.max_.x = pt.x;
		if(more_than(pt.x,box.min_.x))
			box.min_.x = pt.x;
		if(less_than(pt.y,box.min_.y))
			box.min_.y = pt.y;
		if(more_than(pt.y,box.max_.y))
			box.max_.y = pt.y;
	}
}

////Ѱ�Ұ�Χ�߶��������С��Χ��
void get_rect(const std::vector<SLine> &sls,Box &box)
{
	int i,n = sls.size();
	std::set<Point> vertexs;
	for(i = 0; i < n; i++){
		vertexs.insert(sls[i].pt1);
		vertexs.insert(sls[i].pt2);
	}
	get_rect(vertexs,box);
}
///////////////////////rect problem///////////////////////////


///////////////////////find_loops///////////////////////////
struct Line_Branch{
	SLine sl; ////ԭ�߶�
	bool single_branch;////���������ߵ������ǵ���֧���Ƕ��֧
	////ֻ���ҽ��������߶εĶ˵���ԭ�߶ε������˵�ֱ�������ʱ���߶β���Ϊ����֧
	////true�ǵ���֧��false�Ƕ��֧������������Ϊ���֧,���֧�߲�����
};

////�ж��߶�sl�ǵ���֧���Ƕ��֧������֧�����棬���򷵻ؼ�
////�㼯��pts��sl���߶�����intersect_lns�Ľ��㼯��
static bool get_single_branch(const SLine &sl,const std::vector<Point> &pts,
															const std::vector<SLine> &intersect_lns)
{
	if(pts.size() != 2)
		return false;
	bool flag1 = (sl.pt1 == pts[0]) || (sl.pt1 == pts[1]);
	bool flag2 = (sl.pt2 == pts[0]) || (sl.pt2 == pts[1]);
	bool flag3 = (pts[0] == intersect_lns[0].pt1) || (pts[0] == intersect_lns[0].pt2);
	bool flag4 = (pts[1] == intersect_lns[1].pt1) || (pts[1] == intersect_lns[1].pt2);
	return flag1 && flag2 && flag3 && flag4;
}

////�ж��߶�sl1��sl2�Ƿ��Ƕ˵������ģ�����������Ķ˵�д��pt��������
static bool is_link(const SLine &sl1,const SLine &sl2,Point &pt)
{
	bool flag1 = (sl1.pt1 == sl2.pt1) || (sl1.pt1 == sl2.pt2);
	bool flag2 = (sl1.pt2 == sl2.pt1) || (sl1.pt2 == sl2.pt2);
	if(flag1){
		pt = (sl1.pt1 == sl2.pt1) ? sl2.pt1 : sl2.pt2;
		return true;
	}
	if(flag2){
		pt = (sl1.pt2 == sl2.pt1) ? sl2.pt1 : sl2.pt2;
		return true;
	}
	return false;
}

////�ж������߶ε����ӷ�ʽ���غϷ���-1����������β�����ӷ���0
////�����ߵ���β�����ӷ���1����������-2
static int link_mode(const SLine &sl1,const SLine &sl2,Point &pt)
{
	if(sl1 == sl2)
		return -1;
	bool flag = is_link(sl1,sl2,pt);
	if(is_conline(sl1,sl2))
		return flag ? 0 : -2;
	return flag ? 1 : -2;
}


static Line_Branch get_line_branch(const SLine &sl,int n,
																	 const std::vector<SLine> &sls)
{
	std::vector<Point> pts;
	std::vector<SLine> intersect_lns;
	int i;
	for(i = 0; i < n; i++){
		Point pt;
		int flag = link_mode(sl,sls[i],pt);
		if(flag >= 0){
			intersect_lns.push_back(sls[i]);
			pts.push_back(pt);
		}
	}
	Line_Branch ln_bch;
	ln_bch.sl = sl;
	ln_bch.single_branch = get_single_branch(sl,pts,intersect_lns);
	return ln_bch;
}

////��������scs���ҳ�ֻ�е���֧���ߣ������߶�����aim_sls
static void get_aim_sls(const std::vector<SLine> &scs,std::vector<SLine> &aim_sls)
{
	int i, n = scs.size();
	for(i = 0; i < n; i++){
		Line_Branch ln_bch = get_line_branch(scs[i],n,scs);
		if(ln_bch.single_branch)
			aim_sls.push_back(scs[i]);
	}
}

////����������Ѱ��һ���˵����temp���߶Σ�Ȼ���temp��ֵ��Ϊ���߶ε���һ���˵�
////����߶ε�loop�У�Ȼ���ԭ�����߶������аѸ��߶�ɾ����������
////���Ҳ����������߶��򷵻ؼ�
static bool link_point(std::vector<SLine> &aim_sls,Point &temp,Loop &loop)
{
	int i, n = aim_sls.size();
	for(i = 0; i < n; i++)
		if(temp == aim_sls[i].pt1 || temp == aim_sls[i].pt2){
			if(temp == aim_sls[i].pt1)
				temp = aim_sls[i].pt2;
			else
				temp = aim_sls[i].pt1;
			loop.push_back(aim_sls[i]);
			aim_sls.erase(&aim_sls[i]);
			return true;
		}
	return false;
}

////���߶�������Ѱ��һ��������loop�����ҵ����߶������ǻ��򷵻ؼ�
static bool find_loop(std::vector<SLine> &aim_sls,Loop &loop)
{
	Point temp = aim_sls[0].pt1, start = aim_sls[0].pt2;
	loop.push_back(aim_sls[0]);
	aim_sls.erase(&aim_sls[0]);
	while(temp != start){
		bool flag = link_point(aim_sls,temp,loop);
		if(!flag)
			return false;
	}
	return true;
}

////Ѱ�һ�������
////���߶�����slns���ҳ����еĻ����뻷����lps
bool find_loops(const std::vector<SLine> &slns,Loops &lps)
{
	std::vector<SLine> scs = slns, aim_sls;
	get_aim_sls(scs,aim_sls);
	while(aim_sls.size()){
		Loop loop;
		bool flag = find_loop(aim_sls,loop);
		if(flag)
			lps.push_back(loop);
	}
	return lps.size() > 0;
}
///////////////////////find_loops///////////////////////////

////����һ���ĵ㣬�뾶��ʼĩ�Ƕȵõ�һ����
void arc2d(Arc& arc, const Point& c, Float r, Float srad, Float erad)
{
	Float s = stdradian(srad);
	Float e = stdradian(erad);
	Float num = (s + e) * 0.5;
	Float m = more_than(s,e) ? stdradian(num + pi()) : num;
	arc.start.set(c.x + r * cos(s),c.y + r * sin(s),c.z);
	arc.path.set(c.x + r * cos(m),c.y + r * sin(m),c.z);
	arc.end.set(c.x + r * cos(e),c.y + r * sin(e),c.z);
}

////����һ���ĵ�c�ͻ���һ��p,�Լ��������뻡ʼĩ�������������һ��s��e��û�
void arc2d(Arc& arc, const Point& c, const Point& s, const Point& e, const Point& p)
{
  Float r = distance(c,p);
	arc.start = c + normalize(s - c) * r;
	arc.end = c + normalize(e - c) * r;
	arc.path = p;
	arc.center_ = c;
}

////ƽ�ƻ�ʹ��Բ�ı��c��
void set_arc_center(Arc& arc, const Point& c)
{
	Circle cir;
	resume_circle(arc,cir);
	Arc temp;
	temp.start = c + (arc.start - cir.center);
	temp.path = c + (arc.path - cir.center);
	temp.end = c + (arc.end - cir.center);
	arc = temp;
}

////������ʹ��뾶���r��
void set_arc_radius(Arc& arc, Float r)
{
	Circle c;
	resume_circle(arc,c);
	Arc temp;
	temp.start = c.center + normalize(arc.start - c.center) * r;
	temp.path = c.center + normalize(arc.path - c.center) * r;
	temp.end = c.center + normalize(arc.end - c.center) * r;
	arc = temp;
}

////���center����arc_pt������������x�����������ʱ���
static Float get_rad(const Point &arc_pt,const Point &center)
{
	Point vec = project(arc_pt - center);
	Float rad = angle(vec,ox);
	return less_than(vec.y,0) ? (2 * pi() - rad) : rad;
}

////����ʼ�����ʱ�뻡�ȣ�ʼ�ձ��ֻ�����ʱ��ģ���������ʱ�������յ����ʱ��ǣ�
Float arc2d_srad(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	bool flag = is_ccw2d(arc);
	if(flag)
		return get_rad(arc.start,c.center);
	else
		return get_rad(arc.end,c.center);
}

////���յ����ʱ�뻡�ȣ�ʼ�ձ��ֻ�����ʱ��ģ���������ʱ��������ʼ�����ʱ��ǣ�
Float arc2d_erad(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	bool flag = is_ccw2d(arc);
	if(flag)
		return get_rad(arc.end,c.center);
	else
		return get_rad(arc.start,c.center);
}

////�ж϶�ά�����������Ƿ��쳣�����߻����������غϵȣ����쳣���ؼ�
bool is_arc2d(const Arc& arc)
{
  Point start = project(arc.start);
	Point mid = project(arc.path);
	Point end = project(arc.end);
	return relation(start,mid,end);
}

////�жϿռ仡���������Ƿ��쳣�����߻����������غϵȣ�
bool is_arc(const Arc& arc)
{
  return relation(arc.start,arc.path,arc.end);
}

////�󻡵��е�
Point arc_middle_pt(const Arc& arc)
{
  Circle c;
	resume_circle(arc,c);
	return middle_point(arc,arc.start,arc.end,c);
}

////�󻡵��е�Ļ���
Float arc_middle_rad(const Arc& arc)
{
  Float rad_s = arc2d_srad(arc);
	Float rad_e = arc2d_erad(arc);
	return (rad_e + rad_s) * 0.5;
}

////�ж�һ�����ǲ�����ʱ��˳�򣬲����򷵻ؼ�
bool is_ccw2d(const Arc& arc)
{
	Circle c;
	resume_circle(arc,c);
	Float rad_s = get_rad(arc.start,c.center);
	Float rad_p = get_rad(arc.path,c.center);
	Float rad_e = get_rad(arc.end,c.center);
	bool flag1 = more_than(rad_p,rad_s) && more_than(rad_e,rad_p);
	bool flag2 = more_than(rad_p,rad_s) && more_than(rad_s,rad_e);
	bool flag3 = more_than(rad_e,rad_p) && more_than(rad_s,rad_e);
	return flag1 || flag2 || flag3;
}

///////////////////////get_arc_box///////////////////////////
////�������������᷽���ϵ��������С�㣬������������������
////c�ǻ���Ӧ��Բ
static void get_pts(const Arc& arc,const Circle &c,std::vector<Point> &pts,
										const Point &vec_x,const Point &vec_y,const Point &vec_z)
{
	Point pt;
	if(vec_x != O){
		pt = c.center + vec_x * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_x * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
	if(vec_y != O){
		pt = c.center + vec_y * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_y * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
	if(vec_z != O){
		pt = c.center + vec_z * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
		pt = c.center - vec_z * c.radius;
		if(relation(pt,arc))
			pts.push_back(pt);
	}
}

////�������������᷽���ϵ��������С�㣬������������������
////c�ǻ���Ӧ��Բ
static void get_pts(const Arc& arc,const Circle &c,std::vector<Point> &pts)
{
	pts.push_back(arc.start);
	pts.push_back(arc.end);
	Point normal = make_point(c.nor);
	Point vec_x = normalize((normal * ox) * normal);
	Point vec_y = normalize((normal * oy) * normal);
	Point vec_z = normalize((normal * oz) * normal);
	get_pts(arc,c,pts,vec_x,vec_y,vec_z);
}

////���ݵ�pt�����꣬�ȽϺ����������С������꣬Ȼ�����ú�������
////����������x������С�ڵ�pt��x�����꣬��Ѻ�������x��������Ϊpt��x�����꣬��������
void get_box(const Point &pt,Box &box)
{
	if(more_than(pt.x,box.max_.x))
		box.max_.x = pt.x;
	if(more_than(pt.y,box.max_.y))
		box.max_.y = pt.y;
	if(more_than(pt.z,box.max_.z))
		box.max_.z = pt.z;
	if(less_than(pt.x,box.min_.x))
		box.min_.x = pt.x;
	if(less_than(pt.y,box.min_.y))
		box.min_.y = pt.y;
	if(less_than(pt.z,box.min_.z))
		box.min_.z = pt.z;
}

//���Χ�ռ�Բ���ı�׼�����壬��Բ��ƽ����ĳ�������򳤷����˻�Ϊ������
Box get_arc_box(const Arc& arc)
{
	Circle c;
	resume_circle(arc,c);
	std::vector<Point> pts;
	get_pts(arc,c,pts);
	int i,n = pts.size();
	Box box;
	box.max_ = box.min_ = pts[0];
	for(i = 1; i < n; i++)
		get_box(pts[i],box);
	return box;
}
///////////////////////get_arc_box///////////////////////////


///////////////////////put box///////////////////////////
#define BOX_DIS_LEFT					2.0	//���Ҷ���ʱ��������߿��������Ҽ��
#define BOX_DIS_UP						2.0	//���¶���ʱ��������߿���ϼ����¼��
#define BOX_DIS_EQU_LEFT			2.0	//�Ⱦ����ʱ����֮������ҵȼ��
#define BOX_DIS_EQU_UP				2.0	//�Ⱦ����ʱ����֮������µȼ��

////�����ӱ�׼����ʹ������Ϊ���Ͻǵĵ㣬��С��Ϊ���½ǵĵ�
////�˺���ֻ�����ں���Ŀǰ�������������Ϻ����µ�����
static Rect_Box standard_box_main_catercorner(const Rect_Box &box_s)
{
	Rect_Box box_n;
	if(more_than(box_s.max_.x,box_s.min_.x)){
		box_n.max_.set(box_s.max_.x,box_s.min_.y,box_s.min_.z);
		box_n.min_.set(box_s.min_.x,box_s.max_.y,box_s.max_.z);
	}
	else{
		box_n.max_.set(box_s.min_.x,box_s.max_.y,box_s.max_.z);
		box_n.min_.set(box_s.max_.x,box_s.min_.y,box_s.min_.z);
	}
	return box_n;
}

////�����ӱ�׼����ʹ������Ϊ���Ͻǵĵ㣬��С��Ϊ���½ǵĵ�
static Rect_Box standard_box(const Rect_Box &box_s)
{
	Float slope = (box_s.max_.y - box_s.min_.y) / (box_s.max_.x - box_s.min_.x);
	if(more_than(slope,0)){
		if(more_than(box_s.max_.x,box_s.min_.x))
			return box_s;
		else{
			Rect_Box box_n;
			box_n.max_ = box_s.min_;
			box_n.min_ = box_s.max_;
			return box_n;
		}
	}
	return standard_box_main_catercorner(box_s);
}

typedef void (*ALIGNMENT) (const Rect_Box &base_box,Rect_Box &move_box);
////�ú�����ģ�庯�����Ѻ��������еĺ��Ӱ��յ�һ�����Ӷ���
static void alignment(ALIGNMENT alignment_function,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 2)
		return;
	Rect_Box standardbox = standard_box(boxs[0]);
	for(int i = 1;i < n;i++)
		alignment_function(standardbox,boxs[i]);
}

////����룬�Ѻ��ӵ���������Ƶ�left_xλ�ã����ֺ����������겻�䣬ֻ�ı�xֵ
static void left_alignment(const Float &left_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = standardbox.max_.x - standardbox.min_.x;
	standardbox.min_.x = left_x;
	standardbox.max_.x = standardbox.min_.x + len_x;
	box = standardbox;
}
////�Ե�һ������Ϊ��׼�����ڶ������ӣ�������������ߵ�������ͬ
////���ֺ����������겻�䣬ֻ�ı�xֵ
////��׼���Ӳ��������Ǳ�׼����
void left_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	left_alignment(base_box.min_.x,move_box);
}
////������Ե�һ��Ϊ��׼�����
void left_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(left_alignment,boxs);
}
////����������Ϊ��׼�����
void left_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////�Ҷ���,�Ѻ��ӵ��ұ������Ƶ�right_xλ�ã����ֺ����������겻�䣬ֻ�ı�xֵ
static void right_alignment(const Float &right_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = standardbox.max_.x - standardbox.min_.x;
	standardbox.max_.x = right_x;
	standardbox.min_.x = standardbox.max_.x - len_x;
	box = standardbox;
}
////�Ե�һ������Ϊ��׼�Ҷ���ڶ�������
////���ֺ����������겻�䣬ֻ�ı�xֵ
////��׼���Ӳ��������Ǳ�׼����
void right_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	right_alignment(base_box.max_.x,move_box);
}
////������Ե�һ��Ϊ��׼�Ҷ���
void right_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(right_alignment,boxs);
}
////����������Ϊ��׼�Ҷ���
void right_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////�϶���,�Ѻ��ӵ��ϱ������Ƶ�up_yλ�ã����ֺ����������겻�䣬ֻ�ı�yֵ
static void up_alignment(const Float &up_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = standardbox.max_.y - standardbox.min_.y;
	standardbox.max_.y = up_y;
	standardbox.min_.y = standardbox.max_.y - len_y;
	box = standardbox;
}
////�Ե�һ������Ϊ��׼�϶���ڶ�������
////���ֺ����������겻�䣬ֻ�ı�yֵ
////��׼���Ӳ��������Ǳ�׼����
void up_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	up_alignment(base_box.max_.y,move_box);
}
////������Ե�һ��Ϊ��׼�϶���
void up_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(up_alignment,boxs);
}
////����������Ϊ��׼�϶���
void up_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////�¶���,�Ѻ��ӵ��±������Ƶ�down_yλ�ã����ֺ����������겻�䣬ֻ�ı�yֵ
static void down_alignment(const Float &down_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = standardbox.max_.y - standardbox.min_.y;
	standardbox.min_.y = down_y;
	standardbox.max_.y = standardbox.min_.y + len_y;
	box = standardbox;
}
////�Ե�һ������Ϊ��׼�¶���ڶ�������
////���ֺ����������겻�䣬ֻ�ı�yֵ
////��׼���Ӳ��������Ǳ�׼����
void down_alignment(const Rect_Box &base_box,Rect_Box &move_box)
{
	down_alignment(base_box.min_.y,move_box);
}
////������Ե�һ��Ϊ��׼�¶���
void down_alignment(std::vector<Rect_Box> &boxs)
{
	alignment(down_alignment,boxs);
}
////����������Ϊ��׼�¶���
void down_alignment(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
}

////�����м���룺ʹ���������Ƶ���������������y����
////�Ѻ������ĵ��x�����Ƶ�middle_xλ��
static void middle_alignment_left(const Float &middle_x,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_x = (standardbox.max_.x - standardbox.min_.x) / 2;
	standardbox.max_.x = middle_x + len_x;
	standardbox.min_.x = middle_x - len_x;
	box = standardbox;
}

////�Ѻ������鰴��һ�����������м����
////��ÿ���������ĵ��x���궼�ǵ�һ���������ĵ��x���꣬����y���겻��
void middle_alignment_left(std::vector<Rect_Box> &boxs)
{
	int i,n = boxs.size();
	if(n < 2)
		return ;
	Float mid_x = (boxs[0].max_.x + boxs[0].min_.x) / 2;
	for(i = 1; i < n; i++)
		middle_alignment_left(mid_x,boxs[i]);
}

////�Ѻ������鰴��������м����
////��ÿ���������ĵ��x���궼��������ĵ��x���꣬����y���겻��
void middle_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	Float mid_x = (out_frame.max_.x + out_frame.min_.x) / 2;
	int i,n = boxs.size();
	for(i = 0; i < n; i++)
		middle_alignment_left(mid_x,boxs[i]);
}

////�����м���룺ʹ���������Ƶ���������������x����
////�Ѻ������ĵ��y�����Ƶ�middle_yλ��
static void middle_alignment_up(const Float &middle_y,Rect_Box &box)
{
	Rect_Box standardbox = standard_box(box);
	Float len_y = (standardbox.max_.y - standardbox.min_.y) / 2;
	standardbox.max_.y = middle_y + len_y;
	standardbox.min_.y = middle_y - len_y;
	box = standardbox;
}

////�Ѻ������鰴��һ�����������м����
////��ÿ���������ĵ��y���궼�ǵ�һ���������ĵ��y���꣬����x���겻��
void middle_alignment_up(std::vector<Rect_Box> &boxs)
{
	int i,n = boxs.size();
	if(n < 2)
		return ;
	Float mid_y = (boxs[0].max_.y + boxs[0].min_.y) / 2;
	for(i = 1; i < n; i++)
		middle_alignment_up(mid_y,boxs[i]);
}

////�Ѻ������鰴��������м����
////��ÿ���������ĵ��y���궼��������ĵ��y���꣬����x���겻��
void middle_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	Float mid_y = (out_frame.max_.y + out_frame.min_.y) / 2;
	int i,n = boxs.size();
	for(i = 0; i < n; i++)
		middle_alignment_up(mid_y,boxs[i]);
}

////�Ѻ���������ÿ�����Ӷ���׼����n�Ǻ������鳤��
static void standard_box(std::vector<Rect_Box> &boxs,int n)
{
	int i;
	for(i = 0; i < n; i++){
		Rect_Box temp = standard_box(boxs[i]);
		boxs[i] = temp;
	}
}

////���µȾ����
////��������Σ��������˵ĺ���Ϊ��׼���µȾ��ƶ��м�ĺ���
////����ÿ�����ӵ�x���겻��
void equ_dis_alignment_up(std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 3)
		return;
	standard_box(boxs,n);
	Float len = (boxs[0].min_.y - boxs[n-1].max_.y) / (n - 1);
	for(int i = 1; i < n-1; i++){
		Float middle_line_y = boxs[0].min_.y - i * len;
		Float half_len = (boxs[i].max_.y - boxs[i].min_.y) / 2;
		boxs[i].max_.y = middle_line_y + half_len;
		boxs[i].min_.y = middle_line_y - half_len;
	}
}

////��ÿ����������Ҫ�����µȼ��equ_len_y
////lens��ÿ��������y�����ϵĳ������飬n�Ǻ�������ĳ���
////out_frame��������
static bool get_equal_length_y(const std::vector<Float> &lens,int n,
																const Rect_Box &out_frame,Float &equ_len_y)
{
	Float sum_len = out_frame.max_.y - out_frame.min_.y;
	Float add_len = 0;
	for(int i = 0;i < n; i++)
		add_len += lens[i];
	equ_len_y = (sum_len - add_len) / (n + 1);
	return more_than(equ_len_y,0);
}

////�õ���j�����Ӿ�������ϱߵ��Ƶ�����
static Float get_move_y(const std::vector<Float> &lens,int j,Float equ_len_y)
{
	Float sum_len = 0;
	int i;
	for(i = 0; i < j; i++)
		sum_len += lens[i];
	return sum_len + (j + 1) * equ_len_y;
}

////���ݺ�������������y�����ϵĳ������飬n�Ǻ�������ĳ���
static void get_len_y(const std::vector<Rect_Box> &boxs,
											std::vector<Float> &lens,int n)
{
	int i;
	for(i = 0; i < n; i++)
		lens.push_back(boxs[i].max_.y - boxs[i].min_.y);
}

////��������Σ�����򶥶˺͵׶�Ϊ��׼�Ⱦ��ƶ�����
////��������±�Ҳ�Ⱦ࣬���ؼ�����ֺ��ӳ�����y�������
bool equ_dis_alignment_up(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	standard_box(boxs,n);
	Rect_Box standard_out = standard_box(out_frame);
	std::vector<Float> lens;
	get_len_y(boxs,lens,n);
	Float equ_len_y;
	bool flag = get_equal_length_y(lens,n,standard_out,equ_len_y);
	for(int i = 0; i < n; i++){
		Float len_y = get_move_y(lens,i,equ_len_y);
		boxs[i].max_.y = standard_out.max_.y - len_y;
		boxs[i].min_.y = boxs[i].max_.y - lens[i];
	}
	return flag;
}

////���ҵȾ����
////��������Σ��������˵ĺ���Ϊ��׼���ҵȾ��ƶ��м�ĺ���
////����ÿ�����ӵ�y���겻��
void equ_dis_alignment_left(std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	if(n < 3)
		return;
	standard_box(boxs,n);
	Float len = (boxs[0].min_.x - boxs[n-1].max_.x) / (n - 1);
	for(int i = 1; i < n-1; i++){
		Float middle_line_x = boxs[0].min_.x - i * len;
		Float half_len = (boxs[i].max_.x - boxs[i].min_.x) / 2;
		boxs[i].max_.x = middle_line_x + half_len;
		boxs[i].min_.x = middle_line_x - half_len;
	}
}

////��ÿ����������Ҫ�����µȼ��equ_len_x
////lens��ÿ��������x�����ϵĳ������飬n�Ǻ�������ĳ���
////out_frame��������
static bool get_equal_length_x(const std::vector<Float> &lens,int n,
																const Rect_Box &out_frame,Float &equ_len_x)
{
	Float sum_len = out_frame.max_.x - out_frame.min_.x;
	Float add_len = 0;
	for(int i = 0;i < n; i++)
		add_len += lens[i];
	equ_len_x = (sum_len - add_len) / (n + 1);
	return more_than(equ_len_x,0);
}

////�õ���j�����Ӿ��������ߵ��Ƶ�����
static Float get_move_x(const std::vector<Float> &lens,int j,Float equ_len_x)
{
	Float sum_len = 0;
	int i;
	for(i = 0; i < j; i++)
		sum_len += lens[i];
	return sum_len + (j + 1) * equ_len_x;
}

////���ݺ�������������x�����ϵĳ������飬n�Ǻ�������ĳ���
static void get_len_x(const std::vector<Rect_Box> &boxs,
											std::vector<Float> &lens,int n)
{
	int i;
	for(i = 0; i < n; i++)
		lens.push_back(boxs[i].max_.x - boxs[i].min_.x);
}
////��������Σ��������˺��Ҷ�Ϊ��׼�Ⱦ��ƶ�����
////��������ұ�Ҳ�Ⱦ࣬���ؼ�����ֺ��ӳ�����x�������
bool equ_dis_alignment_left(const Rect_Box &out_frame,std::vector<Rect_Box> &boxs)
{
	int n = boxs.size();
	standard_box(boxs,n);
	Rect_Box standard_out = standard_box(out_frame);
	std::vector<Float> lens;
	get_len_x(boxs,lens,n);
	Float equ_len_x;
	bool flag = get_equal_length_x(lens,n,standard_out,equ_len_x);
	for(int i = 0; i < n; i++){
		Float len_x = get_move_x(lens,i,equ_len_x);
		boxs[i].min_.x = standard_out.min_.x + len_x;
		boxs[i].max_.x = boxs[i].min_.x + lens[i];
	}
	return flag;
}

}
