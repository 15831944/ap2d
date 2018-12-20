
#include "StdAfx.h"
#include "global.h"

#include <algorithm>

#include "Point.h"
#include "isin2d.h"
#include "SLine.h"
#include "Arc.h"
#include "Circle.h"
#include "Point.h"
#include "Plane.h"
#include "calculate.h"
#include "getrace.h"

namespace geo{
 
//globle functions define
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-03
////���ܣ��жϵ��Ƿ��ڶ������
////********************************************************************
//bool in(const Point& pt, const Point * polygon, int count)
//{
//	if(count < 2) return false;
//	int nCross = 0; 
//	for (int i = 0; i < count; i++) 
//	{ 
//		Point p1 = polygon[i]; 
//		Point p2 = polygon[(i+1) % count]; 
//		//// ��� y=p.y �� p1p2 �Ľ��� 
//		if( p1.y == p2.y ) //// p1p2 �� y=p0.yƽ�� 
//    {			
//      continue;
//    }
//		if ( pt.y < min(p1.y, p2.y) ) //// ������p1p2�ӳ����� 
//    {	
//      continue;
//    }
//		if ( pt.y >= max(p1.y, p2.y) ) //// ������p1p2�ӳ����� 
//    {
//      continue; 
//    }
//		//// �󽻵�� X ���� 
//		Float x =	(pt.y-p1.y) * (p2.x-p1.x) / (p2.y-p1.y) + (p1.x); 
//		if( x > pt.x ) 
//    {
//      nCross++; //// ֻͳ�Ƶ��߽��� 
//    }
//	} 
//	//// ���߽���Ϊż�������ڶ����֮�� --- 
//	return (bool)(nCross % 2 == 1); 
//}
//bool in(const Point& pt, const std::vector<Point>& polygon)
//{
//  if(polygon.empty()){
//    return false;
//  }
//  return in(pt, &polygon[0], polygon.size());
//}

bool isin(const Point& pt, const Point * polygon, int count)
{
  if(count < 2) return false;
  int nCross = 0; 
  for (int i = 0; i < count; i++) 
  { 
    Point p1 = polygon[i]; 
    Point p2 = polygon[(i+1) % count]; 
    //// ��� y=p.y �� p1p2 �Ľ��� 
    //if( p1.y == p2.y )                    //// p1p2 �� y=p0.yƽ�� 
    if(equ(p1.y, p2.y))                     //// p1p2 �� y=p0.yƽ�� 
    {			
      continue;
    }
    //if ( pt.y < std::min(p1.y, p2.y) )         //// ������p1p2�ӳ����� 
    if(less_than(pt.y, min(p1.y, p2.y)))         //// ������p1p2�ӳ����� 
    {	
      continue;
    }
    if(more_equ(pt.y, max(p1.y, p2.y)))     //// ������p1p2�ӳ����� 
    {
      continue; 
    }
    //// �󽻵�� X ���� 
    Float x =	(pt.y-p1.y) * (p2.x-p1.x) / (p2.y-p1.y) + (p1.x); 
    //if( x > pt.x ) 
    if(more_than(x, pt.x))
    {
      nCross++; //// ֻͳ�Ƶ��߽��� 
    }
  } 
  //// ���߽���Ϊż�������ڶ����֮�� --- 
  return (bool)(nCross % 2 == 1); 
}

bool isin(const Point& pt, const std::vector<Point>& polygon)
{
	TRACE_OUT("isin :start!\n"); 
  if(polygon.empty()){
    return false;
  }
	////����ǡ���ڱ����ϣ���ֱ���϶����ڶ�����ڡ�
	int nSizePolygon = polygon.size();
	TRACE_OUT("nSizePolygon = %d!\n",nSizePolygon); 
	SLine slBorder;
	for (int i=0; i< nSizePolygon; i++)
	{
		slBorder.set(polygon[i], polygon[(i+1)%nSizePolygon]);
		TRACE_OUT("current = %d!\n",i); 
		if(isin2d(pt,slBorder)) {
			return true;
		}
	}
	////�жϵ��Ƿ��ڶ������
	TRACE_OUT("4446777!\n",i); 
  bool v =  isin(pt, &polygon[0], polygon.size());
	TRACE_OUT("isin :ok!\n"); 

	return v;
}

int compare(const Point& the, const Plane& datum)
{
  if(equ(datum.c,0))
    return -2;
  else{
    Float dis = distance(the,datum);
    if(equ(dis,0))
      return 0;
    else{
      Float zh = (the.x * datum.a + the.y * datum.b + datum.d) / (-datum.c);
      return (more_than(zh,the.z)) ? -1 : 1;
    }
  }
}


static Point arc_point(const Point& c, Float r, Float radian)
{
	Point vec(cos(radian),sin(radian),0);
	Point normalize_vec = normalize(vec);
	return c + normalize_vec * r;
}
Arc get_arc(const Point& c, Float r, Float sdegree, Float edegree)
////ͨ��Բ��.�뾶.��ʼ�Ƕ�.��ֹ�Ƕȵõ���
{
	Float sradian = stdradian(convert_degree(sdegree));
	Float eradian = stdradian(convert_degree(edegree));
	Float radian = (sradian + eradian) / 2;
	Float mradian  = (more_equ(sradian,eradian)) ? (radian + geo::pi()) : radian;
	Point spoint = arc_point(c,r,sradian);
	Point epoint = arc_point(c,r,eradian);
	Point mpoint = arc_point(c,r,mradian);
	Arc arc(spoint,mpoint,epoint);
	return arc;
}


static void evaluate(const bool& flag,const Float& degree1,
							const Float& degree2,Float& sdegree, Float& edegree)
{
	if(flag){
			sdegree = degree1;
			edegree = degree2;
		}
		else{
			sdegree = degree2;
			edegree = degree1;
		}
}
bool get_arc(const Arc& arc, Point& c, Float& r, Float& sdegree, Float& edegree)
////ͨ�����õ�Բ��.�뾶.��ʼ�Ƕ�.��ֹ�Ƕ�
{
	if(!(equ(arc.start.z,arc.end.z) && equ(arc.start.z,arc.path.z)
		&& equ(arc.end.z,arc.path.z)))
		return false;
	Circle circle;
	resume_circle(arc,circle);
	c = circle.center;
	r = circle.radius;
	Float degree1 = convert_radian(get_angle2d(arc.start,c));
	Float degree2 = convert_radian(get_angle2d(arc.end,c));
	Arc arc_temp = get_arc(c,r,degree1,degree2);
	bool flag = relation(arc.path,arc_temp);
	evaluate(flag,degree1,degree2,sdegree,edegree);
	return true;
}



}//namespace
