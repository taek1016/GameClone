// Map_Tool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Map_Tool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"

// CMap_Tool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMap_Tool, CDialog)

CMap_Tool::CMap_Tool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAP_TOOL, pParent)
	, m_iDrawID(0)
	, m_strObjKey(_T(""))
	, m_strObjStatus(_T(""))
{

}

CMap_Tool::~CMap_Tool()
{
}

void CMap_Tool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAP_LIST, m_ListBox);
	DDX_Control(pDX, IDC_MAP_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_OBJECT_KEY_EDIT, m_strObjKey);
	DDX_Text(pDX, IDC_OBJECT_STATUS_EDIT, m_strObjStatus);
}



BEGIN_MESSAGE_MAP(CMap_Tool, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_MAP_SAVE_BUTTON2, &CMap_Tool::OnBnClickedMapSaveButton2)
	ON_BN_CLICKED(IDC_MAP_LOAD_BUTTON, &CMap_Tool::OnBnClickedMapLoadButton)
	ON_LBN_SELCHANGE(IDC_MAP_LIST, &CMap_Tool::OnLbnSelchangeMapList)
END_MESSAGE_MAP()


// CMap_Tool 메시지 처리기입니다.


void CMap_Tool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	TCHAR	szFileName[MAX_STR]{};
	int iCount = ::DragQueryFile(hDropInfo, -1, nullptr, 0);

	CString strRelative = L"";
	CString strFileName = L"";
	
	UpdateData(TRUE);

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	pView->m_pTerrain->SetObjectKey(m_strObjKey.GetString());
	pView->m_pTerrain->SetObjectStatus(m_strObjStatus.GetString());

	for (int i = 0; i < iCount; ++i)
	{
		::DragQueryFile(hDropInfo, i, szFileName, MAX_STR);

		strFileName = ::PathFindFileName(szFileName);

		lstrcpy(szFileName, strFileName);
		::PathRemoveExtension(szFileName);

		m_ListBox.AddString(szFileName);
	}

	SettingHorizontalScrollSize();
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CMap_Tool::SettingHorizontalScrollSize()
{
	CString	strName = L"";

	int iSrcCx = 0, iDstCX = 0;
	
	CDC* pDC = m_ListBox.GetDC();

	int iListCount = m_ListBox.GetCount();

	for (int i = 0; i < iListCount; ++i)
	{
		m_ListBox.GetText(i, strName);

		iSrcCx = pDC->GetTextExtent(strName).cx;

		if (iDstCX < iSrcCx)
		{
			iDstCX = iSrcCx;
		}
	}

	m_ListBox.ReleaseDC(pDC);

	if (iDstCX > m_ListBox.GetHorizontalExtent())
	{
		m_ListBox.SetHorizontalExtent(iDstCX);
	}
}

void CMap_Tool::OnBnClickedMapSaveButton2()
{
	CFileDialog Dlg(FALSE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	UpdateData(TRUE);
	if (IDOK == Dlg.DoModal())
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pView);

		NULL_CHECK(pView->m_pTerrain);

		pView->m_pTerrain->SetObjectKey(m_strObjKey.GetString());
		pView->m_pTerrain->SetObjectStatus(m_strObjStatus.GetString());

		pView->m_pTerrain->SaveTile(Dlg.GetPathName());
	}
	UpdateData(FALSE);
}

void CMap_Tool::OnBnClickedMapLoadButton()
{
	CFileDialog Dlg(TRUE, L".dat", L"제목 없음.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat|Text Files(*.txt)|*.txt||", this);

	TCHAR szCurrentDir[MAX_STR] = L"";

	::GetCurrentDirectory(MAX_STR, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
		NULL_CHECK(pView);

		NULL_CHECK(pView->m_pTerrain);
		pView->m_pTerrain->LoadTile(Dlg.GetPathName());
		pView->Invalidate(FALSE);
	}
}

void CMap_Tool::OnLbnSelchangeMapList()
{
	int iIndex = m_ListBox.GetCurSel();

	if (-1 == iIndex)
	{
		return;
	}

	CString strName = L"";
	m_ListBox.GetText(iIndex, strName);

	int i = 0;
	for (; i < strName.GetLength(); ++i)
	{
		if (isdigit(strName[i]))
		{
			break;
		}
	}

	strName.Delete(0, i);

	m_iDrawID = _ttoi(strName);

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	// 타일 미리보기 출력
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(pView->m_pTerrain->GetObjectKey(), pView->m_pTerrain->GetObjectStatus(), m_iDrawID);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width TO_HALF;
	float fCenterY = pTexInfo->tImgInfo.Height TO_HALF;

	D3DXMATRIX matScale, matTrans, matWorld;

	D3DXMatrixScaling(
		&matScale,
		static_cast<float>(CSINGLETON::GetWidth() / pTexInfo->tImgInfo.Width / 2.5f),
		static_cast<float>(CSINGLETON::GetHeight() / pTexInfo->tImgInfo.Height / 2.5f),
		0.f);

	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale * matTrans;

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&matWorld);

	CSINGLETON::pDirectMgr->Render_Begin();

	CSINGLETON::pDirectMgr->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	CSINGLETON::pDirectMgr->Render_End(m_Picture.m_hWnd);
}
