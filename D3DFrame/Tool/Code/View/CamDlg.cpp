// D:\Codes\D3DFrame\Tool\Code\View\CamDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Tool/Code/View/CamDlg.h"
#include "afxdialogex.h"


// CCamDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCamDlg, CDialogEx)

CCamDlg::CCamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAM_DLG, pParent)
{

}

CCamDlg::~CCamDlg()
{
}

void CCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCamDlg, CDialogEx)
END_MESSAGE_MAP()


// CCamDlg 메시지 처리기입니다.
