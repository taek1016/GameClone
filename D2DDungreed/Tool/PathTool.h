#pragma once
#include "afxwin.h"


// CPathTool

class CPathTool : public CDialog
{
	DECLARE_DYNAMIC(CPathTool)

public:
	CPathTool(CWnd* pParemt = NULL);
	virtual ~CPathTool();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	void SettingHorizontalScrollSize();

	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedPathSave();
	afx_msg void OnBnClickedPathLoad();

public:
	CListBox m_ListBox;
	std::list<PATH_INFO*>	m_PathInfoList;

};


