#pragma once
#include "afxcmn.h"


// CDataTab ��ȭ �����Դϴ�.
class CMyFormView;
class CPathTool;

class CDataTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDataTab)

	enum DATA_TAB { DATA_PATH, DATA_END };

public:
	CDataTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDataTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATA_TAB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
