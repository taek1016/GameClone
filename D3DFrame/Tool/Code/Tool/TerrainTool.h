#pragma once
#include "afxwin.h"


// CTerrainTool 대화 상자입니다.
class CTerrainTab;
BEGIN(Engine)
class CCell;
END
class CTerrainTool : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CTerrainTab* pParentTab, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainTool();

	const float			Get_DefaultYValue(void) const;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAIN_TOOL };
#endif
	void				Initialize_MapMeshes(void);
	void				Activate(void);
	void				DeActivate(void);
	bool				GetActivate(void) const { return m_bActivate; }

	void				Act(void);
	void				Add_List(vector<Engine::CCell*>* pVecCell);

protected:
	virtual void		DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	bool				m_bActivate;
	CTerrainTab*		m_pParentTab;
	DWORD				m_dwCntX;
	DWORD				m_dwCntZ;
	DWORD				m_dwVtxItv;
	float				m_fDetail;

	class CToolTerrain*	m_pTerrain;

	CListBox			m_bListBox;

	float				m_fZMove;

	wstring				m_wstrFilePath;

	float				m_fXPos;
	float				m_fYPos;
	float				m_fZPos;

public:
	afx_msg void OnBnClickedTerrainControl();
	afx_msg void OnBnClickedNaviControl();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDeltaposNaviXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposNaviYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposNaviZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTerrainSave();
	afx_msg void OnBnClickedTerrainLoad();
	afx_msg void OnEnChangeTerrainMeshName();
private:
	int m_iCntX;
	int m_iCntZ;
public:
	afx_msg void OnBnClickedGuidelineCreateButton();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeNaviXPos();
	afx_msg void OnEnChangeNaviYPos();
	afx_msg void OnEnChangeNaviZPos();
private:
	float m_fDefaultY;
public:
	afx_msg void OnEnChangeNaviDefaultYButton();
	afx_msg void OnBnClickedZMove001Radio();
	afx_msg void OnBnClickedZMove01Radio();
	afx_msg void OnBnClickedZMove10Radio();
};
