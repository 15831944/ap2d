#if !defined(AFX_COLOR_COMBOBOX_H__D155032B_3D38_4410_BF9C_E5EA19A8AF9F__INCLUDED_)
#define AFX_COLOR_COMBOBOX_H__D155032B_3D38_4410_BF9C_E5EA19A8AF9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Color_ComboBox.h : header file
//
//!!!Ϊʹ��ģ��CArray/CList֮������������������ͷ�ļ�!!!
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// Color_ComboBox window
/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���Color_ComboBox.h
	��Ȩ��
	��������������Ҫ�����ɫѡ����Ͽ�
	ʹ�ã���combobox �������droplist ��owerdraw ���variable,��sort����Ҳȥ��
	�ڶԻ���������
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/



class Color_ComboBox : public CComboBox
{
public:
	typedef struct BSCBITEM
	{
		int			iIndex;
		COLORREF	crColor;
		LPCTSTR		lpCaption;
	}BSCBITEM, *LPBSCBITEM;

// Construction
public:
	Color_ComboBox();

// Attributes
public:

// Operations
public:
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);	
	void init_color(void);//��ʼ����Ͽ�(��һ�������õĺ���)	
	void add_one_color(CString color_name,COLORREF col);

	COLORREF get_color();//�õ���ǰ����ɫֵ��R/G/Bֵ
	void get_rgb_color(int* R, int* G, int* B);

	int get_color_index();

	void set_color_index(int color){color_index_ = color;}
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Color_ComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Color_ComboBox();

	// Generated message map functions
protected:
	bool m_bOverControl;	//����״̬(�Ƿ��ڰ�ť��)	
	int iIconX, iIconY;		//SMALL ICON�Ĵ�С�ߴ�
	COLORREF m_crColor;		//��ǰѡ�е���ɫ
	CList<LPBSCBITEM, LPBSCBITEM> m_crItem;
	int color_index_;



	LPBSCBITEM red_;
	LPBSCBITEM yellow_;
	LPBSCBITEM green_;
	LPBSCBITEM cyan_;
	LPBSCBITEM blue_;
	LPBSCBITEM fuchsin_;
	LPBSCBITEM write_;
	LPBSCBITEM black_;
		
	void OnCBPaint(CDC* pDC);
	Color_ComboBox::LPBSCBITEM GetItem(int iIndex = 0);
	//{{AFX_MSG(Color_ComboBox)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSelendok();
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOR_COMBOBOX_H__D155032B_3D38_4410_BF9C_E5EA19A8AF9F__INCLUDED_)
