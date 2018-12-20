// TSolidGeometry.h: interface for the TSolidGeometry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_)
#define AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "export.h"
#include "TPlaneGeometry.h"
#include "counter.h"
#include <vector>

namespace TIAN_GA_BETTER{


class GEOAPI TPlane
{
public:
	TPlane()MCT_INIT1("GA:TPlane"){a=b=c=d=0;}
	TPlane(double ta, double tb, double tc, double td)MCT_INIT1("GA:TPlane"){Set(ta,tb,tc,td);}
	TPlane(CPt3D_Pri pt1, CPt3D_Pri pt2, CPt3D_Pri pt3)MCT_INIT1("GA:TPlane"){Set(pt1,pt2,pt3);}
	~TPlane(){;}

	void Set(double ta, double tb, double tc, double td){a=ta;b=tb;c=tc;d=td;}
	void Set(CPt3D_Pri pt1, CPt3D_Pri pt2, CPt3D_Pri pt3);

	CGeNorm Normal() const;

  //  ��ѧ��ʽ��ax+by+cz+d=0
	double a, b, c, d;
private:
	MCT_DEF
};


class GEOAPI TSolidGeometry  
{
public:

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-06 to 2007-07-06
////���ܣ��㵽ƽ��ľ��롣
////********************************************************************
	static double DisPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-06 to 2007-07-06
////���ܣ�����ƽ��������¡�
////********************************************************************
	static double DxPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
	static double DyPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
	static double DzPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-09 to 2007-07-09
////���ܣ�����㣬�����ʽ�Ҷ�ֵ(�㵽ƽ�����������)��
////********************************************************************
	static double DNarmalPtToPlane(const CPt3D_Pri& pt, const TPlane& pl);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-09 to 2007-07-09
////���ܣ��㵽ƽ��Ĵ��㡣
////********************************************************************
	static CPt3D_Pri PtPedal(const CPt3D_Pri& pt, const TPlane& pl);

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-03 to 2007-07-09
////���ܣ��߶�������
////********************************************************************
	static bool ShowHideLineInPolygon(const TSegLine& sl, const std::vector<CPt3D_Pri>& vPtsPolygon,
					std::vector<TSegLine>& vSlsHide, std::vector<TSegLine>& vSlsShow);
	static bool ShowHideLineInPolygon(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2, 
					const std::vector<CPt3D_Pri>& vPtsPolygon,
					std::vector<CPt3D_Pri>& vPtsHide, std::vector<CPt3D_Pri>& vPtsShow);

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-09 to 2007-07-09
////���ܣ�ֱ����ƽ��Ľ��㡣
////********************************************************************
	static bool Intersect(const TLine& ln, const TPlane& pl, CPt3D_Pri& ptCross);

//**********************************************************************
//<Author>:Tian Baijie
//<Edit>=Date:2007/08/31
////���ܣ�����������߶���ĳ���ֵ(x/y/z)��
//****************************************
	static bool PtScale (CPt3D_Pri& pt, const TLine& ln, double m, double n);
// 	static bool PtScaleX(CPt3D_Pri& pt, const TLine& ln);
// 	static bool PtScaleY(CPt3D_Pri& pt, const TLine& ln);
	static bool PtScaleZ(CPt3D_Pri& pt, const TLine& ln);
//</Edit>
//</Author>
//**********

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-10 to 2007-07-10
////���ܣ�ȥ���غϵ�(ͬʱɾ��������)��������ͬһ��ֱ���ϲ��ҵ�����
////********************************************************************
	static bool DeleteRepeatPt(std::vector<CPt3D_Pri>& vPts);
	static bool DeleteRepeatLn(std::vector<TSegLine>& vSls);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-05 to 2007-07-05
////���ܣ��������ľ�������
////********************************************************************
	static bool SortDisToPt(std::vector<CPt3D_Pri>& vPts, const CPt3D_Pri& ptFixed);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-05 to 2007-07-05
////���ܣ�����ľ���
////********************************************************************
	static double DisPt(const CPt3D_Pri& pt1, const CPt3D_Pri& pt2);

////********************************************************************
////���ܣ��жϵ��Ƿ���������
////********************************************************************
	static bool IsPtInLine(const CPt3D_Pri& pt, const TLine	  & tl);
	static bool IsPtInLine(const CPt3D_Pri& pt, const TSegLine& sl);
	static bool IsPtInLine(const CPt3D_Pri& pt, const TRayLine& rl);

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/07/31
////����ƽ����н�(����/�Ƕ�)
//****************************************
	static double ArcBetweenPlane(const TPlane& pl1, const TPlane& pl2);
	static double AngleBetweenPlane(const TPlane& pl1, const TPlane& pl2);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
	////���ܣ�ƽ��һ��ֱ�ߡ�
	////������	lnResult��Ŀ��ֱ�ߡ�
	////		lnSource��Դֱ�ߡ�
	////		ptWay	��������Ƶ㡣
	////		dis		��ƽ�ƾ��롣
	////���أ�	bool	���ɹ�����true��ʧ�ܷ���false��
	////		TLine	������ƽ�ƺ��Ŀ���ߡ�
	////ע�⣺���������Ƶ���Դֱ���ϣ�
	////		bool	������false��
	////		TLine	������Դֱ�ߡ�
//****************************************
	static TLine LineParallel(const TLine& lnSource,
													const CPt3D_Pri & ptWay);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
													const CPt3D_Pri & ptWay);
	static TLine LineParallel(const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
										const CPt3D_Pri & ptWay, double dis);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////˫���ӳ���
//****************************************
	static bool  LineExtend(TLine& lnResult, 
            							const TLine& lnSource, 
                          double dLen);
	static TLine LineExtend(const TLine& lnSource, 
                          double dLen);
	static bool  LineExtend(TLine& lnResult, 
                          const TLine& lnSource, 
							            double dLenSt, 
                          double dLenEd);
	static TLine LineExtend(const TLine& lnSource, 
							            double dLenSt, 
                          double dLenEd);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/01
////���ܣ��㵽ֱ�ߵľ���
//****************************************
	static double DisPtToLine(const CPt3D_Pri& pt, const TLine& ln);
//</Add>
//</Author>
//**********

//**********************************************************************
//<Author>:Tian Baijie
//<Add>=Date:2007/08/31
////���ܣ���õ���ֱ���ϵĴ��㡣
//****************************************
	static CPt3D_Pri PtPedal(const CPt3D_Pri & ptBase, const TLine& ll);
//</Add>
//</Author>
//**********


protected:
	TSolidGeometry();
	virtual ~TSolidGeometry();
private:
	MCT_DEF
};

}

#endif // !defined(AFX_TSOLIDGEOMETRY_H__16CBEF7D_3797_4B54_9338_47DD0A890CE7__INCLUDED_)
