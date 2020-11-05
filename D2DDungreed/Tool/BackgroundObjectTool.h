#pragma once
#include "afxwin.h"


// CBackgroundObjectTool ��ȭ �����Դϴ�.

class CMoveBackgroundObject;
class CBackgroundObjectTool : public CDialog
{
	DECLARE_DYNAMIC(CBackgroundObjectTool)

public:
	CBackgroundObjectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBackgroundObjectTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKGROUNDOBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	void SettingHorizontalScrollSize();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnClickedPushButton();
	afx_msg void OnBnClickedObjSaveButton();
	afx_msg void OnBnClickedObjLoadButton();
	afx_msg void OnBnClickedObjectRadio();
	afx_msg void OnBnClickedFrontObjRadio();

	CMoveBackgroundObject* GetMoveObject() const
	{
		return m_pObject;
	}

public:
	float							m_fMaxAnimationCount;
	float							m_fSpeed;
	float							m_fXSize;
	float							m_fYSize;
	float							m_fZValue;

	CString							m_strObjStatus;
	CString							m_strObjKey;
	CString							m_strName;

	CListBox						m_List;

	CMoveBackgroundObject*			m_pObject;
	std::vector<CMoveBackgroundObject*>		m_vecObject;

	OBJECT_TYPE						m_eObjType;
};
