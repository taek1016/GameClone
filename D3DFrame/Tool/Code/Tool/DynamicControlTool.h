#pragma once
#include "afxwin.h"


// CDynamicControlTool ��ȭ �����Դϴ�.

class CDynamicControlTool : public CDialogEx
{
	DECLARE_DYNAMIC(CDynamicControlTool)

public:
	CDynamicControlTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDynamicControlTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMIC_CONTROLLER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	CListBox m_PrefabList;
};
