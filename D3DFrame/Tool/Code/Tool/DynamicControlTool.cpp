// D:\Codes\D3DFrame\Tool\Code\Tool\DynamicControlTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "D:\Codes\D3DFrame\Tool\Code\Tool\DynamicControlTool.h"
#include "afxdialogex.h"


// CDynamicControlTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDynamicControlTool, CDialogEx)

CDynamicControlTool::CDynamicControlTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DYNAMIC_CONTROLLER_DIALOG, pParent)
{

}

CDynamicControlTool::~CDynamicControlTool()
{
}

void CDynamicControlTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PREFAB_LIST, m_PrefabList);
}


BEGIN_MESSAGE_MAP(CDynamicControlTool, CDialogEx)
END_MESSAGE_MAP()


// CDynamicControlTool 메시지 처리기입니다.
