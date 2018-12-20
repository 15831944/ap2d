
#ifndef _GEOMETRY_ARC_H_
#define _GEOMETRY_ARC_H_

#include <vector>
#include "export.h"
#include "Point.h"
#include "Normal.h"
#include "counter.h"

namespace geo{

class LLine;
class RLine;
class SLine;
class Circle;
class Box;
  
class GEOAPI Arc
{
public:
  Point center_;//��ʱ���������3��ȷ�����ߣ���3�㲻��ȷ������ʱ��center������;
  Point start;
  Point path;
  Point end;

public:
	Arc(const Point& s=ORG, const Point& p=ORG, const Point& e=ORG);
	void set(const Point& s=ORG, const Point& p=ORG, const Point& e=ORG);
  void set(const Point& c, const Point& s, const Point& e, const Point& p);
  void set_radian2d(const Point& c, Float r, Float srad, Float erad);
  void set_degree2d(const Point& c, Float r, Float sdeg, Float edeg);

public:
  void center(const Point& c);
  void radius(Float r);

public:
  Point middle()const;
  Point center()const;
  Float radius()const;
  
public:
  Float radian()const;  ////�ſ��Ƕ�
  Float degree()const;  ////�ſ��Ƕ�

public:
  Float start_radian2d()const;
  Float start_degree2d()const;
  Float end_radian2d()const;
  Float end_degree2d()const;

public:
  Float middle_radian2d()const;
  Float middle_degree2d()const;

public:
  Point middle2d()const;
  Point start2d()const;
  Point path2d()const;
  Point end2d()const;
  

public:
  Box box()const;

public:
  void intersect2d(const LLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const RLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const SLine & rhs, std::vector<Point>& pts) const;
  void intersect2d(const Circle& rhs, std::vector<Point>& pts) const;
  void intersect2d(const Arc   & rhs, std::vector<Point>& pts) const;

private:
  bool is_ccw2d()const;


private:
	MCT_DEF
};
  
}
#endif

