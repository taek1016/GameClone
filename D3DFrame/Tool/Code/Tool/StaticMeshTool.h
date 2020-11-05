#pragma once
#include "afxcmn.h"


// CStaticMeshTab 대화 상자입니다.
class CToolStaticObject;
class CToolStaticObjectCtrl;

class CStaticMeshTool : public CDialogEx
{
	DECLARE_DYNAMIC(CStaticMeshTool)

public:
	CStaticMeshTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStaticMeshTool();

	void			Activate(void);
	void			DeActivate(void);
	Engine::_bool	GetActivated(void) const;
	void			KeyInput(void);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STATIC_MESH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	CToolStaticObject*			get_SelectedObj(void);

	Engine::_bool				m_bActivated;

	list<const Engine::_tchar*>	m_TypeList;
	CToolStaticObjectCtrl*		m_pStaticMeshCtrl;

	CString						m_strKey;
	CString						m_strSelKey;
	CTreeCtrl					m_TreeCtrl;

	list<const Engine::_tchar*>	m_LoadNameList;

	float						m_fPosX;
	float						m_fPosY;
	float						m_fPosZ;
	float						m_fScaleX;
	float						m_fScaleY;
	float						m_fScaleZ;
	float						m_fRotX;
	float						m_fRotY;
	float						m_fRotZ;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnEnChangeStaticMeshPosX();
	afx_msg void OnDeltaposStaticMeshPosXSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshPosYEdit();
	afx_msg void OnDeltaposStaticMeshYPosSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshPosZEdit();
	afx_msg void OnDeltaposStaticMeshZPosSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshScalePosX();
	afx_msg void OnDeltaposStaticMeshScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshPosYScale();
	afx_msg void OnDeltaposStaticMeshScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshScaleZ();
	afx_msg void OnDeltaposStaticMeshScaleSpinZ(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshRotX();
	afx_msg void OnDeltaposStaticMeshRotSpinX(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshRotY();
	afx_msg void OnDeltaposStaticMeshRotSpinY(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeStaticMeshRotZ();
	afx_msg void OnDeltaposStaticMeshRotZSpin(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedButtonClone();
	afx_msg void OnBnClickedStaticMeshAdd();
	afx_msg void OnBnClickedStaticMeshDelete();
	afx_msg void OnBnClickedStaticMeshSave();
	afx_msg void OnBnClickedStaticMeshLoad();
	afx_msg void OnTvnSelchangedTreeStaticObj(NMHDR *pNMHDR, LRESULT *pResult);
private:
	float m_fRadius;
public:
	afx_msg void OnEnChangeStaticSphereRadiusEdit();
	afx_msg void OnDeltaposStaticSphereRadiusSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedStaticMeshSphereCreateButton();
	afx_msg void OnBnClickedColRenderCheck();
};
