#pragma once


// CEffectTab ��ȭ �����Դϴ�.
class CMyFormView;
class CEffectTab : public CDialogEx
{
	DECLARE_DYNAMIC(CEffectTab)

public:
	CEffectTab(CMyFormView* pParentForm,CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CEffectTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EFFECT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CMyFormView*		m_pParentForm;
};
