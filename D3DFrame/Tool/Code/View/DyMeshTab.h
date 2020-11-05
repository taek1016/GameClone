#pragma once
#include "afxcmn.h"


// DyMeshTab ��ȭ �����Դϴ�.
class CDynamicObjTool;
class CPrefabDlg;

class CDyMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDyMeshTab)

public:
	CDyMeshTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual						~CDyMeshTab();

	void						Initialize_DynamicMeshTab(void);
	void						Initialize_DynamicMeshLoad(void);
	Engine::_bool				Get_Initialized(void);

	void						DeActivate(void);
	void						Activate(void);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_MESH_DLG };
#endif

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	Engine::_bool				m_bInitialized;
	Engine::_bool				m_bActivated;
	CTabCtrl					m_TabCtrl;

	CDynamicObjTool*		m_pMonsterMesh;
	CPrefabDlg*					m_pPrefabDlg;

	vector<CDialogEx*>			m_vecDialog;
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
