#pragma once
#include "afxwin.h"


// CMap_Tool 대화 상자입니다.

class CMap_Tool : public CDialog
{
	DECLARE_DYNAMIC(CMap_Tool)

public:
	CMap_Tool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMap_Tool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAP_TOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	void SettingHorizontalScrollSize();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedMapSaveButton2();
	afx_msg void OnBnClickedMapLoadButton();
	afx_msg void OnLbnSelchangeMapList();

	// 컨트롤 변수
	CListBox	m_ListBox;
	CStatic		m_Picture;

	int			m_iDrawID;

	CString		m_strObjKey;
	CString		m_strObjStatus;
};
