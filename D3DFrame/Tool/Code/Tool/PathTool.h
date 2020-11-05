#pragma once


// CPathTool ��ȭ �����Դϴ�.

class CPathTool : public CDialogEx
{
	DECLARE_DYNAMIC(CPathTool)

public:
	CPathTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPathTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATH_DLG };
#endif
	void			Renew_Data(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
private:
	int m_iStaticMeshCount;
	int m_iDynamicMeshCount;
	int m_iTextureCount;

public:
	afx_msg void OnBnClickedPathSaveButton();
	afx_msg void OnBnClickedCountSaveButton();
	afx_msg void OnEnChangeStaticMeshCountEdit();
	afx_msg void OnEnChangeDynamicMeshCountEdit();
	afx_msg void OnEnChangeTextureCountEdit();
};
