#pragma once


// CEffectTab ��ȭ �����Դϴ�.

class CCamPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEffectTab)

public:
	CCamPathDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCamPathDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EFFECT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
