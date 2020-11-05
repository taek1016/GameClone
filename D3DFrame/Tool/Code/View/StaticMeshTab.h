#pragma once
#include "afxcmn.h"


// CTabDlg ��ȭ �����Դϴ�.
class CMyFormView;
class CStaticMeshTool;

class CStaticMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CStaticMeshTab)

public:
	CStaticMeshTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStaticMeshTab();

	const Engine::_bool&	Get_Initialized(void) const;
	void					Initialize_StaticMeshTab(void);
	void					Initialize_StaticMeshLoad(void);
	void					Key_Input(void);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	Engine::_bool			m_bMeshLoaded;
	CMyFormView*			m_pParentForm;
	CTabCtrl				m_TabCtrl;
	vector<CDialogEx*>		m_vecDlg;
	CStaticMeshTool*		m_pMeshTool;

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
