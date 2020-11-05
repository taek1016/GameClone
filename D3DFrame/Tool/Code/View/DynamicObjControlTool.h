#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDyMeshTab 대화 상자입니다.
class CToolDynamicObject;

class CDynamicObjTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDynamicObjTool)

public:
	CDynamicObjTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDynamicObjTool();

	Engine::_bool	Get_Initialized(void) const;

	Engine::_bool	Get_Activated(void) const;
	void			Activate(void);
	void			Deactivate(void);

	void			Initialize_DynamicMeshTab(void);
	void			Initialize_DynamicMeshLoad(void);

	void			KeyInput(void);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_MONSTER };
#endif

protected:
	void				reset_List(void);
	CToolDynamicObject*	get_SelectedObj(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	Engine::_tchar*	m_pTypeName;
	CString			m_strCloneName;
	CString			m_SelectedStrName;

	Engine::_bool	m_bIntialized;
	Engine::_bool	m_bActivated;

	float			m_fPosX;
	float			m_fPosY;
	float			m_fPosZ;
	float			m_fScaleX;
	float			m_fScaleY;
	float			m_fScaleZ;
	float			m_fRotX;
	float			m_fRotY;
	float			m_fRotZ;

	CComboBox		m_PrafabComboBox;
	CListBox		m_CloneList;

public:
	afx_msg void OnEnChangeDynamicPosXEdit();
	afx_msg void OnDeltaposDynamicPosXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedGroupPlayerRadio();
	afx_msg void OnBnClickedGroupNpcRadio();
	afx_msg void OnBnClickedGroupMonsterRadio();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnEnChangeDynamicPosYEdit();
	afx_msg void OnDeltaposDynamicPosYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicPosZEdit();
	afx_msg void OnDeltaposDynamicPosZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicScaleEdit();
	afx_msg void OnDeltaposDynamicScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicScaleYEdit();
	afx_msg void OnDeltaposDynamicScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicScaleZEdit();
	afx_msg void OnDeltaposDynamicScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicRotXEdit();
	afx_msg void OnDeltaposDynamicRotXSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicRotYEdit();
	afx_msg void OnDeltaposDynamicRotYSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeDynamicRotZEdit();
	afx_msg void OnDeltaposDynamicRotZSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCloneButton();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedDynamicMeshSave();
	afx_msg void OnBnClickedDynamicMeshLoad();
};