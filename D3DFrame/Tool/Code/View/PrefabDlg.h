#pragma once
#include "afxwin.h"


// CPrefabDlg 대화 상자입니다.
class CToolDynamicObject;

class CPrefabDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrefabDlg)

public:
	CPrefabDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPrefabDlg();

	void			Initialize_Names(void);

	Engine::_bool	Get_Initialized(void);
	void			Initialize_Prefab(void);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PREFAB_DLG };
#endif

protected:
	void				save_PrefabData(HANDLE hFile, CToolDynamicObject* pObj);
	void				save_AnimationData(HANDLE hFile, CToolDynamicObject* pObj);
	void				save_BoneData(HANDLE hFile, CToolDynamicObject* pObj);
	void				make_Prefabs(void);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	void				applyPrefabChange(void);

	CToolDynamicObject*	m_pDynamicObj;

	Engine::_bool		m_bInitialized;

	CComboBox			m_AnimationComboBox;
	CComboBox			m_PrefabComboBox;
	CComboBox			m_BoneComboBox;
	CComboBox			m_ActionComboBox;

	CString				m_strAnimationName;
	CString				m_strPrefabName;
	CString				m_strBoneName;
	CString				m_strMakeActionName;

	float				m_fScaleX;
	float				m_fScaleY;
	float				m_fScaleZ;

	float				m_fSphereRadius;

	float				m_fBoxMin;
	float				m_fBoxMax;

	float				m_fActionCool;

public:
	afx_msg void OnBnClickedCallPrefabButton();
	afx_msg void OnBnClickedPrefabChangeApplyButton();
	afx_msg void OnBnClickedAnimateButton();
	afx_msg void OnBnClickedBoneColliderApplyButton();
	afx_msg void OnBnClickedBoneColliderDeleteButton();
	afx_msg void OnBnClickedPrefabSaveButton();
	afx_msg void OnBnClickedPrefabLoadButton();
	afx_msg void OnEnChangePrefabKeyEdit();
	afx_msg void OnEnChangeAnimationNumberEdit();
	afx_msg void OnEnChangeAnimationKeyStringEdit();
	afx_msg void OnBnClickedBoneNameSaveButton();
	afx_msg void OnBnClickedBoneNameLoadButton();
	afx_msg void OnBnClickedExportKeyButton();
	afx_msg void OnEnChangeMainColEdit();
	afx_msg void OnBnClickedMainColApplyButton();
	afx_msg void OnEnChangeColliderRadiusEdit();
	afx_msg void OnEnChangePrefabScaleXEdit();
	afx_msg void OnDeltaposPrefabScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangePrefabScaleYEdit();
	afx_msg void OnDeltaposPrefabScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangePrefabSclaeZEdit();
	afx_msg void OnDeltaposPrefabScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangePrefabActionCombo();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedBoxColApplyButton();
	afx_msg void OnEnChangeMinEdit();
	afx_msg void OnEnChangeMaxEdit();
	afx_msg void OnEnChangeActionNameEdit();
	afx_msg void OnEnChangeCoolTimeEdit();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeActionColCombo();
private:
public:
	afx_msg void OnEnChangeEdit3();
private:
	float m_fActionRadius;
};
