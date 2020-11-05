#pragma once
#include "afxwin.h"


// CDynamicControlTool 대화 상자입니다.

class CDynamicControlTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDynamicControlTool)

public:
	CDynamicControlTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDynamicControlTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_CONTROLLER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_PrefabList;
};
