#pragma once


// CEventTab ��ȭ �����Դϴ�.
class CMyFormView;
class CDynamicMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDynamicMeshTab)

public:
	CDynamicMeshTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDynamicMeshTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_MESH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

	CMyFormView*		m_pParentForm;
};
