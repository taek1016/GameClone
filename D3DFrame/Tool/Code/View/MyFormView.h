#pragma once
#include "afxcmn.h"



// CMyFormView 폼 뷰입니다.
class CTerrainTab;
class CStaticMeshTab;
class CDataTab;
class CEffectTab;
class CDyMeshTab;

class CToolView;

class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

	enum TAB_ENUM { TAB_TERRAIN, TAB_STATIC_MESH, TAB_DYNAMIC_MESH, TAB_DATA, TAB_EFFECT, TAB_EVENT, TAB_END};

protected:
	CMyFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMyFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	void		Initialize_FormView(void);
	void		Set_ToolView(CToolView* pToolView);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CTabCtrl			m_TabCtrl;

	vector<CDialogEx*>	m_vecDialog;
	Engine::_int		m_iSize;

	CTerrainTab*		m_pTerrainTab		= nullptr;
	CStaticMeshTab*		m_pStaticMeshTab	= nullptr;
	CDataTab*			m_pDataTab			= nullptr;
	CEffectTab*			m_pEffectTab		= nullptr;
	CDyMeshTab*			m_pDynamicMeshTab	= nullptr;

	CToolView*			m_pToolView			= nullptr;

public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	virtual void OnInitialUpdate();
};