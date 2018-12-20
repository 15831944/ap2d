		// TPlaneGeometry.cpp: implementation of the TPlane class.
		//
		//////////////////////////////////////////////////////////////////////

		//**********************************************************************
		//<Author>:Tian Baijie
		//****************************************


		#include "stdafx.h"
		#include "TPlaneGeometry.h"
		#include "TGlobal.h"

		#include <assert.h>

		#ifdef _DEBUG
		#undef THIS_FILE
		static char THIS_FILE[]=__FILE__;
		#define new DEBUG_NEW
		#endif

		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////

		namespace TIAN_GA_BETTER{


		using namespace std;


		/***********************************************************************
								TLine
		***********************************************************************/

		TLine::TLine(const TPoint& p1,const TPoint& p2)
		:pt1(p1)
		,pt2(p2)
		MCT_INIT2("GA:TLine")
		{}
		TLine::TLine()
		MCT_INIT1("GA:TLine")
		{pt1=TPoint(0,0,0);pt2=TPoint(1,1,1);}
		TLine::~TLine()
		{}
		TRayLine::TRayLine(const TPoint& p1,const TPoint& p2)
		:TLine(p1,p2)
		MCT_INIT2("GA:TRayLine")//pt1(p1),pt2(p2)
		{}
		TRayLine::~TRayLine()
		{}
		TSegLine::TSegLine(const TPoint& p1,const TPoint& p2)
		:TRayLine(p1,p2)
		MCT_INIT2("GA:TSegLine")//pt1(p1),pt2(p2)
		{}
		TSegLine::~TSegLine()
		{}	

		void TLine::Set(TPoint pt, CGeNorm normal, double dis)
		{
			normal.normalize();
			pt1 = pt;
			pt2 = pt.PolarTo(dis, &normal);
		}
		void TLine::Set(const TPoint& p1,const TPoint& p2)
		{
			pt1 = p1;
			pt2 = p2;
		}
		void TLine::Reverse()
		{
			TPoint pt;
			pt  = pt1;
			pt1 = pt2;
			pt2 = pt;
		}
		void TLine::PedalUnclockwise(EOrgPt eOrg)
		{
			if (eOrg != TPO_ORGPT1 && eOrg != TPO_ORGPT2)	
				return;
			if (eOrg == TPO_ORGPT2)	
				Reverse();

			pt2 = pt2 - pt1;
			pt2.RotateZ(90.0);
			pt2 = pt2 + pt1;

			if (eOrg == TPO_ORGPT2)					
				Reverse();
		}
		void TLine::PedalClockwise(EOrgPt eOrg)
		{
			if (eOrg != TPO_ORGPT1 && eOrg != TPO_ORGPT2)	return;
			if (eOrg == TPO_ORGPT2)	Reverse();

			pt2 = pt2 - pt1;
			pt2.RotateZ(270.0);
			pt2 = pt2 + pt1;

			if (eOrg == TPO_ORGPT2)					Reverse();
		}

		bool TLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn1(pt1, pt2);
			nmLn1.normalize();
			CGeNorm nmLn2(pt2, pt1);
			nmLn2.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn1 || nmPt == nmLn2 ? true : false;
		}
		bool TRayLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn(pt1, pt2);
			nmLn.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn ? true : false;
		}

		bool TSegLine::IsPtInLine(const TPoint& pt) const
		{
			CGeNorm nmLn1(pt1, pt2);
			nmLn1.normalize();
			CGeNorm nmLn2(pt2, pt1);
			nmLn2.normalize();
			CGeNorm nmPt(pt1, pt );
			nmPt.normalize();
			return nmPt == nmLn1 && nmPt == nmLn2 ? true : false;
		}


		/************************************************************************/
		/*                   TArc                                               */
		/************************************************************************/
		TArc::TArc()
		:_ptCentre(gc_ptOrg)
		,_r(0)
		,_stArc(0)
		,_edArc(0)
		MCT_INIT2("GA:TArc")
		{
		}
		TArc::TArc(TPoint ptCentre, double r, double stArc, double edArc)
		:_ptCentre(ptCentre)
		,_r(r)
		,_stArc(stArc)
		,_edArc(edArc)
		MCT_INIT2("GA:TArc")
		{
		}
		TArc::TArc(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd)
		:_ptCentre(ptCentre)
		,_r(r)
		MCT_INIT2("GA:TArc")
		{
			Init(ptSt,ptEd);
		}
		TArc::TArc(TPoint pt1, TPoint pt2, TPoint pt3)
		MCT_INIT1("GA:TArc")
		{
			Init(pt1,pt2,pt3);
		}

		TArc::~TArc()
		{}

		void TArc::Set(TPoint ptCentre, double r, double stArc, double edArc)
		{
			_ptCentre = ptCentre;
			_r				= r;
			_stArc		= stArc;
			_edArc		= edArc;
		}

		void TArc::Set(TPoint ptCentre, double r, TPoint ptSt, TPoint ptEd)
		{
			_ptCentre = ptCentre;
			_r				= r;
			Init(ptSt, ptEd);
		}

		void TArc::Set(TPoint pt1, TPoint pt2, TPoint pt3)
		{
			Init(pt1,pt2,pt3);
		}

		TPoint TArc::PtSt() const
		{
			TPoint ptSt;
			ptSt.x = _ptCentre.x + _r*cos(_stArc);
			ptSt.y = _ptCentre.y + _r*sin(_stArc);
			ptSt.z = 0;
			return ptSt;
		}
		TPoint TArc::PtEd() const
		{
			TPoint ptEd;
			ptEd.x = _ptCentre.x + _r*cos(_edArc);
			ptEd.y = _ptCentre.y + _r*sin(_edArc);
			ptEd.z = 0;
			return ptEd;
		}
		TLine TArc::LineSt() const
		{
			return TLine(_ptCentre, PtSt());
		}
		TLine TArc::LineEd() const
		{
			return TLine(_ptCentre, PtEd());
		}


		void TArc::Init(TPoint ptSt, TPoint ptEd)
		{
		//	CGeNorm gnSt(_ptCentre, ptSt);	////��ʼ���Բ�ĵĲ�ֵ
		//	CGeNorm gnEd(_ptCentre, ptEd);	////��ֹ���Բ�ĵĲ�ֵ
			_stArc = TPlaneGeometry::Radian(ptSt, _ptCentre);
			_edArc = TPlaneGeometry::Radian(ptEd, _ptCentre);
		}
		////��ô����������Բ��Բ�ĺͰ뾶
		////��������ֱ�߷���ֵ��FALSE
		bool TArc::Init(TPoint pt1,TPoint pt2,TPoint pt3)
		{
			double x1=pt1.x, x2=pt2.x, x3=pt3.x;
			double y1=pt1.y, y2=pt2.y, y3=pt3.y;

			if((x1==x2)&&(x2==x3))
			{
				return false;
			}
			if((x1!=x2)&&(x2!=x3))
			{
				double k1 = (y2-y1)/(x2-x1);
				double k2 = (y2-y3)/(x2-x3);
				if(k1==k2)
				{
					return false;
				}
			}
			
			double a=2*(x2-x1);
			double b=2*(y2-y1);
			double c=x2*x2+y2*y2-x1*x1-y1*y1;
			double d=2*(x3-x2);
			double e=2*(y3-y2);
			double f=x3*x3+y3*y3-x2*x2-y2*y2;
			double x=(b*f-e*c)/(b*d-e*a);
			double y=(d*c-a*f)/(b*d-e*a);
			double r=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));

			_ptCentre.x = x;
			_ptCentre.y = y;
			_ptCentre.z = 0;
			_r = r;

			double asin1 = TPlaneGeometry::Radian(pt1, _ptCentre);
			double asin2 = TPlaneGeometry::Radian(pt2, _ptCentre);
			double asin3 = TPlaneGeometry::Radian(pt3, _ptCentre);
			bool bIncrease = IsIncrease(asin1,asin2,asin3);////���3��ķ���(�Ƿ���ʱ��)

			if (bIncrease)
			{
				Init(pt1,pt3);
			}
			else
			{
				Init(pt3,pt1);
			}


			return false;
		}
		bool TArc::IsIncrease(double asin1, double asin2, double asin3)
		{
			if(asin1<asin3)
			{
				if(asin1<asin2 && asin2<asin3)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				if(asin1>asin2 && asin2>asin3)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		}

		double TArc::Length() const
		{
			return _r*(TPlaneGeometry::Radian(_edArc-_stArc));
		}
		double TArc::LenPtToCentre(const TPoint& pt) const
		{
			return sqrt(pow(_ptCentre.x-pt.x,2)+pow(_ptCentre.y-pt.y,2));
		}


		/***********************************************************************
								TPlaneGeometry
		***********************************************************************/
		//////////////////////////////////////////////////////////
		TPlaneGeometry::TPlaneGeometry()
		MCT_INIT1("GA:TPlaneGeometry")
		{

		}

		TPlaneGeometry::~TPlaneGeometry()
		{

		}
		TPlaneGeometry& TPlaneGeometry::Instance()
		{
			static TPlaneGeometry tool;
			return tool;
		}

		////ֱ�ߺ��߶�
		bool TPlaneGeometry::Intersect(const TLine &ll, const TSegLine& sl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll.pt1.x,ll.pt1.y,ll.pt2.x,ll.pt2.y,
										sl.pt1.x,sl.pt1.y,sl.pt2.x,sl.pt2.y
										);

			if (bResult && IsIntersectInsideLine(pt, sl))	
			{
				return true;
			}

			return false;
		}


		////����ֱ��
		bool TPlaneGeometry::Intersect(const TLine &ll1, const TLine &ll2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll1.pt1.x, ll1.pt1.y,ll1.pt2.x,ll1.pt2.y,
										ll2.pt1.x, ll2.pt1.y,ll2.pt2.x,ll2.pt2.y
										);
			if (bResult)	////�����ӳ��ཻ������ֱ��
			{
				return true;
			}

			return false;
		}

		////ֱ�ߺ�����
		bool TPlaneGeometry::Intersect(const TLine &ll1, const TRayLine &rl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										ll1.pt1.x, ll1.pt1.y,ll1.pt2.x,ll1.pt2.y,
										rl.pt1.x,  rl.pt1.y, rl.pt2.x, rl.pt2.y
										);

			if (bResult && IsIntersectInsideLine(pt, rl))	
			{
				return true;
			}

			return false;
		}

		////�����߶�(�ݲ�����z����)
		bool TPlaneGeometry::Intersect(const TSegLine &sl1, const TSegLine &sl2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										sl1.pt1.x, sl1.pt1.y,sl1.pt2.x,sl1.pt2.y,
										sl2.pt1.x, sl2.pt1.y,sl2.pt2.x,sl2.pt2.y
										);
			if (bResult							&& 
				IsIntersectInsideLine(pt, sl1)	&& 
				IsIntersectInsideLine(pt, sl2)	)	////ֱ���ཻ�������߶�
			{
				return true;
			}

			return false;
		}

		////�߶κ�����
		bool TPlaneGeometry::Intersect(const TSegLine &sl, const TRayLine &rl,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										sl.pt1.x, sl.pt1.y, sl.pt2.x, sl.pt2.y,
										rl.pt1.x, rl.pt1.y, rl.pt2.x, rl.pt2.y
										);

			if (bResult							&& 
				IsIntersectInsideLine(pt, rl)	&&
				IsIntersectInsideLine(pt, sl)	)	
			{
				return true;
			}

			return false;
		}

		////��������
		bool TPlaneGeometry::Intersect(const TRayLine &rl1, const TRayLine &rl2,TPoint& pt)
		{
			bool bResult = intersect_line2line_2d(pt.x, pt.y,
										rl1.pt1.x, rl1.pt1.y, rl1.pt2.x, rl1.pt2.y,
										rl2.pt1.x, rl2.pt1.y, rl2.pt2.x, rl2.pt2.y
										);

			if(bResult && IsIntersectInsideLine(pt, rl1) && IsIntersectInsideLine(pt, rl2)	)	
			{
				return true;
			}

			return false;
		}




		////********************************************************************
		////���ܣ��ж�ƽ���ϵ������߽���
		////���أ�true�н���,falseƽ�л����غ�
		////�������нӽ���������������(4����)������
		////ע�⣺�����ж��䷵��ֵ��ȷ���Ƿ��ܹ��ཻ
		////********************************************************************
		bool TPlaneGeometry::intersect_line2line_2d(double& destpt_x, double& destpt_y, 
											  double line1st_x, double line1st_y,
											  double line1ed_x, double line1ed_y,
											  double line2st_x, double line2st_y, 
											  double line2ed_x, double line2ed_y)
		{
			double a=0,b=0,c=0,d=0,e=0;
			double P1[2],P2[2],P3[2],P4[2],P[2];
			P1[0] = line1st_x,P1[1] = line1st_y;
			P2[0] = line1ed_x,P2[1] = line1ed_y;
			P3[0] = line2st_x,P3[1] = line2st_y;
			P4[0] = line2ed_x,P4[1] = line2ed_y;
			a = P2[0] - P1[0];       ////�߶�p1p2��x�����
			b = P4[0] - P3[0];       ////�߶�p3p4��x�����
			c = P2[1] - P1[1];       ////�߶�p1p2��y�����
			d = P4[1] - P3[1];       ////�߶�p3p4��y�����
			e = a*d - b*c;
			if (fabs(e) < FLOAT_PRECISION)    
				return false;    ////���߶�ƽ�л����غ�
			P[1] = (c*d*(P3[0] - P1[0]) + a*d*P1[1] - b*c*P3[1])/e;
			if (fabs(c)<FLOAT_PRECISION) 
				P[0] = P3[0] + b*(P[1]-P3[1])/d;
			else 
				P[0] = P1[0] + a*(P[1]- P1[1])/c;

			double temp1 = (P[0]-P1[0])*(P[0]-P2[0]);
			double temp2 = (P[0]-P3[0])*(P[0]-P4[0]);
				
			destpt_x = P[0];
			destpt_y = P[1];

			return true;
		}

		////********************************************************************
		////���ܣ��жϽ����Ƿ���ֱ����
		////ע�⣺����pt��������֪��slֱ���ϵĵ�(�Ѿ��Ǳ���)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint& pt, const TLine	 & tl)
		{
			TRayLine r1(tl.pt1,tl.pt2), r2(tl.pt2,tl.pt1);
			if (IsIntersectInsideLine(pt,r1) || IsIntersectInsideLine(pt,r2))
			{
				return true;
			}
			return false;
		}

		////********************************************************************
		////���ܣ��жϽ����Ƿ���������
		////ע�⣺����pt��������֪��rlֱ���ϵĵ�(�Ѿ��Ǳ���)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint& pt, const TRayLine& rl)
		{
			CGeNorm normRayLine(rl.pt1, rl.pt2);
			normRayLine.m_z;
			normRayLine.normalize();
			CGeNorm normToPt(rl.pt1, pt);
			normRayLine.m_z;
			normToPt.normalize();

			if (normRayLine == normToPt)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		////********************************************************************
		////���ܣ��жϽ����Ƿ����߶���
		////ע�⣺����pt��������֪��slֱ���ϵĵ�(�Ѿ��Ǳ���)
		////********************************************************************
		bool TPlaneGeometry::IsIntersectInsideLine(const TPoint &pt, const TSegLine &sl)
		{
			CGeNorm normSegLine(sl.pt1, sl.pt2);
			CGeNorm normToPt(sl.pt1, pt);
			if (normToPt.len() > normSegLine.len())
			{
				return false;
			}
			normSegLine.normalize();
			normToPt.normalize();
			if (normSegLine == normToPt)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		////********************************************************************
		////���ܣ���ɴ�ֱ��
		////ע�⣺��pt1Ϊ���ģ���ת90��
		////********************************************************************
		TLine TPlaneGeometry::NormLine(TLine &ll) 
		{
			ll.pt2 = ll.pt2 - ll.pt1;
			ll.pt2.RotateZ(90.0);
			ll.pt2 = ll.pt2 + ll.pt1;
			return ll;
		}
		TLine TPlaneGeometry::LinePedal(const TPoint& pt, const TLine& tl)
		{
			if (pt == tl.pt1)
			{
				return LinePedal(tl);
			}
			if(pt == tl.pt2)
			{
				return LinePedal(TLine(tl.pt2,tl.pt1));
			}
			TPoint ptPedal = PtPedal(pt, tl);
			TPoint ptInLine= ptPedal + (tl.pt2 - tl.pt1);
			TLine tLine(ptPedal, ptInLine);
			NormLine(tLine);
			return tLine;
		}
		TLine TPlaneGeometry::LinePedal(const TLine& tl)
		{
			TLine result = tl;
			NormLine(result);
			return result;
		}

		////********************************************************************
		////���ܣ����صڼ������ᣨ1==X, 2==Y, 3== -X, 4== -Y, other == 0��
		////********************************************************************
		int TPlaneGeometry::RadianToCoordAxis(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TEquFloat(dRadian,0))
			{
				return 1;
			}
			if( TEquFloat(dRadian,PI_R/2))
			{
				return 2;
			}
			if( TEquFloat(dRadian,PI_R))
			{
				return 3;
			}
			if( TEquFloat(dRadian,PI_R*3/2))
			{
				return 4;
			}
			return 0;
		}

		////********************************************************************
		////���ܣ����صڼ�����
		////********************************************************************
		int TPlaneGeometry::RadianToQuadrant(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TMoreEqu(dRadian,0) &&
				TLessThen(dRadian,PI_R/2))
			{
				return 1;
			}
			if( TMoreEqu(dRadian,PI_R/2) &&
				TLessThen (dRadian,PI_R))
			{
				return 2;
			}
			if( TMoreEqu(dRadian,PI_R) &&
				TLessThen (dRadian,PI_R*3/2))
			{
				return 3;
			}
			if( TMoreEqu(dRadian,PI_R*3/2) &&
				TLessThen (dRadian,PI_R*2))
			{
				return 4;
			}
			return 0;
		}
		////********************************************************************
		////���ܣ����صڼ�����(��1���޲���0����/2)
		////********************************************************************
		int TPlaneGeometry::RadianToQuadrantRe(double dRadian)
		{
			dRadian = Radian(dRadian);
			if( TMoreThen(dRadian,0) &&
				TLessEqu(dRadian,PI_R/2))
			{
				return 1;
			}
			if( TMoreThen(dRadian,PI_R/2) &&
				TLessEqu(dRadian,PI_R))
			{
				return 2;
			}
			if( TMoreThen(dRadian,PI_R) &&
				TLessEqu(dRadian,PI_R*3/2))
			{
				return 3;
			}
			if( TMoreThen(dRadian,PI_R*3/2) &&
				TLessEqu(dRadian,PI_R*2)	||
				TEquFloat(dRadian, 0))
			{
				return 4;
			}
			return 0;
		}
		////********************************************************************
		////���ܣ����һ����Ļ���(��X������������н�)
		////ע�⣺����ֵ��0��2��(����2��)֮��
		////********************************************************************
		double TPlaneGeometry::RadianToQuadrant14(double dRadian)
		{
			//ȷ��������0~2��֮��
			dRadian = Radian(dRadian);
			if( TMoreThen(dRadian,PI_R/2) &&
				TLessEqu (dRadian,PI_R*3/2))
			{
				dRadian += PI_R;
			}
			dRadian = Radian(dRadian);
			return dRadian;
		}
		////********************************************************************
		////���ܣ����һ����Ļ���(��X������������н�)
		////ע�⣺����ֵ��0��2��(����2��)֮��
		////********************************************************************
		double TPlaneGeometry::Radian(const TPoint& pt, const TPoint& ptOrg)
		{
			if(pt == ptOrg)
			{
				return 0;
			}
			TPoint ptTe = pt;
			ptTe.z = 0;
			CGeNorm normPt(ptOrg, ptTe);
			return Radian(normPt);
		}
		double TPlaneGeometry::Radian(const TLine& tl)
		{
			return Radian(tl.pt2, tl.pt1);
		}
		double TPlaneGeometry::Radian(const CGeNorm& norm)
		{
			CGeNorm normTe = norm;
			normTe.m_z = 0;
			if (normTe == CGeNorm(0,0,0)) {
				return 0;
			}
			CGeNorm normX(TPoint(0,0,0),TPoint(1,0,0));
			double dRadian = normTe.Angle2Norm(normX);
			return normTe.m_y >=0 ? dRadian : 2*PI_R-dRadian;
		}
		double TPlaneGeometry::Radian(double dRadian)
		{
			while (dRadian<0)
			{
				dRadian += 2*PI_R;
			}
			while (dRadian>=2*PI_R)
			{
				dRadian -= 2*PI_R;
			}
			return dRadian;
		}

		////********************************************************************
		////���ܣ��жϵ��Ƿ��������γɵ�͹����
		////ע�⣺pt2Ϊ�Ƕ���
		////********************************************************************
		bool TPlaneGeometry::IsPtInSalient(const TPoint& pt, 
							const TPoint& pt1, const TPoint& pt2, const TPoint& pt3)
		{
			CGeNorm normpt1(pt2,pt1);
			CGeNorm normpt3(pt2,pt3);
			CGeNorm normpt (pt2,pt);

			double dRadian1 = Radian(normpt1);
			double dRadian3 = Radian(normpt3);
			double dRadianpt= Radian(normpt);

			double dRadianMax = max(dRadian1, dRadian3);
			double dRadianMin = min(dRadian1, dRadian3);

			if ((dRadianMax - dRadianMin) > PI_R)
			{
				dRadianMin += 2*PI_R;
				if (dRadianpt < PI_R)
				{
					dRadianpt += 2*PI_R;
				}
			}
			if (dRadianMin < dRadianpt && dRadianpt < dRadianMax)
			{
				return true;
			}
			return false;
		}


		////********************************************************************
		////���ߣ���۽�
		////���ܣ������ƽ�����϶�Ӧ�ĵ㡣
		////������ptInput���յ�(�ڻ�����)��ll���ߣ�ptConsult���յ�(��ƽ������)
		////ע�⣺�ɻ��ߵ�ptInput���ƽ���ߵ㺯������ֵ
		////********************************************************************
		TPoint TPlaneGeometry::PtInParallel(const TPoint & ptBase,
										const TLine ll, const TPoint& ptConsult)
		{
			TLine llParallel	= LineParallel(ptConsult,ll);	////�õ�ƽ����

			return PtPedal(ptBase, llParallel);
		}
		////********************************************************************
		////���ߣ���۽�
		////���ܣ���ô�����֪���ƽ���ߡ�
		////********************************************************************
		TLine TPlaneGeometry::LineParallel(const TPoint & ptBase, const TLine& ll)
		{
			TLine llResult(TPoint(ptBase), (ptBase+(ll.pt2-ll.pt1)));
			return llResult;
		}
		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/07/30
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
		bool TPlaneGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
												const TPoint & ptWay, double dis)
		{
			////���������Ƶ���Դֱ���ϣ����޷����Ʒ���
			TPoint ptWayCopy = ptWay;
			ptWayCopy.z = 0;
			if(IsPtInLine(ptWayCopy, lnSource))			
			{
				return false;
			}
			TPoint ptPedal = PtPedal(ptWayCopy, lnSource);
			ptPedal.z = 0;
			CGeNorm nmPedal(ptPedal, ptWayCopy);
			nmPedal.normalize();
			TPoint ptS1 = lnSource.pt1;
			TPoint ptD1 = ptS1.PolarTo(dis, &nmPedal);
			TPoint ptS2 = lnSource.pt2;
			TPoint ptD2 = ptS2.PolarTo(dis, &nmPedal);
			lnResult.Set(ptD1, ptD2);
			return true;
		}
		TLine TPlaneGeometry::LineParallel(const TLine& lnSource,
												const TPoint & ptWay, double dis)
		{
			TLine lnResult;
			if(!LineParallel(lnResult, lnSource, ptWay, dis))
			{
				lnResult = lnSource;
			}
			return lnResult;
		}
		bool TPlaneGeometry::LineParallel(TLine& lnResult, const TLine& lnSource,
															 const TPoint & ptWay)
		{
			double dis = DisPtToLine(ptWay, lnSource);
			return LineParallel(lnResult, lnSource, ptWay, dis);
		}
		TLine TPlaneGeometry::LineParallel(const TLine& lnSource,
															const TPoint & ptWay)
		{
			TLine lnResult;
			if(!LineParallel(lnResult, lnSource, ptWay))
			{
				lnResult = lnSource;
			}
			return lnResult;
		}
		//</Add>
		//</Author>
		//**********

		////********************************************************************
		////���ߣ���۽�
		////���ܣ���õ���ֱ���ϵĴ��㡣
		////********************************************************************
		TPoint TPlaneGeometry::PtPedal(const TPoint & ptBase, const TLine& ll)
		{
			//����߱�����һ����
			if(ll.pt1 == ll.pt2)
			{
				return ll.pt1;
			}
			//�����������
			if(IsPtInLine(ptBase, ll))	
			{
				return ptBase;
			}

			TLine llParallel	= LineParallel(ptBase,ll);	////�õ�ƽ����
			NormLine(llParallel);

			TPoint ptResult;
			Intersect(TLine(ll),llParallel,ptResult);
			return ptResult;
		}

		////********************************************************************
		////���ߣ���۽�
		////���ܣ���ýǷ��ߡ�
		////********************************************************************
		double TPlaneGeometry::MidArc(const TArc & arc)
		{
			double arcMid = (arc._edArc + arc._stArc) /2;
			if (arc._stArc > arc._edArc)
			{
				arcMid+=PI_R;
			}
			arcMid = Radian(arcMid);
			return arcMid;
		}
		TPoint TPlaneGeometry::MidArcPt(const TArc & arc)
		{
			double arcMid = MidArc(arc);
			TPoint ptMid;
			ptMid.x = arc._ptCentre.x + arc._r*cos(arcMid);
			ptMid.y = arc._ptCentre.y + arc._r*sin(arcMid);
			ptMid.z = 0;
			return ptMid;
		}
		TLine TPlaneGeometry::MidArcLine(const TArc & arc)
		{
			TPoint ptMid = MidArcPt(arc);
			return TLine(TPoint(arc._ptCentre), ptMid);
		}

		////********************************************************************
		////���ߣ���۽�
		////���ܣ���ýǷ��ߵ�������ߡ�
		////********************************************************************
		TLine TPlaneGeometry::TangentLine(const TArc & arc)
		{
			TLine llMid = MidArcLine(arc);
			TLine llReverseMid(llMid.pt2,llMid.pt1);
			NormLine(llReverseMid);
			TLine llTangentLine(TPoint(0,0,0),TPoint(1,1,0));
			Intersect(llReverseMid,arc.LineSt(), llTangentLine.pt1);
			Intersect(llReverseMid,arc.LineEd(), llTangentLine.pt2);
			return llTangentLine;
		}

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-04-24 to 2007-04-24
		////���ܣ��ǶȻ��Ȼ�����
		////********************************************************************
		double TPlaneGeometry::Angle2Arc(double angle)
		{
			return angle * PI_R / 180.0;
		}
		double TPlaneGeometry::Arc2Angle(double arc)
		{
			return arc * 180.0 / PI_R;
		}

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-05-15 to 2007-04-15
		////���ܣ��ڸ��������Ͻ�ȡһ�Ρ�
		////********************************************************************
		TLine TPlaneGeometry::LineIntersect(const TLine& tl, double len, EOrgPt eOrg)
		{
			if (!(eOrg == TPO_ORGPT1 || eOrg == TPO_ORGPT2))	return tl;

			TLine tlOld = eOrg == TPO_ORGPT1 ? tl : Reverse(tl);
			CGeNorm norm(tlOld.pt1, tlOld.pt2);
			norm.normalize();
			TPoint ptNew = tlOld.pt1.PolarTo((float)len, &norm);
			TLine tlNew(tlOld.pt1, ptNew);

			return eOrg == TPO_ORGPT1 ? tlNew : Reverse(tlNew);
		}

		////********************************************************************
		////���ڣ�2007-05-20 to 2007-04-20
		////���ܣ��㵽�ߵľ��롣
		////ע�⣺����true�������߶��ϣ�����false���������ӳ�����
		////********************************************************************
		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TLine& tl)
		{
			TPoint ptPedal = PtPedal(pt, tl);
			len = TLine(pt, ptPedal).Length();
			return true;
		}

		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TRayLine& rl)
		{
			TPoint ptPedal = PtPedal(pt, rl);
			len = TLine(pt, ptPedal).Length();
			if (IsPtInLine(ptPedal, rl))
			{
				return true;
			}
			return false;
		}

		bool TPlaneGeometry::Length(double & len, const TPoint& pt, const TSegLine& sl)
		{
			TPoint ptPedal = PtPedal(pt, sl);
			len = TLine(pt, ptPedal).Length();
			if (IsPtInLine(ptPedal, sl))
			{
				return true;
			}
			return false;
		}
		////********************************************************************
		////���ڣ�2007-07-05 to 2007-07-05
		////���ܣ�����ľ���
		////********************************************************************
		double TPlaneGeometry::DisPt(const TPoint& pt1, const TPoint& pt2)
		{
			return sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2));
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////���ܣ��㵽ֱ�ߵľ���
		//****************************************
		double TPlaneGeometry::DisPtToLine(const TPoint& pt, const TLine& ln)
		{
			TPoint ptS = pt;
			ptS.z = 0;
			TPoint ptPedal = PtPedal(ptS, ln);
			ptPedal.z = 0;
			return DisPt(ptS, ptPedal);
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////���ܣ��㵽ֱ�ߵľ��룬���ض������ϵ�ӳ�䣨������+-��
		////����pt1 -> pt2
		//****************************************
		double TPlaneGeometry::DisPtByNormal(
								TPoint pt1, TPoint pt2, CGeNorm nm)
		{
			//��pt1��nm��ֱ�ߣ���pt2��ֱ�ߵĴ���ptPd����pt1��ptPd�ľ���ͷ���nmPd
			//����nm��nmPd���þ���+-����(���Ϊ+)
			TLine ln(pt1, nm);
			TPoint ptPd = PtPedal(pt2, ln);
			double dis = DisPt(pt1, ptPd);

			CGeNorm nmPd(pt1, ptPd);
			nmPd.normalize();
			nm.normalize();

			return nm == nmPd ? dis : -dis;
		}
		//**********************************************************************
		//<Add>=Date:2007/07/30
		////���ܣ��㵽ֱ�ߵľ��룬���ض������ϵ�ӳ�䣨������+-��
		////����ln -> pt
		//****************************************
		double TPlaneGeometry::DisPtToLineByNormal(
								TPoint pt, TLine ln, CGeNorm nm)
		{
			//����ֱ�ߵĴ��������ʹ����������ϵľ���
			TPoint ptPdLn = PtPedal(pt, ln);
			return DisPtByNormal(ptPdLn, pt, nm);
		}
		//**********


		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-05-20 to 2007-04-20
		////���ܣ��жϵ��Ƿ��ڻ���
		////********************************************************************
		bool TPlaneGeometry::IsPtInArc(const TPoint& pt, const TArc& arc)
		{
			double rArc = Radian(pt, arc._ptCentre);
			if (arc._edArc > arc._stArc)
			{
				if (arc._stArc <= rArc && rArc <=  arc._edArc)
				{
					return true;
				}
			}
			else
			{
				if (arc._stArc <= rArc || rArc <=  arc._edArc)
				{
					return true;
				}
			}
			return false;
		}

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-07-03 to 2007-07-03
		////���ܣ��жϵ��Ƿ��ڶ������
		////********************************************************************
		bool TPlaneGeometry::IsPtInPolygon(const TPoint& pt, 
										   const TPoint * pPtPolygon, int nCount)
		{
			if(nCount < 2) return false;
			int nCross = 0; 
			for (int i = 0; i < nCount; i++) 
			{ 
				TPoint p1 = pPtPolygon[i]; 
				TPoint p2 = pPtPolygon[(i+1) % nCount]; 
				//// ��� y=p.y �� p1p2 �Ľ��� 
				if (TEquFloat(p1.y,p2.y) ) //// p1p2 �� y=p0.yƽ�� 
					continue; 
		//		if ( pt.y < min(p1.y, p2.y) ) //// ������p1p2�ӳ����� 
				if (TLessThen(pt.y, min(p1.y, p2.y)) ) //// ������p1p2�ӳ����� 
					continue; 
		//		if ( pt.y >= max(p1.y, p2.y) ) //// ������p1p2�ӳ����� 
				if (TMoreEqu( pt.y, max(p1.y, p2.y)) ) //// ������p1p2�ӳ����� 
					continue; 
				//// �󽻵�� X ���� 
				double x =	(double)(pt.y-p1.y) * 
							(double)(p2.x-p1.x) / 
							(double)(p2.y-p1.y) + p1.x; 
				if (TMoreThen(x, pt.x) ) 
					nCross++; //// ֻͳ�Ƶ��߽��� 
			} 
			//// ���߽���Ϊż�������ڶ����֮�� --- 
			return (bool)(nCross % 2 == 1); 
		}

		bool TPlaneGeometry::IsPtInPolygon(const TPoint& pt, 
										   const vector<TPoint>& vPtPlolygons)
		{
			int nSizePolygon = vPtPlolygons.size();
			if(nSizePolygon < 2) return false;
			////����ǡ���ڱ����ϣ���ֱ���϶����ڶ�����ڡ�
			TSegLine slBorder;
			for (int i=0; i< nSizePolygon; i++)
			{
				slBorder.Set(vPtPlolygons[i], vPtPlolygons[(i+1)%nSizePolygon]);
				if (IsPtInLine(pt, slBorder)) {
					return true;
				}
			}
			////�жϵ��Ƿ��ڶ������
			return IsPtInPolygon(pt, &vPtPlolygons[0], nSizePolygon);
		}


		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-07-05 to 2007-07-05
		////���ܣ��ߴ���������ڣ����������ڡ����߶��顣
		////********************************************************************
		bool TPlaneGeometry::LineInPolygon(const TSegLine& sl,const vector<TPoint>& vPtsPolygon,
							vector<TSegLine>& vSlsInside, vector<TSegLine>& vSlsOutside)
		{
			int nSizePolygon = vPtsPolygon.size();
			if (nSizePolygon < 2)	return false;

			TSegLine slIn(sl);

			TPoint ptAcross;								////�߶�����߽���(��ʱ)
			TSegLine slBorder;							////����(��ʱ)
			vector<TPoint> vPtsAcross;					////�߶�����߽�������
			vPtsAcross.push_back(sl.pt1);				////��ԭʼ�߶ε������˵����
			for (int i=0; i< nSizePolygon; i++)
			{
				slBorder.Set(vPtsPolygon[i], vPtsPolygon[(i+1)%nSizePolygon]);
				slIn.pt1.z = slIn.pt2.z = slBorder.pt1.z = slBorder.pt2.z = 0.0;
				if((slIn.pt1 == slBorder.pt1 && slIn.pt2 == slBorder.pt2)||
					(slIn.pt1 ==  slBorder.pt2&& slIn.pt2 == slBorder.pt1))
				{
					continue;			
				}
				else if (Intersect(slIn, slBorder, ptAcross))
				{
					if (!(IsPtEqu(vPtsAcross[vPtsAcross.size()-1] , ptAcross)))
						vPtsAcross.push_back(ptAcross);		////��������
				}
			}
			if (!(IsPtEqu(vPtsAcross[vPtsAcross.size()-1] , sl.pt2)))
				vPtsAcross.push_back(sl.pt2);
			
			SortDisToPt(vPtsAcross, sl.pt1);			////����

			TSegLine slTemp;								
			for (i=0; i<vPtsAcross.size()-1; i++)
			{											////�е��ڶ������
				slTemp.Set(vPtsAcross[i], vPtsAcross[i+1]);
			if(IsPtInPolygon(slTemp.PtCenter(), vPtsPolygon)){
					vSlsInside.push_back(slTemp);
			}
			else{
					vSlsOutside.push_back(slTemp);
			}
			}

			return true;
		}

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-07-05 to 2007-07-05
		////���ܣ��������ľ�������(�ɽ���Զ)
		////********************************************************************
		bool TPlaneGeometry::SortDisToPt(vector<TPoint>& vPts, const TPoint& ptFixed)
		{
			for (int i=0; i<vPts.size()-1; i++)
			{
				for(int k=0; k<vPts.size()-1; k++)
				{
					if (DisPt(vPts[k],ptFixed) > DisPt(vPts[k+1],ptFixed))
					{
						swap(vPts[k], vPts[k+1]);
					}
				}
			}
			return true;
		}



		BOOL TPlaneGeometry::IfAoRect(vector<TPoint>& pt3dsFront)
		{
			CGeNorm nmlNow, nmlPre, nmlMaxicNow, nmlMaxicPre;////danger
			TPoint ptStart,ptEnd;
			int j=0;
			for(int i=0;i<pt3dsFront.size()+2;i++)
			{
				j = (i+1)%pt3dsFront.size();
				pt3dsFront[i].z = 0;
				ptStart = pt3dsFront[i];
				ptEnd = pt3dsFront[j];
				nmlPre = nmlNow;
				nmlNow.Set(ptStart,ptEnd);

				nmlMaxicPre = nmlNow;
				nmlMaxicNow = nmlNow * nmlPre;

				if (nmlMaxicNow.m_z * nmlMaxicPre.m_z < 0)
					return TRUE;
			}
			return FALSE;
		} 

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-07-05 to 2007-07-05
		////���ܣ����ݱ������м�ֵ
		////˵����(x0-x1)/(x2-x1) == m/(m-n)
		////********************************************************************
		double TPlaneGeometry::ScaleMean(double x1, double x2, double m, double n)
		{
			return x1 + (m*(x2-x1))/(m-n);
		}

		////********************************************************************
		////���ߣ���۽�
		////���ڣ�2007-07-10 to 2007-07-10
		////���ܣ�ȥ���غϵ㡣
		////********************************************************************
		bool TPlaneGeometry::DeleteRepeatPt(vector<TPoint>& vPts)
		{
			SortDisToPt(vPts, vPts[0]);
			vector<TPoint>::iterator it1 = vPts.end(), it2 = vPts.end();
			while (it1 != vPts.begin() && it2 != vPts.begin())
			{
				it1--;
				if (*it1 == *it2)
				{
					vPts.erase(it1,it2);
					it1--;
					it2--;
				}
				it2--;
			}
			return true;
		}

		////********************************************************************
		////���ܣ��жϵ��Ƿ�������
		////********************************************************************
		bool TPlaneGeometry::IsPtInLine(const TPoint& pt, const TLine	 & tl)
		{
			TRayLine r1(tl.pt1,tl.pt2), r2(tl.pt2,tl.pt1);
			if (IsPtInLine(pt,r1) || IsPtInLine(pt,r2))
			{
				return true;
			}
			return false;
		}
		bool TPlaneGeometry::IsPtInLine(const TPoint& pt, const TRayLine& rl)
		{
			CGeNorm normRayLine(rl.pt1, rl.pt2);
			normRayLine.m_z = 0.0;
			normRayLine.normalize();
			CGeNorm normToPt(rl.pt1, pt);
			normToPt.m_z = 0.0;
			normToPt.normalize();

			if (normRayLine == normToPt)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		bool TPlaneGeometry::IsPtInLine(const TPoint &pt, const TSegLine &sl)
		{
			TRayLine r1(sl.pt1,sl.pt2), r2(sl.pt2,sl.pt1);
			if (IsPtInLine(pt,r1) && IsPtInLine(pt,r2))
			{
				return true;
			}
			return false;
		}

		//////********************************************************************
		//////���ܣ��жϵ��Ƿ���ȣ�����z��
		//////********************************************************************
		bool TPlaneGeometry::IsPtEqu(const TPoint& pt1, const TPoint& pt2)
		{
			return (TEquFloat(pt1.x, pt2.x) && TEquFloat(pt1.y, pt2.y));
		}
		//////********************************************************************
		//////���ܣ��ж��߶��Ƿ�������ƽ��ֱ��֮��(����z)
		//////********************************************************************
		bool TPlaneGeometry::IsSegInsideLine(const TSegLine& sl, 
								const TLine& ln1, const TLine& ln2)
		{
			TPoint ptCross;
			if(Intersect(ln1,ln2,ptCross))
				return false;
			double dis_ln1_ln2 =0, dis_sl_Ln1 = 0, dis_sl_ln2 = 0;
			Length(dis_ln1_ln2, ln1.pt1, ln2);
			Length(dis_sl_Ln1 , sl .pt1, ln1);
			Length(dis_sl_ln2 , sl .pt1, ln2);
			if(TMoreThen(dis_sl_Ln1,dis_ln1_ln2) || TMoreThen(dis_sl_ln2,dis_ln1_ln2))
				return false;
			Length(dis_sl_Ln1 , sl .pt2, ln1);
			Length(dis_sl_ln2 , sl .pt2, ln2);
			if(TMoreThen(dis_sl_Ln1,dis_ln1_ln2) || TMoreThen(dis_sl_ln2,dis_ln1_ln2))
				return false;
			return true;
		}

		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/07/30
		////�ж϶�����Ƿ���͹�����
		//****************************************
		bool TPlaneGeometry::IsPolygonConvex(const vector<TPoint>& vPtsPolygon)
		{
			int iResult = 0;
			int nSizePolygon = vPtsPolygon.size();
			CGeNorm gn1(gc_ptOrg,gc_ptOrg);
			CGeNorm gn2(gn1); 
			CGeNorm gnRusult(gn1);
			for(int i=0; i<nSizePolygon+1; i++)
			{
				gn2 = gn1;
				gn1.Set(TPoint(vPtsPolygon[i%nSizePolygon]),				
						TPoint(vPtsPolygon[(i+1)%nSizePolygon]));
				gn1.normalize();
				if(!(gn2 == gc_gnOrg))
				{
					gnRusult = gn1 * gn2;
					gnRusult.normalize();
					iResult += gnRusult.m_z>=0 ? 1 : -1;
				}
			}
			if(abs(iResult) == nSizePolygon)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//</Add>
		//</Author>
		//**********


		//**********************************************************************
		//<Author>:Tian Baijie
		//<Add>=Date:2007/08/02
		////˫���ӳ���
		//****************************************
		bool TPlaneGeometry::LineExtend(TLine& lnResult, 
										const TLine& lnSource, 
										double dLen)
		{
		  if(!LineExtend(lnResult, lnSource, dLen, dLen))
		  {
			return false;
		  }
		  return true;
		}
		TLine TPlaneGeometry::LineExtend(const TLine& lnSource, double dLen)
		{
		  TLine lnResult;
		  LineExtend(lnSource, dLen);
		  return lnResult;
		}
		bool  TPlaneGeometry::LineExtend(TLine& lnResult, 
										 const TLine& lnSource, 
															   double dLenSt, 
										 double dLenEd)
		{
		  TPoint ptS1 = lnSource.pt1;
		  ptS1.z = 0;
		  TPoint ptS2 = lnSource.pt2;
		  ptS2.z = 0;
		  CGeNorm nmWay(ptS1, ptS2);
		  nmWay.normalize();
		  TPoint ptD2 = ptS2.PolarTo(dLenEd, &nmWay);
		  nmWay.Set(ptS2, ptS1);
		  nmWay.normalize();
		  TPoint ptD1 = ptS1.PolarTo(dLenSt, &nmWay);
		  lnResult.Set(ptD1, ptD2);
		  return true;
		}
		TLine TPlaneGeometry::LineExtend(const TLine& lnSource, 
															   double dLenSt, 
										 double dLenEd)
		{
		  TLine lnResult;
		  LineExtend(lnSource, dLenSt, dLenEd);
		  return lnResult;
		}

		bool TPlaneGeometry::PtOrtho(TPoint& pt, 
									 TLine lnBase, TPoint ptBase)
		{
			TLine lnBaseParallel = LineParallel(lnBase, ptBase);
			pt = PtPedal(pt, lnBaseParallel); 
			return true;
		}
		bool TPlaneGeometry::PtOrtho(TPoint& pt, TLine lnBase)
		{
			pt = PtPedal(pt, lnBase); 
			return true;
		}

		////********************************************************************
		////���ܣ����ݵ�ͽǶ����/�ߡ�
		////********************************************************************
		TPoint TPlaneGeometry::PtFromAngle(TPoint pt, double angle)
		{
			pt.z = 0;
			pt.x = pt.x + cos(angle);
			pt.y = pt.y + sin(angle);
			return pt;
		}
		TLine TPlaneGeometry::LineFromangle(TPoint pt, double angle)
		{
			return TLine(pt, PtFromAngle(pt, angle));
		}

		CGeNorm TPlaneGeometry::NormalFromAngle(double angle)
		{
			CGeNorm nm;
			nm.m_x = cos(angle) * 1;
			nm.m_y = sin(angle) * 1;
			nm.m_z = 0;
			return nm;
			
		}

		bool TPlaneGeometry::is_line_superpositon(TLine ln1, TLine ln2)
		{
			if(IsPtInLine(ln2.pt1, ln1) && IsPtInLine(ln2.pt2, ln1)){
			  return true;
			}
			return false;
		}

		bool TPlaneGeometry::is_pt_superposition(TPoint pt1, TPoint pt2)
		{
		  pt1.z = 0;
		  pt2.z = 0;
		  if(pt1 == pt2){
			return true;
		  }else{
			return false;
		  }
		}






		//</Author>
		}
		//********** 





