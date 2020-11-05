// D:\Codes\D3DFrame\Tool\Code\View\DyMeshTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "View\DynamicObjControlTool.h"

#include "Object\ToolDynamicObject.h"
#include "Object\ToolTerrain.h"
#include "Object\NaviObject.h"

#include "afxdialogex.h"
#include "Transform.h"

// CDyMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDynamicObjTool, CDialogEx)

CDynamicObjTool::CDynamicObjTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DYNAMIC_MONSTER, pParent)
	, m_bIntialized(false)
	, m_bActivated(false)
	, m_pTypeName(_T(""))
	, m_fPosX(0)
	, m_fPosY(0)
	, m_fPosZ(0)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fRotZ(0)
{
}

CDynamicObjTool::~CDynamicObjTool()
{
}

Engine::_bool CDynamicObjTool::Get_Initialized(void) const
{
	return m_bIntialized;
}

Engine::_bool CDynamicObjTool::Get_Activated(void) const
{
	return m_bActivated;
}

void CDynamicObjTool::Activate(void)
{
	m_bActivated = true;


}

void CDynamicObjTool::Deactivate(void)
{
	m_bActivated = false;
}

void CDynamicObjTool::Initialize_DynamicMeshTab(void)
{
	DLL::pToolContainer->Add_Tool(L"MonsterTool", this);

	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto iterPrefabName : *pList)
	{
		m_PrafabComboBox.AddString(iterPrefabName->wStrName.c_str());
	}
}

void CDynamicObjTool::Initialize_DynamicMeshLoad(void)
{
}

void CDynamicObjTool::KeyInput(void)
{
	auto pObj = DLL::pObjMgr->Get_Obj<CToolDynamicObject>(m_pTypeName, m_SelectedStrName);

	if (nullptr == pObj)
	{
		return;
	}

	auto pVector = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Navi()->Get_Vec();

	if (nullptr == pVector)
	{
		return;
	}

	list<Engine::_vec3> cellList;

	Engine::_vec3 vRayPos, vRayDir, vResult, vMousePos;
	Engine::_float fU, fV, fDist;
	Engine::_matrix matView, matProj, matViewInv;

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	DLL::pCalculate->ViewPortToProj(&vMousePos);

	pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	::D3DXMatrixInverse(&matViewInv, nullptr, &matView);

	vRayPos = Engine::_vec3(0.f, 0.f, 0.f);
	vRayDir = vMousePos - vRayPos;

	D3DXVec3TransformCoord(&vRayPos, &vRayPos, &matViewInv);
	D3DXVec3TransformNormal(&vRayDir, &vRayDir, &matViewInv);

	DLL::pCalculate->ProjToView(&vMousePos, &matProj, &vMousePos);
	DLL::pCalculate->ViewToWorld(&vMousePos, &matView, &vMousePos);

	for (auto iter : *pVector)
	{
		if (D3DXIntersectTri(iter->Get_Point(Engine::CCell::POINT::POINT_A),
			iter->Get_Point(Engine::CCell::POINT::POINT_B),
			iter->Get_Point(Engine::CCell::POINT::POINT_C),
			&vRayPos, &vRayDir, &fU, &fV, &fDist))
		{

			vResult = vRayPos + (fDist * vRayDir);

			cellList.push_back(vResult);
		}
	}
	// 정렬해야 함.
	cellList.sort(NAVI_SORT(vMousePos));

	if (cellList.empty())
	{
		return;
	}

	pObj->Set_Pos(&cellList.front());
}

void CDynamicObjTool::reset_List(void)
{
	auto pMap = DLL::pObjMgr->Get_Map(m_pTypeName);

	m_CloneList.ResetContent();

	if (nullptr == pMap)
	{
		return;
	}

	for (auto iter : *pMap)
	{
		m_CloneList.AddString(iter.second->Get_Name());
	}
}

CToolDynamicObject* CDynamicObjTool::get_SelectedObj(void)
{
	return DLL::pObjMgr->Get_Obj<CToolDynamicObject>(m_pTypeName, m_SelectedStrName);
}

void CDynamicObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DYNAMIC_POS_X_EDIT, m_fPosX);
	DDX_Text(pDX, IDC_DYNAMIC_POS_Y_EDIT, m_fPosY);
	DDX_Text(pDX, IDC_DYNAMIC_POS_Z_EDIT, m_fPosZ);
	DDX_Text(pDX, IDC_DYNAMIC_SCALE_EDIT, m_fScaleX);
	DDX_Text(pDX, IDC_DYNAMIC_SCALE_Y_EDIT, m_fScaleY);
	DDX_Text(pDX, IDC_DYNAMIC_SCALE_Z_EDIT, m_fScaleZ);
	DDX_Text(pDX, IDC_DYNAMIC_ROT_X_EDIT, m_fRotX);
	DDX_Text(pDX, IDC_DYNAMIC_ROT_Y_EDIT, m_fRotY);
	DDX_Text(pDX, IDC_DYNAMIC_ROT_Z_EDIT, m_fRotZ);
	DDX_Control(pDX, IDC_COMBO1, m_PrafabComboBox);
	DDX_Control(pDX, IDC_LIST1, m_CloneList);
}


BEGIN_MESSAGE_MAP(CDynamicObjTool, CDialogEx)
	ON_EN_CHANGE(IDC_DYNAMIC_POS_X_EDIT, &CDynamicObjTool::OnEnChangeDynamicPosXEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_POS_X_SPIN, &CDynamicObjTool::OnDeltaposDynamicPosXSpin)

	ON_BN_CLICKED(IDC_GROUP_PLAYER_RADIO, &CDynamicObjTool::OnBnClickedGroupPlayerRadio)
	ON_BN_CLICKED(IDC_GROUP_NPC_RADIO, &CDynamicObjTool::OnBnClickedGroupNpcRadio)
	ON_BN_CLICKED(IDC_GROUP_MONSTER_RADIO, &CDynamicObjTool::OnBnClickedGroupMonsterRadio)

	ON_LBN_SELCHANGE(IDC_LIST1, &CDynamicObjTool::OnLbnSelchangeList1)

	ON_EN_CHANGE(IDC_DYNAMIC_POS_Y_EDIT, &CDynamicObjTool::OnEnChangeDynamicPosYEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_POS_Y_SPIN, &CDynamicObjTool::OnDeltaposDynamicPosYSpin)

	ON_EN_CHANGE(IDC_DYNAMIC_POS_Z_EDIT, &CDynamicObjTool::OnEnChangeDynamicPosZEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_POS_Z_SPIN, &CDynamicObjTool::OnDeltaposDynamicPosZSpin)

	ON_EN_CHANGE(IDC_DYNAMIC_SCALE_EDIT, &CDynamicObjTool::OnEnChangeDynamicScaleEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_SCALE_X_SPIN, &CDynamicObjTool::OnDeltaposDynamicScaleXSpin)
	ON_EN_CHANGE(IDC_DYNAMIC_SCALE_Y_EDIT, &CDynamicObjTool::OnEnChangeDynamicScaleYEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_SCALE_Y_SPIN, &CDynamicObjTool::OnDeltaposDynamicScaleYSpin)
	ON_EN_CHANGE(IDC_DYNAMIC_SCALE_Z_EDIT, &CDynamicObjTool::OnEnChangeDynamicScaleZEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_SCALE_Z_SPIN, &CDynamicObjTool::OnDeltaposDynamicScaleZSpin)

	ON_EN_CHANGE(IDC_DYNAMIC_ROT_X_EDIT, &CDynamicObjTool::OnEnChangeDynamicRotXEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_ROT_X_SPIN, &CDynamicObjTool::OnDeltaposDynamicRotXSpin)
	ON_EN_CHANGE(IDC_DYNAMIC_ROT_Y_EDIT, &CDynamicObjTool::OnEnChangeDynamicRotYEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_ROT_Y_SPIN, &CDynamicObjTool::OnDeltaposDynamicRotYSpin)
	ON_EN_CHANGE(IDC_DYNAMIC_ROT_Z_EDIT, &CDynamicObjTool::OnEnChangeDynamicRotZEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DYNAMIC_ROT_Z_SPIN, &CDynamicObjTool::OnDeltaposDynamicRotZSpin)

	ON_BN_CLICKED(IDC_DYNAMIC_MESH_COUNT_EDIT, &CDynamicObjTool::OnBnClickedCloneButton)
	ON_BN_CLICKED(IDC_DELETE_BUTTON, &CDynamicObjTool::OnBnClickedDeleteButton)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDynamicObjTool::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_DYNAMIC_MESH_SAVE, &CDynamicObjTool::OnBnClickedDynamicMeshSave)
	ON_BN_CLICKED(IDC_DYNAMIC_MESH_LOAD, &CDynamicObjTool::OnBnClickedDynamicMeshLoad)
END_MESSAGE_MAP()


// CDyMeshTab 메시지 처리기입니다.

void CDynamicObjTool::OnEnChangeDynamicPosXEdit()
{
	UpdateData(TRUE);

	// X 위치 이동.
	auto pObj = get_SelectedObj();
	Engine::_vec3 vPos = *pObj->Get_Pos();

	UpdateData(FALSE);
}


void CDynamicObjTool::OnDeltaposDynamicPosXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	UpdateData(FALSE);
}


void CDynamicObjTool::OnBnClickedGroupPlayerRadio()
{
	m_pTypeName = L"Player";
}


void CDynamicObjTool::OnBnClickedGroupNpcRadio()
{
	m_pTypeName = L"NPC";
}


void CDynamicObjTool::OnBnClickedGroupMonsterRadio()
{
	m_pTypeName = L"Monster";
}

void CDynamicObjTool::OnLbnSelchangeList1()
{
	m_CloneList.GetText(m_CloneList.GetCurSel(), m_SelectedStrName);
}

void CDynamicObjTool::OnEnChangeDynamicPosYEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicPosYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicPosZEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CDynamicObjTool::OnDeltaposDynamicPosZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicScaleEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicScaleYEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicScaleZEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicRotXEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicRotXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicRotYEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDynamicObjTool::OnDeltaposDynamicRotYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnEnChangeDynamicRotZEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CDynamicObjTool::OnDeltaposDynamicRotZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

}


void CDynamicObjTool::OnBnClickedCloneButton()
{
	UpdateData(TRUE);

	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Clone(m_strCloneName.GetString()));

	if (nullptr == pObj)
	{
		return;
	}

	pObj->Late_Initialize();

	DLL::pObjMgr->Add_ObjList(m_pTypeName, pObj->Get_Name(), pObj);

	m_CloneList.AddString(pObj->Get_Name());
	reset_List();

	UpdateData(FALSE);
}


void CDynamicObjTool::OnBnClickedDeleteButton()
{
	UpdateData(TRUE);

	DLL::pObjMgr->Delete_Obj(m_pTypeName, m_SelectedStrName);
	reset_List();

	UpdateData(FALSE);
}

void CDynamicObjTool::OnCbnSelchangeCombo1()
{
	int iSel = m_PrafabComboBox.GetCurSel();
	m_PrafabComboBox.GetLBText(iSel, m_strCloneName);
	const map<const Engine::_tchar*, Engine::CGameObject*>* pMap = DLL::pObjMgr->Get_Map(m_pTypeName);

	if (nullptr == pMap)
	{
		return;
	}

	reset_List();

	UpdateData(FALSE);
}


void CDynamicObjTool::OnBnClickedDynamicMeshSave()
{
	HANDLE hFile = nullptr;
	DWORD dwBytes = 0;


	Engine::_vec3 vPos, vAngle;

	const Engine::_tchar* szExtension = L".dynamicObjdat";
	const Engine::_tchar* szType[] = { L"Player", L"Monster", L"NPC" };

	const Engine::_int iSize = sizeof(szType) / sizeof(szType[0]);

	const map<const Engine::_tchar*, Engine::CGameObject*>* pObjMap = nullptr;

	//const Engine::_tchar* szSaveContents[][4] = { { L"BloodElf" },{ L"Doomguard", L"Boar", L"KodoBeast", L"Nefarian" },{ L"zuljin", L"Thrall" } };

	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr]{};
	TCHAR szFileName[iMaxStr]{};

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);

	::PathCombine(szCurrentDir, szCurrentDir, L"Data\\");

	Engine::_int iLen = 0;
	Engine::_int iCount = 0;

	Engine::CTransform* pTransform = nullptr;

	wstring strName;
	for (Engine::_int i = 0; i < iSize; ++i)
	{
		::ZeroMemory(szFileName, sizeof(Engine::_tchar) * iMaxStr);
		wsprintf(szFileName, L"%s%s%s", szCurrentDir, szType[i], szExtension);

		hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			continue;
		}

		pObjMap = DLL::pObjMgr->Get_Map(szType[i]);

		if (pObjMap == nullptr)
		{
			CloseHandle(hFile);

			continue;
		}

		for (auto iter : *pObjMap)
		{
			strName = dynamic_cast<CToolDynamicObject*>(iter.second)->Get_RenderKey();

			iLen = static_cast<Engine::_int>(strName.length());
			WriteFile(hFile, &iLen, sizeof(Engine::_int), &dwBytes, NULL);
			WriteFile(hFile, strName.c_str(), sizeof(Engine::_tchar) * iLen, &dwBytes, NULL);

			pTransform = iter.second->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);

			WriteFile(hFile, pTransform->Get_Info(Engine::INFO_POS), sizeof(Engine::_vec3), &dwBytes, NULL);
			WriteFile(hFile, pTransform->Get_Angle(), sizeof(Engine::_vec3), &dwBytes, NULL);

			iCount++;
		}

		CloseHandle(hFile);
	}

	MessageBox(L"../../Data/를 확인하세요.");
}


void CDynamicObjTool::OnBnClickedDynamicMeshLoad()
{
	Engine::_vec3 vPos, vAngle;

	HANDLE hFile = nullptr;
	DWORD dwBytes = 0;

	Engine::CTransform* pTransform = nullptr;

	const int iMaxStr = 256;
	Engine::_int iNameSize;
	TCHAR szNames[iMaxStr]{};

	CToolDynamicObject* pObj = nullptr;

	CFileDialog Dlg(TRUE, L".dynamicObjdat", L".dynamicObjdat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Dynamic Object Data Files(*.dynamicObjdat)|*.dynamicObjdat||", this);

	TCHAR szCurrentDir[iMaxStr]{};

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	wstring wstrType;

	if (IDOK == Dlg.DoModal())
	{
		hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		while (true)
		{
			::ZeroMemory(szNames, sizeof(TCHAR) * iMaxStr);
			ReadFile(hFile, &iNameSize, sizeof(Engine::_int), &dwBytes, NULL);
			ReadFile(hFile, szNames, sizeof(TCHAR) * iNameSize, &dwBytes, NULL);

			ReadFile(hFile, &vPos, sizeof(Engine::_vec3), &dwBytes, NULL);

			if (0 == dwBytes)
			{
				break;
			}

			ReadFile(hFile, &vAngle, sizeof(Engine::_vec3), &dwBytes, NULL);

			pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Clone(szNames));
			pObj->Late_Initialize();
			DLL::pObjMgr->Add_ObjList(pObj->Get_RenderKey().c_str(), pObj->Get_Name(), pObj);

			pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
			pTransform->Set_Info(Engine::INFO::INFO_POS, &vPos);
			pTransform->Set_Angle(&vAngle);
		}

		CloseHandle(hFile);
	}
}
