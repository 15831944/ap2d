// TabCtrl_Left.h: interface for the TabCtrl_Left class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABCTRL_LEFT_H__95217571_6A80_493B_9805_99B28BCAC2DA__INCLUDED_)
#define AFX_TABCTRL_LEFT_H__95217571_6A80_493B_9805_99B28BCAC2DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define TCS_UP			0x0001		///����
#define TCS_DOWN		0x0002		///����
#define TCS_MONOSPACE	0x0004		///�ȿ�Ч��
#define TCS_ANIMATE		0x0008		///���������Ķ���Ч��
#define TCS_MASK		0x000f		///����:��������ֵ��"��",�������ڲ�ʹ��
#include "counter.h"

class TabCtrl_Left   : public CWnd
{
public:
	class CPageItem
	{
		friend class TabCtrl_Left;
		CPageItem()MCT_INIT1("CPageItem"){}
		CWnd*		m_pWnd;		///����,����ΪNULL
		UINT		m_nStyle;	///�������ͣ�0:��ͨ��1:��̬����
		CString		m_sText;	///����
		HICON		m_hIcon;	///ͼ��
	public:
		CRect		m_rect;		
	public:
		void SetPageStyle(UINT nStyle)
		{
			m_nStyle = nStyle;
		}

		UINT GetAreaWidth(CDC *pDC);
		void Draw(CDC *pDC,UINT nStyle,BOOL bActive);
	private:
	MCT_DEF
	};
	DECLARE_DYNCREATE(TabCtrl_Left)
// Construction
public:
	TabCtrl_Left();
	virtual ~TabCtrl_Left();

// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TabCtrl_Left)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetStyleMonoSpace(BOOL bEnable = TRUE);
	void SetStyleDirection(int Direction);		///Directionȡֵ:TCS_UP,TCS_DOWN
	void SetStyleAnimate(BOOL bEnable = TRUE);	///������bEnable = TRUE,����ΪFALSE
	void UpdateWindow();
	BOOL m_bEraseBkgnd;
	UINT GetStyle();
	void SetStyle(UINT style);
	void DrawFrame(CDC *pDC);
	void* GetPageItem(UINT nIndex);
	void SetActivePage(int nIndex);
	BOOL AddPage(CRuntimeClass* pClass,UINT nIDTemplate,LPCTSTR sText,UINT IconID = NULL);
	CPageItem* AddPage(CWnd *pWnd,LPCTSTR sText,UINT IconID = NULL);
	void AutoSize();
	void GetClientRect(LPRECT lpRect );
	BOOL Create(UINT wStyle, const CRect & rect, CWnd * pParentWnd, UINT nID);

	// Generated message map functions
protected:
	//{{AFX_MSG(TabCtrl_Left)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont		m_font;
	int			m_nActivePage;
	UINT		m_nStyle;
	UINT		m_nBorder;
	CPtrList	m_PageList;

private:
	TabCtrl_Left::CPageItem *pItem_;

private:
	MCT_DEF
};

#endif // !defined(AFX_TABCTRL_LEFT_H__95217571_6A80_493B_9805_99B28BCAC2DA__INCLUDED_)
