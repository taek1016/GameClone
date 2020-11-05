#pragma once
#include "afxcmn.h"


// CTerrainTab 대화 상자입니다.

//////////////////////////////////////////////////////////////////////////
/// TODO 
/// 1. 버텍스 맵 피킹
/// 2. 이미지 바꾸기
/// 3. CntX, CntZ, Interval, Detail값 바꿔서 Tex 새로 생성하기
/// 4. 네비게이션 메쉬 배치하기
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
	CTerrainTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainTab();

	void		Initialize_FormView(void);
	const Engine::_bool	Get_Initialized(void) const;
	void				Initialize_MapMeshes(void);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAIN_DLG };
#endif
	void			Deactivate_Tool(void);
	void			Activate(void);
protected:
	virtual void	DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
