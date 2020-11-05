// BackgroundObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BackgroundObjectTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "../D2DDungreed/Object/MoveBackgroundObject/MoveBackgroundObject.h"

// CBackgroundObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBackgroundObjectTool, CDialog)

CBackgroundObjectTool::CBackgroundObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
	, m_fZValue(0)
	, m_strObjStatus(_T(""))
	, m_strObjKey(_T(""))
	, m_strName(_T(""))
	, m_fMaxAnimationCount(0.f)
	, m_fSpeed(0)
	, m_fXSize(0)
	, m_fYSize(0)
{

}

CBackgroundObjectTool::~CBackgroundObjectTool()
{
	std::for_each(m_vecObject.begin(), m_vecObject.end(), SafeDelete<CMoveBackgroundObject*>);
	m_vecObject.clear();
}

void CBackgroundObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ANIMATION_EDIT, m_fMaxAnimationCount);
	DDX_Text(pDX, IDC_SPEED_EDIT, m_fSpeed);
	DDX_Text(pDX, IDC_X_SIZE_EDIT, m_fXSize);
	DDX_Text(pDX, IDC_Y_SIZE_EDIT, m_fYSize);
	DDX_Text(pDX, IDC_Z_VALUE_EDIT, m_fZValue);
	DDX_Text(pDX, IDC_OBJ_STATUS_EDIT, m_strObjStatus);
	DDX_Text(pDX, IDC_OBJ_KEY_EDIT, m_strObjKey);
	DDX_Text(pDX, IDC_NAME_EDIT, m_strName);
	DDX_Control(pDX, IDC_OBJ_TOOL_LIST, m_List);
}

void CBackgroundObjectTool::SettingHorizontalScrollSize()
{
	CString	strName = L"";

	int iSrcCx = 0, iDstCX = 0;

	CDC* pDC = m_List.GetDC();

	int iListCount = m_List.GetCount();

	for (int i = 0; i < iListCount; ++i)
	{
		m_List.GetText(i, strName);

		iSrcCx = pDC->GetTextExtent(strName).cx;

		if (iDstCX < iSrcCx)
		{
			iDstCX = iSrcCx;
		}
	}

	m_List.ReleaseDC(pDC);

	if (iDstCX > m_List.GetHorizontalExtent())
	{
		m_List.SetHorizontalExtent(iDstCX);
	}
}


BEGIN_MESSAGE_MAP(CBackgroundObjectTool, CDialog)
	ON_LBN_SELCHANGE(IDC_OBJ_TOOL_LIST, &CBackgroundObjectTool::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CBackgroundObjectTool::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_PUSH_BUTTON, &CBackgroundObjectTool::OnBnClickedPushButton)
	ON_BN_CLICKED(IDC_OBJ_SAVE_BUTTON, &CBackgroundObjectTool::OnBnClickedObjSaveButton)
	ON_BN_CLICKED(IDC_OBJ_LOAD_BUTTON, &CBackgroundObjectTool::OnBnClickedObjLoadButton)
	ON_BN_CLICKED(IDC_OBJECT_RADIO, &CBackgroundObjectTool::OnBnClickedObjectRadio)
	ON_BN_CLICKED(IDC_FRONT_OBJ_RADIO, &CBackgroundObjectTool::OnBnClickedFrontObjRadio)
END_MESSAGE_MAP()


// CBackgroundObjectTool 메시지 처리기입니다.


void CBackgroundObjectTool::OnDropFiles(HDROP hDropInfo)
{
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

		m_List.AddString(szFileName);
	}

	SettingHorizontalScrollSize();
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CBackgroundObjectTool::OnLbnSelchangeList1()
{
	int iIndex = m_List.GetCurSel();

	if (-1 == iIndex)
	{
		return;
	}

	CString strName = L"";
	m_List.GetText(iIndex, strName);

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CToolView* pView = dynamic_cast<CToolView*>(pFrameWnd->m_MainSplitter.GetPane(0, 1));
	NULL_CHECK(pView);

	// 타일 미리보기 출력
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(pView->m_pTerrain->GetObjectKey(), pView->m_pTerrain->GetObjectStatus());
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
}

void CBackgroundObjectTool::OnBnClickedDeleteButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iIndex = m_List.GetCurSel();

	if (-1 == iIndex)
	{
		return;
	}

	//auto iter = std::find(m_vecObject.begin(), m_vecObject.end(), iIndex);

	SafeDelete(m_vecObject[iIndex]);
	m_vecObject.erase(m_vecObject.begin() + iIndex);
}


void CBackgroundObjectTool::OnBnClickedPushButton()
{
	UpdateData(TRUE);

	if (
		m_strName.GetLength() == 0				||
		m_strObjKey.GetLength() == 0			||
		m_strObjStatus.GetLength() == 0			||
		(0.f > m_fZValue && m_fZValue < 1.f)	||
		(0.f > m_fMaxAnimationCount)			||
		m_eObjType == OBJECT_TYPE::OBJECT_END
		)
	{
		return;
	}

	m_pObject = CMoveBackgroundObject::Create
	(
		m_strObjKey.GetString(),
		m_strObjStatus.GetString(),
		static_cast<WORD>(m_fMaxAnimationCount),
		D3DXVECTOR3(0.f, 0.f, m_fZValue),
		D3DXVECTOR3(1.f, 1.f, 0.f),
		m_fSpeed
	);

	m_pObject->SetObjType(m_eObjType);

	m_vecObject.push_back(m_pObject);

	m_List.AddString(m_strName);

	UpdateData(FALSE);
}

void CBackgroundObjectTool::OnBnClickedObjSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBackgroundObjectTool::OnBnClickedObjLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBackgroundObjectTool::OnBnClickedObjectRadio()
{
	m_eObjType = OBJECT_TYPE::OBJECT_OBJECT;
}


void CBackgroundObjectTool::OnBnClickedFrontObjRadio()
{
	m_eObjType = OBJECT_TYPE::OBJECT_FRONT_OBJECT;
}