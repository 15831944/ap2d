// TPlane.h: interface for the TPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_)
#define AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//**********************************************************************
//<Author>:Tian Baijie
//****************************************

#include <vector>
#include <math.h>

#include "export.h"

#include "TPt3D.h"
#include "counter.h"


namespace TIAN_GA_BETTER{

const TPoint gc_ptOrg = TPoint(0,0,0);
const CGeNorm gc_gnOrg = CGeNorm(gc_ptOrg,gc_ptOrg);

enum EOrgPt {TPO_ORGPT1 = 1, TPO_ORGPT2 = 2
};

class GEOAPI TLine////ֱ��
{
public:
	void Set(TPoint pt,CGeNorm normal,double dis = 1);
	void Set(const TPoint& p1,const TPoint& p2);
	void Reverse();
////********************************************************************
////����(��ĳ����Ϊ�ᣬ˳��ʱ����ת)
////********************************************************************
	void PedalUnclockwise(EOrgPt eOrg = TPO_ORGPT1);
	void PedalClockwise(EOrgPt eOrg = TPO_ORGPT1);
////********************************************************************

	TPoint PtCenter()const{return TPoint((pt1.x+pt2.x)/2, (pt1.y+pt2.y)/2, (pt1.z+pt2.z)/2);}

	double Length(){return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2)+pow(pt1.z-pt2.z,2));}

	TLine(const TPoint& p1,const TPoint& p2);
	TLine(TPoint pt,CGeNorm normal,double dis = 1)MCT_INIT1("GA:TLine"){Set(pt,normal,dis);}
	TLine();
	~TLine();

	virtual bool IsPtInLine(const TPoint& pt) const;

	TPoint pt1;

	TPoint pt2;
private:
	MCT_DEF
};
class GEOAPI TRayLine : public TLine////����
{
public:
	TRayLine(const TPoint& p1,const TPoint& p2);
	TRayLine()MCT_INIT1("GA:TRayLine"){pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
	~TRayLine();

	virtual bool IsPtInLine(const TPoint& pt) const;
private:
	MCT_DEF
};
class GEOAPI TSegLine : public TRayLine//�߶�
{
public:
//	TPoint pt1;
//	TPoint pt2;

	TSegLine(const TPoint& p1,const TPoint& p2);
	TSegLine()MCT_INIT1("GA:TSegLine"){pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
	~TSegLine();

	virtual bool IsPtInLine(const TPoint& pt) const;
private:
	MCT_DEF
};

class GEOAPI TArc//��(��λ������)
{
public:
	TArc();
	TArc(TPoint ptCentre, double r, double stArc, double edArc);
	TArc(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd);
	TArc(TPoint pt1, TPoint pt2, TPoint pt3);
	~TArc();
	
	void Set(TPoint ptCentre, double r, double stArc, double edArc);
	void Set(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd);
	void Set(TPoint pt1, TPoint pt2, TPoint pt3);

	TPoint PtSt() const;
	TPoint PtEd() const;

	TLine LineSt()	const;
	TLine LineEd()	const;

	double Length() const;
	double LenPtToCentre(const TPoint& pt) const;

	TPoint  _ptCentre;
	double _r;

	double _stArc;
	double _edArc;

private:
	void Init(TPoint ptSt, TPoint ptEd);
	bool Init(TPoint pt1,TPoint pt2,TPoint pt3);

//�Ƿ�����ʱ��
	bool IsIncrease(double asin1, double asin2, double asin3);

private:
	MCT_DEF
};


typedef  class GEOAPI TPlaneGeometry  
{
public:
	static bool Intersect(const TLine	& ll1,	const TRayLine	&rl ,TPoint& pt);
	static bool Intersect(const TLine	& ll1,	const TLine		&ll2,TPoint& pt);
	static bool Intersect(const TLine	& ll ,	const TSegLine	&sl ,TPoint& pt);
	static bool Intersect(const TSegLine& sl1,	const TSegLine	&sl2,TPoint& pt);
	static bool Intersect(const TSegLine& sl ,	const TRayLine	&rl ,TPoint& pt);
	static bool Intersect(const TRayLine& rl1,	const TRayLine	&rl2,TPoint& pt);
	static TPlaneGeometry& Instance();	~TPlaneGeometry();

////********************************************************************
////���ܣ��󴩹���֪��Ĵ�ֱ��
////ע�⣺���û�и�����֪��(��Ĭ��Ϊ��֪�ߵ�pt1��)
////********************************************************************
	static TLine NormLine(TLine & tl);
	static TLine LinePedal(const TPoint& pt, const TLine& tl);
	static TLine LinePedal(const TLine& tl);
////********************************************************************
////���ܣ����صڼ�����(��1���޺�0������/2)
////********************************************************************
	static int RadianToQuadrant(double dRadian);
////********************************************************************
////���ܣ����صڼ�����(��1���޲���0����/2)
////********************************************************************
	static int RadianToQuadrantRe(double dRadian);
////********************************************************************
////���ܣ����صڼ������ᣨ1==X, 2==Y, 3== -X, 4== -Y, other == 0��
////********************************************************************
	static int RadianToCoordAxis(double dRadian);
////********************************************************************
////���ܣ����һ����(��/����)�Ļ���(��X������������н�)
////ע�⣺����ֵ��1.4�����ڣ���0����/2��3��/2~2��֮�䣨��С������
////********************************************************************
	static double RadianToQuadrant14(double dRadian);
////********************************************************************
////���ܣ����һ����(��/����)�Ļ���(��X������������н�)
////ע�⣺����ֵ��0��2��(����2��)֮��
////********************************************************************
	static double Radian(const TPoint& pt, const TPoint& ptOrg = TPoint(0,0,0));
	static double Radian(const TLine& tl);
	static double Radian(const CGeNorm& norm);
	static double Radian(double dRadian);
////********************************************************************
////���ܣ��жϵ��Ƿ��������γɵ�͹����
////ע�⣺pt2Ϊ�Ƕ���
////********************************************************************
	static bool   IsPtInSalient(const TPoint& pt, 
					const TPoint& pt1, const TPoint& pt2, const TPoint& pt3);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-04-16 to 2007-04-19
////���ܣ������ƽ�����϶�Ӧ�ĵ㡣
////********************************************************************
	static TPoint PtInParallel(const TPoint & ptBase,
									const TLine ll, const TPoint& ptConsult);

////********************************************************************
////���ߣ���۽�
////���ܣ���ô�����֪���ƽ���ߡ�
////********************************************************************
	static TLine LineParallel(const TPoint & ptBase, const TLine& ll);
////********************************************************************
////���ܣ��ع̶��߷����춯�㡣
////********************************************************************
	static bool PtOrtho(TPoint& pt, TLine lnBase, TPoint ptBase);
	static bool PtOrtho(TPoint& pt, TLine lnBase);
//**********************************************************************
//<Add>=Date:2007/07/30
////���ܣ�  ƽ��һ��ֱ�ߡ�
////������	lnResult��Ŀ��ֱ�ߡ�
////		    lnSource��Դֱ�ߡ�
////		    ptWay	��������Ƶ㡣
////		    dis		��ƽ�ƾ��롣
////���أ�	bool	���ɹ�����true��ʧ�ܷ���false��
////		    TLine	������ƽ�ƺ��Ŀ���ߡ�
////ע�⣺  ���������Ƶ���Դֱ���ϣ�
////		    bool	������false��
////		    TLine	������Դֱ�ߡ�
//****************************************
	static TLine LineParallel(const TLine& lnSource,
													const TPoint & ptWay);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
													const TPoint & ptWay);
	static TLine LineParallel(const TLine& lnSource,
										const TPoint & ptWay, double dis);
	static bool LineParallel(TLine& lnResult, const TLine& lnSource,
										const TPoint & ptWay, double dis);
//**********************************************************************
//<Add>=Date:2007/08/02
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
////********************************************************************
////���ܣ����ݵ�ͽǶ����/�ߡ�
////********************************************************************
	static TPoint PtFromAngle(TPoint pt, double angle);
	static TLine LineFromangle(TPoint pt, double angle);
////********************************************************************
////���ڣ�2007-04-20 to 2007-04-20
////���ܣ���õ���ֱ���ϵĴ��㡣
////********************************************************************
	static TPoint PtPedal(const TPoint & ptBase, const TLine& ll);
////********************************************************************
////���ڣ�2007-04-24 to 2007-04-24
////���ܣ���ýǷ��ߡ�
////********************************************************************
	static double MidArc(const TArc & arc);
	static TPoint  MidArcPt(const TArc & arc);
	static TLine  MidArcLine(const TArc & arc);
////********************************************************************
////���ڣ�2007-04-24 to 2007-04-24
////���ܣ���ýǷ��ߵ�������ߡ�
////********************************************************************
	static TLine TangentLine(const TArc & arc);
////********************************************************************
////���ڣ�2007-04-24 to 2007-04-24
////���ܣ��ǶȻ��Ȼ�����
////********************************************************************
	static double Angle2Arc(double angle);
	static double Arc2Angle(double arc);
////********************************************************************
////���ڣ�2007-05-15 to 2007-04-15
////���ܣ��ڸ��������Ͻ�ȡһ�Ρ�
////ע�⣺iWay:��ʾ��ȡ����1����pt1�����ȡ��2����pt2�����ȡ
//********************************************************************
	static TLine LineIntersect(const TLine& tl, double len, EOrgPt eOrg = TPO_ORGPT1);
////********************************************************************
////���ڣ�2007-05-15 to 2007-04-15
////���ܣ���÷����ߡ�
////********************************************************************
	static TLine Reverse(TLine tl){return TLine(tl.pt2, tl.pt1);}
////********************************************************************
////���ڣ�2007-05-20 to 2007-04-20
////���ܣ��㵽�ߵľ��롣
////ע�⣺����true�������߶��ϣ�����false���������ӳ�����
////********************************************************************
	static bool Length(double & len, const TPoint& pt, const TLine& tl);
	static bool Length(double & len, const TPoint& pt, const TRayLine& rl);
	static bool Length(double & len, const TPoint& pt, const TSegLine& sl);

	static double DisPt(const TPoint& pt1, const TPoint& pt2);
	static double DisPtByNormal(TPoint pt1, TPoint pt2, CGeNorm nm);
	static double DisPtToLine(const TPoint& pt, const TLine& ln);
	static double DisPtToLineByNormal(TPoint pt, TLine ln, CGeNorm nm);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-05-20 to 2007-04-20
////���ܣ��жϵ��Ƿ��ڻ���
////********************************************************************
	static bool IsPtInArc(const TPoint& pt, const TArc& arc);
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-03 to 2007-07-03
////���ܣ��жϵ��Ƿ��ڶ������
////********************************************************************
	static bool IsPtInPolygon(const TPoint& pt, 
					const TPoint * pPtPolygon, int nCount);
	static bool IsPtInPolygon(const TPoint& pt, 
					const std::vector<TPoint>& vPtPlolygons);
  template<class PtIt>
	static bool IsPtInPolygon(const TPoint& pt, 
								   PtIt first, PtIt last)
	{
		std::vector<TPoint> vPts;
		PtIt it = first;
		while (it != last)
		{
			vPts.push_back(*it);
			it++;
		}
		return IsPtInPolygon(pt, vPts);
	}

////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-05 to 2007-07-05
////���ܣ��ߴ���������ڣ����������ڡ����߶��顣
////********************************************************************
	static bool LineInPolygon(const TSegLine& sl,const std::vector<TPoint>& vPtsPolygon,
					std::vector<TSegLine>& vSlsInside, std::vector<TSegLine>& vSlsOutside);
	
////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-05 to 2007-07-05
////���ܣ��������ľ�������
////********************************************************************
	static bool SortDisToPt(std::vector<TPoint>& vPts, const TPoint& ptFixed);


////********************************************************************
////���ߣ���۽�
////���ڣ�2007-07-05 to 2007-07-05
////���ܣ����ݱ������м�ֵ
////********************************************************************
	static double ScaleMean(double x1, double x2, double m, double n);
////********************************************************************
////���ڣ�2007-07-10 to 2007-07-10
////���ܣ�ȥ���غϵ�(ͬʱɾ��������)��
////********************************************************************
	static bool DeleteRepeatPt(std::vector<TPoint>& vPts);

//**********************************************************************
//<Add>=Date:2007/07/30
////�ж϶�����Ƿ���͹�����
//****************************************
	static bool IsPolygonConvex(const std::vector<TPoint>& vPtsPolygon);
//**********
//**********************************************************************
////�Ƕȣ����ȣ���normal
//****************************************
	static CGeNorm NormalFromAngle(double angle);
	
	static bool is_line_superpositon(TLine ln1, TLine ln2);
  static bool is_pt_superposition(TPoint pt1, TPoint pt2);

	
//**********
	
	static BOOL IfAoRect(std::vector<TPoint>& pt3dsFront);

////********************************************************************
////���ܣ��жϽ����Ƿ����߶�/������
////ע�⣺����pt��������֪��rl/slֱ���ϵĵ�(�Ѿ��Ǳ���)���ѿ���z����
////		������z������ú���IsPtInLine
////		  ����z������ú���TSolidGeometry::IsPtInLine
////********************************************************************
	static bool IsIntersectInsideLine(const TPoint& pt, const TLine	 & tl);
	static bool IsIntersectInsideLine(const TPoint& pt, const TSegLine& sl);
	static bool IsIntersectInsideLine(const TPoint& pt, const TRayLine& rl);
//////********************************************************************
//////���ܣ��жϵ��Ƿ�������
//////********************************************************************
	static bool IsPtInLine(const TPoint& pt, const TLine	  & tl);
	static bool IsPtInLine(const TPoint& pt, const TSegLine& sl);
	static bool IsPtInLine(const TPoint& pt, const TRayLine& rl);
//////********************************************************************
//////���ܣ��жϵ��Ƿ���ȣ�����z��
//////********************************************************************
	static bool IsPtEqu(const TPoint& pt1, const TPoint& pt2);
//////********************************************************************
//////���ܣ��ж��߶��Ƿ�������ƽ��ֱ��֮��(����z)
//////********************************************************************
	static bool IsSegInsideLine(const TSegLine& sl, 
						const TLine& ln1, const TLine& ln2);





protected:

////********************************************************************
////���ܣ��ж�ƽ���ϵ������߽���
////���أ�true�н���,falseƽ�л����غ�
////�������нӽ���������������(4����)������
////ע�⣺�����ж��䷵��ֵ��ȷ���Ƿ��ܹ��ཻ
////********************************************************************
	static bool intersect_line2line_2d(double& destpt_x, double& destpt_y, 
								double line1st_x, double line1st_y,
								double line1ed_x, double line1ed_y,
								double line2st_x, double line2st_y, 
								double line2ed_x, double line2ed_y	);


private:
	TPlaneGeometry();
private:
	MCT_DEF
} TTool, TGeometry, TGeo;


}
//</Author>
//********** 

#endif // !defined(AFX_TPLANE_H__D69A5040_39AB_4FA9_986F_99AC8F0FD71E__INCLUDED_)
