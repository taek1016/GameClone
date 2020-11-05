#pragma once
#include "afxwin.h"


// CMap_Tool ��ȭ �����Դϴ�.

class CMap_Tool : public CDialog
{
	DECLARE_DYNAMIC(CMap_Tool)

public:
	CMap_Tool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMap_Tool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_TOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	void SettingHorizontalScrollSize();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedMapSaveButton2();
	afx_msg void OnBnClickedMapLoadButton();
	afx_msg void OnLbnSelchangeMapList();

	// ��Ʈ�� ����
	CListBox	m_ListBox;
	CStatic		m_Picture;

	int			m_iDrawID;

	CString		m_strObjKey;
	CString		m_strObjStatus;
};
