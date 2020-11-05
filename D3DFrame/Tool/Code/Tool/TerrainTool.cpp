// D:\Codes\D3DFrame\Tool\Code\Tool\TerrainTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "../Tool/Code/Tool/TerrainTool.h"
#include "afxdialogex.h"
#include "Cell.h"
#include "Object/ToolTerrain.h"
#include "Object/NaviObject.h"
#include "Object/ToolGuideAxis.h"
// CTerrainTool 대화 상자입니다.
#include "Transform.h"

IMPLEMENT_DYNAMIC(CTerrainTool, CDialogEx)

CTerrainTool::CTerrainTool(CTerrainTab* pParentTab, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TERRAIN_TOOL, pParent)
	, m_pParentTab(pParentTab)
	, m_dwCntX(0)
	, m_dwCntZ(0)
	, m_dwVtxItv(0)
	, m_fDetail(0)
	, m_bActivate(false)
	, m_pTerrain(nullptr)
	, m_fXPos(0)
	, m_fYPos(0)
	, m_fZPos(0)
	, m_wstrFilePath(L"../../Data/Terrain.dat")
	, m_iCntX(0)
	, m_iCntZ(0)
	, m_fDefaultY(0)
{
}

CTerrainTool::~CTerrainTool()
{
}

const float CTerrainTool::Get_DefaultYValue(void) const
{
	return m_fDefaultY;
}

void CTerrainTool::Initialize_MapMeshes(void)
{
	DLL::pDataMgr->Initialize_MapMeshes();
}

void CTerrainTool::Activate(void)
{
	m_bActivate = true;
}

void CTerrainTool::DeActivate(void)
{
	m_bActivate = false;
}

void CTerrainTool::Act(void)
{
	m_pTerrain->KeyInput();
}

void CTerrainTool::Add_List(vector<Engine::CCell*>* pVecCell)
{
	int iCount = 0;
	m_bListBox.ResetContent();
	Engine::_tchar	szName[256]{};

	for (auto iter : *pVecCell)
	{
		swprintf_s(szName, L"%lu", iCount++);

		m_bListBox.AddString(szName);
	}
}

void CTerrainTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_bListBox);
	DDX_Text(pDX, IDC_NAVI_X_POS, m_fXPos);
	DDX_Text(pDX, IDC_NAVI_Y_POS, m_fYPos);
	DDX_Text(pDX, IDC_NAVI_Z_POS, m_fZPos);
	DDX_Text(pDX, IDC_NAVI_DEFAULT_Y_BUTTON, m_fDefaultY);
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialogEx)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_TERRAIN_CONTROL, &CTerrainTool::OnBnClickedTerrainControl)
	ON_BN_CLICKED(IDC_NAVI_CONTROL, &CTerrainTool::OnBnClickedNaviControl)
	ON_BN_CLICKED(IDC_CELL_DELETE, &CTerrainTool::OnBnClickedButton1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NAVI_X_SPIN, &CTerrainTool::OnDeltaposNaviXSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NAVI_Y_SPIN, &CTerrainTool::OnDeltaposNaviYSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NAVI_Z_SPIN, &CTerrainTool::OnDeltaposNaviZSpin)
	ON_BN_CLICKED(IDC_TERRAIN_SAVE, &CTerrainTool::OnBnClickedTerrainSave)
	ON_BN_CLICKED(IDC_TERRAIN_LOAD, &CTerrainTool::OnBnClickedTerrainLoad)
	ON_EN_CHANGE(IDC_TERRAIN_MESH_NAME, &CTerrainTool::OnEnChangeTerrainMeshName)
	ON_LBN_SELCHANGE(IDC_LIST1, &CTerrainTool::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_NAVI_X_POS, &CTerrainTool::OnEnChangeNaviXPos)
	ON_EN_CHANGE(IDC_NAVI_Y_POS, &CTerrainTool::OnEnChangeNaviYPos)
	ON_EN_CHANGE(IDC_NAVI_Z_POS, &CTerrainTool::OnEnChangeNaviZPos)
	ON_EN_CHANGE(IDC_NAVI_DEFAULT_Y_BUTTON, &CTerrainTool::OnEnChangeNaviDefaultYButton)
	ON_BN_CLICKED(IDC_Z_MOVE_0_0_1_RADIO, &CTerrainTool::OnBnClickedZMove001Radio)
	ON_BN_CLICKED(IDC_Z_MOVE_0_1_RADIO, &CTerrainTool::OnBnClickedZMove01Radio)
	ON_BN_CLICKED(IDC_Z_MOVE_1_0_RADIO, &CTerrainTool::OnBnClickedZMove10Radio)
END_MESSAGE_MAP()


// CTerrainTool 메시지 처리기입니다.

void CTerrainTool::OnBnClickedTerrainControl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pTerrain)
	{
		m_pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	}
	m_pTerrain->Change_CtrlTarget(L"NaviCtrl");
}


void CTerrainTool::OnBnClickedNaviControl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pTerrain)
	{
		m_pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	}
	m_pTerrain->Change_CtrlTarget(L"NaviMesh");
}


void CTerrainTool::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iSel = m_bListBox.GetCurSel();
	CString strSelString;
	m_bListBox.GetText(iSel, strSelString);
	Engine::_ulong dwIdx = _ttoi(strSelString);

	m_pTerrain->Delete_Navi(dwIdx);

	vector<Engine::CCell*>* pCell = m_pTerrain->Get_Navi()->Get_Vec();

	m_bListBox.ResetContent();

	int iNum = static_cast<Engine::_int>(pCell->size());
	const int iMaxStr = 256;
	TCHAR szNames[iMaxStr]{};

	for (int i = 0; i < iNum; ++i)
	{
		::ZeroMemory(szNames, iMaxStr);

		swprintf_s(szNames, L"%lu", i);
		m_bListBox.AddString(szNames);
	}
}


void CTerrainTool::OnDeltaposNaviXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f;
	Engine::_vec3	vMove(0.f, 0.f, 0.f);

	vMove.x += (m_fZMove * fMove);

	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();
	if (nullptr != pAxis)
	{
		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Move_Pos(pCenterPos, &vMove);
		m_fXPos = pCenterPos->x;
	}

	UpdateData(FALSE);
}


void CTerrainTool::OnDeltaposNaviYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Engine::_float	fMove = pNMUpDown->iDelta * -1.f;
	Engine::_vec3	vMove(0.f, 0.f, 0.f);

	vMove.y += (m_fZMove * fMove);

	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();
	if (nullptr != pAxis)
	{
		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Move_Pos(pCenterPos, &vMove);
		m_fYPos = pCenterPos->y;
	}

	UpdateData(FALSE);
}


void CTerrainTool::OnDeltaposNaviZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f;
	Engine::_vec3	vMove(0.f, 0.f, 0.f);

	vMove.z += (m_fZMove * fMove);

	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();
	if (nullptr != pAxis)
	{
		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Move_Pos(pCenterPos, &vMove);
		m_fZPos = pCenterPos->z;
	}

	UpdateData(FALSE);
}


void CTerrainTool::OnBnClickedTerrainSave()
{
	CFileDialog Dlg(FALSE, L".navi", L".navi", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Navi Files(*.navi)|*.navi||", this);

	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			CloseHandle(hFile);
			return;
		}

		m_pTerrain->SaveTerrain(hFile);

		CloseHandle(hFile);
	}
}


void CTerrainTool::OnBnClickedTerrainLoad()
{
	CFileDialog Dlg(TRUE, L".navi", L".navi", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Navi Files(*.navi)|*.navi||", this);

	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		if (!m_pTerrain)
		{
			m_pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
		}
		m_pTerrain->LoadData(hFile);
		CloseHandle(hFile);
	}

	m_bListBox.ResetContent();

	TCHAR szItemName[iMaxStr]{};
	if (nullptr == m_pTerrain)
	{
		return;
	}
	const vector<Engine::CCell*>* pVecCell = m_pTerrain->Get_Navi()->Get_Vec();
	int iCount = 0;
	for (auto iter : *pVecCell)
	{
		wsprintf(szItemName, L"%d", iCount++);
		m_bListBox.AddString(szItemName);
	}
}


void CTerrainTool::OnEnChangeTerrainMeshName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	UpdateData(FALSE);
}







void CTerrainTool::OnBnClickedGuidelineCreateButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_pTerrain)
	{
		m_pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	}

	m_pTerrain->Make_Tex(m_iCntX, m_iCntZ);
}


void CTerrainTool::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


}


void CTerrainTool::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CTerrainTool::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTerrainTool::OnEnChangeNaviXPos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();

	if (nullptr != pAxis)
	{
		Engine::_vec3 vMove = *pAxis->Get_CenterPos();
		vMove.x = m_fXPos;

		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Set_Pos(pCenterPos, &vMove);
	}

	UpdateData(FALSE);
}


void CTerrainTool::OnEnChangeNaviYPos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();

	if (nullptr != pAxis)
	{
		Engine::_vec3 vMove = *pAxis->Get_CenterPos();
		vMove.y = m_fYPos;

		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Set_Pos(pCenterPos, &vMove);
	}

}


void CTerrainTool::OnEnChangeNaviZPos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CToolGuideAxis* pAxis = m_pTerrain->Get_ActivatedAxis();

	if (nullptr != pAxis)
	{
		Engine::_vec3 vMove = *pAxis->Get_CenterPos();
		vMove.z = m_fZPos;

		Engine::_vec3* pCenterPos = pAxis->Get_CenterPos();
		m_pTerrain->Get_Navi()->Set_Pos(pCenterPos, &vMove);
	}

}


void CTerrainTool::OnEnChangeNaviDefaultYButton()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CTerrainTool::OnBnClickedZMove001Radio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fZMove = 0.01f;
}


void CTerrainTool::OnBnClickedZMove01Radio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fZMove = 0.1f;
}


void CTerrainTool::OnBnClickedZMove10Radio()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_fZMove = 1.f;
}
