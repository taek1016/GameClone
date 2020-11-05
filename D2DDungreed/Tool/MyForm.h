#pragma once



// CMyForm �� ���Դϴ�.

#include "Map_Tool.h"
#include "PathTool.h"
#include "BackgroundObjectTool.h"
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapButton();
	afx_msg void OnBnClickedPathtoolButton();
	afx_msg void OnBnClickedObjectButton();

	virtual void OnInitialUpdate();

public:
	CFont					m_Font;
	CMap_Tool				m_MapTool;
	CPathTool				m_PathTool;
	CBackgroundObjectTool	m_ObjectTool;
};


