#pragma once


// CEventTab 대화 상자입니다.
class CMyFormView;
class CDynamicMeshTab : public CDialogEx
{
	DECLARE_DYNAMIC(CDynamicMeshTab)

public:
	CDynamicMeshTab(CMyFormView* pParentForm, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDynamicMeshTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_MESH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	CMyFormView*		m_pParentForm;
};
