#pragma once
#include "afxcmn.h"


// CTerrainTab ��ȭ �����Դϴ�.

//////////////////////////////////////////////////////////////////////////
/// TODO 
/// 1. ���ؽ� �� ��ŷ
/// 2. �̹��� �ٲٱ�
/// 3. CntX, CntZ, Interval, Detail�� �ٲ㼭 Tex ���� �����ϱ�
/// 4. �׺���̼� �޽� ��ġ�ϱ�
//////////////////////////////////////////////////////////////////////////

class CMyFormView;

class CNaviTool;
class CTerrainTool;
class CPickTool;
class CTerrainMeshTool;

class CTerrainTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTab)

public:
	CTerrainTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTerrainTab();

	void		Initialize_FormView(void);
	const Engine::_bool	Get_Initialized(void) const;
	void				Initialize_MapMeshes(void);
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAIN_DLG };
#endif
	void			Deactivate_Tool(void);
	void			Activate(void);
protected:
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	vector<CDialogEx*>	m_vecDlg;
	CTabCtrl			m_TabCtrl;
	CMyFormView*		m_pParentForm;

	CTerrainTool*		m_pTerrainTool;
	CTerrainMeshTool*	m_pTerrainMeshTool;

	Engine::_bool		m_bInitialized;

public:
	CMyFormView*		Get_FormView(void) { return m_pParentForm; }
	virtual BOOL		OnInitDialog();
	afx_msg void		OnBnClickedWireframe();
	afx_msg void		OnBnClickedSolid();
	afx_msg void		OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
