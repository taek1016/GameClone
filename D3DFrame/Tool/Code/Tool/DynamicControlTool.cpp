// D:\Codes\D3DFrame\Tool\Code\Tool\DynamicControlTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "D:\Codes\D3DFrame\Tool\Code\Tool\DynamicControlTool.h"
#include "afxdialogex.h"


// CDynamicControlTool ��ȭ �����Դϴ�.

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


// CDynamicControlTool �޽��� ó�����Դϴ�.
