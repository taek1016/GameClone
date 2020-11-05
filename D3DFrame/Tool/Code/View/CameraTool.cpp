// D:\Codes\D3DFrame\Tool\Code\View\CameraTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "D:\Codes\D3DFrame\Tool\Code\View\CameraTool.h"
#include "afxdialogex.h"


// CCamPathDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCamPathDlg, CDialogEx)

CCamPathDlg::CCamPathDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERA_DLG, pParent)
{

}

CCamPathDlg::~CCamPathDlg()
{
}

void CCamPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCamPathDlg, CDialogEx)
END_MESSAGE_MAP()


// CCameraTool 메시지 처리기입니다.
