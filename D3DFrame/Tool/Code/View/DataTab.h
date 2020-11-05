#pragma once
#include "afxcmn.h"


// CDataTab 대화 상자입니다.
class CMyFormView;
class CPathTool;

class CDataTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDataTab)

	enum DATA_TAB { DATA_PATH, DATA_END };

public:
	CDataTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDataTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	CMyFormView* m_pParentForm;

private:
	CTabCtrl			m_TabCtrl;
	vector<CDialogEx*>	m_vecDlg;

	CPathTool*			m_pPathTool;

public:
	afx_msg void OnTcnSelchangeDataTab(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
