#pragma once


// CTerrainMeshTool 대화 상자입니다.

class CTerrainMeshTool : public CDialogEx
{
	DECLARE_DYNAMIC(CTerrainMeshTool)

public:
	CTerrainMeshTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainMeshTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAIN_MESH_DLG };
#endif

private:
	float				m_fPosX;
	float				m_fPosY;
	float				m_fPosZ;
	float				m_fScaleX;
	float				m_fScaleY;
	float				m_fScaleZ;
	float				m_fAngleX;
	float				m_fAngleY;
	float				m_fAngleZ;
	CString				m_TerrainMeshName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeTerrainPosX();
	afx_msg void OnDeltaposTerrainPosXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainPosY();
	afx_msg void OnDeltaposTerrainPosYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainPosZ();
	afx_msg void OnDeltaposTerrainPosZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainScaleX();
	afx_msg void OnDeltaposTerrainScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainScaleY();
	afx_msg void OnDeltaposTerrainScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainScaleZ();
	afx_msg void OnDeltaposTerrainScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainAngleX();
	afx_msg void OnDeltaposTerrainAngleXSpin7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainAngleY();
	afx_msg void OnDeltaposTerrainAngleYSpin8(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTerrainAngleZ();
	afx_msg void OnDeltaposTerrainAngleZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTerrainMeshClone();

	afx_msg void OnEnChangeTerrainMeshName();
	afx_msg void OnBnClickedTerrainSaveButton();
	afx_msg void OnBnClickedTerrainLoadButton();
};
