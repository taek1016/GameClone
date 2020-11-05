#pragma once
#include "afxcmn.h"


// CTabDlg 대화 상자입니다.
class CMyFormView;
class CStaticMeshTool;

class CStaticMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CStaticMeshTab)

public:
	CStaticMeshTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStaticMeshTab();

	const Engine::_bool&	Get_Initialized(void) const;
	void					Initialize_StaticMeshTab(void);
	void					Initialize_StaticMeshLoad(void);
	void					Key_Input(void);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
