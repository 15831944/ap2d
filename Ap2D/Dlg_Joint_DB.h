#if !defined(AFX_DLG_JOINT_DB_H__800B5548_82F4_49E3_AE5C_06C2670ED0B2__INCLUDED_)
#define AFX_DLG_JOINT_DB_H__800B5548_82F4_49E3_AE5C_06C2670ED0B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Joint_DB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Dlg_Joint_DB dialog

class Dlg_Joint_DB : public CDialog
{
// Construction
public:
	Dlg_Joint_DB(CWnd* pParent = NULL);   // standard constructor
//	Dlg_Joint_DB();
	virtual	~Dlg_Joint_DB();

	void	init_db();
	void get_datas();
	void	show_data_to_dlg();
	void show_image(CString strFile);//��ʾͼƬ��picture�ؼ���
	void 	set_sel_name(CString name);//���� ѡ�е��ı���
	void init_sel(); //���ݴ����name ��ʼ����ǰ�Ի�����picture�ؼ�����ʾ����
	void re_call();//��������Ĺ����Ƿ���dlg_joint_db_edit����ˢ��dlg_joint_db�Ի���
	BOOL dlg_is_have();
	BOOL show_picture(CString);
	
// Dialog Data
	//{{AFX_DATA(Dlg_Joint_DB)
	enum { IDD = IDD_DLG_JOINT_DB };
	CStatic	static_pictures_;
	CComboBox	combo_joint_name_;
	//}}AFX_DATA
//	CBitmap bmp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dlg_Joint_DB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(Dlg_Joint_DB)
	afx_msg void OnButEditDb();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboJointName();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual void OnOK();
//	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString file_path_;
	CString sel_name_;
	BOOL dlg_status_;
	  
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_JOINT_DB_H__800B5548_82F4_49E3_AE5C_06C2670ED0B2__INCLUDED_)
