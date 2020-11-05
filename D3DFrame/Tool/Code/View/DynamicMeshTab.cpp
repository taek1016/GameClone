// D:\Codes\D3DFrame\Tool\Code\View\EventTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Tool/Code/View/DynamicMeshTab.h"
#include "../Tool/Code/View/MyFormView.h"
#include "afxdialogex.h"


// CEventTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDynamicMeshTab, CDialogEx)

CDynamicMeshTab::CDynamicMeshTab(CMyFormView* pParentForm, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DYNAMIC_MESH_DLG, pParent)
	, m_pParentForm(pParentForm)
{

}

CDynamicMeshTab::~CDynamicMeshTab()
{
	m_pParentForm = nullptr;
}

void CDynamicMeshTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDynamicMeshTab, CDialogEx)
END_MESSAGE_MAP()


// CEventTab 메시지 처리기입니다.
