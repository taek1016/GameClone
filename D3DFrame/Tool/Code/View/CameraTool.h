#pragma once


// CEffectTab 대화 상자입니다.

class CCamPathDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEffectTab)

public:
	CCamPathDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCamPathDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EFFECT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
