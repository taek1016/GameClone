#pragma once


// CCamDlg ��ȭ �����Դϴ�.

class CCamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCamDlg)

public:
	CCamDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCamDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAM_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
