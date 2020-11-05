#pragma once


// CPathTool 대화 상자입니다.

class CPathTool : public CDialogEx
{
	DECLARE_DYNAMIC(CPathTool)

public:
	CPathTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPathTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATH_DLG };
#endif
	void			Renew_Data(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
