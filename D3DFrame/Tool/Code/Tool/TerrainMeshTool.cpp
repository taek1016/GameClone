// D:\Codes\D3DFrame\Tool\Code\Tool\TerrainMeshTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Tool\TerrainMeshTool.h"
#include "afxdialogex.h"
#include "Transform.h"

#include "Object/ToolTerrain.h"

// CTerrainMeshTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTerrainMeshTool, CDialogEx)

CTerrainMeshTool::CTerrainMeshTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TERRAIN_MESH_DLG, pParent)
	, m_TerrainMeshName(_T(""))
	, m_fPosX(0)
	, m_fPosY(0)
	, m_fPosZ(0)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_fAngleX(0)
	, m_fAngleY(0)
	, m_fAngleZ(0)

{

}

CTerrainMeshTool::~CTerrainMeshTool()
{
}

void CTerrainMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TERRAIN_MESH_NAME, m_TerrainMeshName);
	DDX_Text(pDX, IDC_TERRAIN_POS_X, m_fPosX);
	DDX_Text(pDX, IDC_TERRAIN_POS_Y, m_fPosY);
	DDX_Text(pDX, IDC_TERRAIN_POS_Z, m_fPosZ);
	DDX_Text(pDX, IDC_TERRAIN_SCALE_X, m_fScaleX);
	DDX_Text(pDX, IDC_TERRAIN_SCALE_Y, m_fScaleY);
	DDX_Text(pDX, IDC_TERRAIN_SCALE_Z, m_fScaleZ);
	DDX_Text(pDX, IDC_TERRAIN_ANGLE_X, m_fAngleX);
	DDX_Text(pDX, IDC_TERRAIN_ANGLE_Y, m_fAngleY);
	DDX_Text(pDX, IDC_TERRAIN_ANGLE_Z, m_fAngleZ);
}


BEGIN_MESSAGE_MAP(CTerrainMeshTool, CDialogEx)
	ON_EN_CHANGE(IDC_TERRAIN_POS_X, &CTerrainMeshTool::OnEnChangeTerrainPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_POS_X_SPIN, &CTerrainMeshTool::OnDeltaposTerrainPosXSpin)
	ON_EN_CHANGE(IDC_TERRAIN_POS_Y, &CTerrainMeshTool::OnEnChangeTerrainPosY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_POS_Y_SPIN, &CTerrainMeshTool::OnDeltaposTerrainPosYSpin)
	ON_EN_CHANGE(IDC_TERRAIN_POS_Z, &CTerrainMeshTool::OnEnChangeTerrainPosZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_POS_Z_SPIN, &CTerrainMeshTool::OnDeltaposTerrainPosZSpin)
	ON_EN_CHANGE(IDC_TERRAIN_SCALE_X, &CTerrainMeshTool::OnEnChangeTerrainScaleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_SCALE_X_SPIN, &CTerrainMeshTool::OnDeltaposTerrainScaleXSpin)
	ON_EN_CHANGE(IDC_TERRAIN_SCALE_Y, &CTerrainMeshTool::OnEnChangeTerrainScaleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_SCALE_Y_SPIN, &CTerrainMeshTool::OnDeltaposTerrainScaleYSpin)
	ON_EN_CHANGE(IDC_TERRAIN_SCALE_Z, &CTerrainMeshTool::OnEnChangeTerrainScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_SCALE_Z_SPIN, &CTerrainMeshTool::OnDeltaposTerrainScaleZSpin)
	ON_EN_CHANGE(IDC_TERRAIN_ANGLE_X, &CTerrainMeshTool::OnEnChangeTerrainAngleX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_ANGLE_X_SPIN7, &CTerrainMeshTool::OnDeltaposTerrainAngleXSpin7)
	ON_EN_CHANGE(IDC_TERRAIN_ANGLE_Y, &CTerrainMeshTool::OnEnChangeTerrainAngleY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_ANGLE_Y_SPIN8, &CTerrainMeshTool::OnDeltaposTerrainAngleYSpin8)
	ON_EN_CHANGE(IDC_TERRAIN_ANGLE_Z, &CTerrainMeshTool::OnEnChangeTerrainAngleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TERRAIN_ANGLE_Z_SPIN, &CTerrainMeshTool::OnDeltaposTerrainAngleZSpin)
	ON_BN_CLICKED(IDC_TERRAIN_MESH_CLONE, &CTerrainMeshTool::OnBnClickedTerrainMeshClone)
	ON_EN_CHANGE(IDC_TERRAIN_MESH_NAME, &CTerrainMeshTool::OnEnChangeTerrainMeshName)
	ON_BN_CLICKED(IDC_TERRAIN_SAVE_BUTTON, &CTerrainMeshTool::OnBnClickedTerrainSaveButton)
	ON_BN_CLICKED(IDC_TERRAIN_LOAD_BUTTON, &CTerrainMeshTool::OnBnClickedTerrainLoadButton)
END_MESSAGE_MAP()


// CTerrainMeshTool 메시지 처리기입니다.

void CTerrainMeshTool::OnEnChangeTerrainPosX()
{
	UpdateData(TRUE);

	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vPos = *pTransform->Get_Info(Engine::INFO::INFO_POS);
	vPos.x = m_fPosX;
	pTransform->Set_Info(Engine::INFO::INFO_POS, &vPos);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainPosXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Info(Engine::INFO::INFO_POS);

	vMove.x += fMove;
	m_fPosX = vMove.x;

	pTransform->Set_Info(Engine::INFO::INFO_POS, &vMove);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainPosY()
{
	UpdateData(TRUE);
	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vPos = *pTransform->Get_Info(Engine::INFO::INFO_POS);
	vPos.y = m_fPosY;
	pTransform->Set_Info(Engine::INFO::INFO_POS, &vPos);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainPosYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Info(Engine::INFO::INFO_POS);

	vMove.y += fMove;
	m_fPosY = vMove.y;

	pTransform->Set_Info(Engine::INFO::INFO_POS, &vMove);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainPosZ()
{
	UpdateData(TRUE);
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vPos = *pTransform->Get_Info(Engine::INFO::INFO_POS);
	vPos.z = m_fPosZ;
	pTransform->Set_Info(Engine::INFO::INFO_POS, &vPos);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainPosZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Info(Engine::INFO::INFO_POS);

	vMove.z += fMove;
	m_fPosZ = vMove.z;
	pTransform->Set_Info(Engine::INFO::INFO_POS, &vMove);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainScaleX()
{
	UpdateData(TRUE);
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.x = m_fScaleX;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Scale();

	vMove.x += fMove;
	m_fScaleX = vMove.x;
	pTransform->Set_Scale(&vMove);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainScaleY()
{
	UpdateData(TRUE);
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.y = m_fScaleY;
	pTransform->Set_Scale(&vScale);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Scale();

	vMove.y += fMove;
	m_fScaleY = vMove.y;
	pTransform->Set_Scale(&vMove);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainScaleZ()
{
	UpdateData(TRUE);

	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.z = m_fScaleZ;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Scale();

	vMove.z += fMove;
	m_fScaleZ = vMove.z;
	pTransform->Set_Scale(&vMove);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainAngleX()
{
	UpdateData(TRUE);

	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vAngle = *pTransform->Get_Angle();
	vAngle.x = m_fAngleX;
	pTransform->Set_Angle(&vAngle);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainAngleXSpin7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Angle();

	vMove.x += fMove;
	m_fAngleX = vMove.x;
	pTransform->Set_Angle(&vMove);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainAngleY()
{
	UpdateData(TRUE);

	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vAngle = *pTransform->Get_Angle();
	vAngle.y = m_fAngleY;
	pTransform->Set_Angle(&vAngle);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainAngleYSpin8(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Angle();

	vMove.y += fMove;
	m_fAngleY = vMove.y;
	pTransform->Set_Angle(&vMove);
	UpdateData(FALSE);
}


void CTerrainMeshTool::OnEnChangeTerrainAngleZ()
{
	UpdateData(TRUE);

	auto pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);
	Engine::_vec3 vAngle = *pTransform->Get_Angle();
	vAngle.z = m_fAngleZ;
	pTransform->Set_Angle(&vAngle);

	UpdateData(FALSE);
}


void CTerrainMeshTool::OnDeltaposTerrainAngleZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	Engine::CTransform* pTransform = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain")->Get_Component<Engine::CTransform>(L"Transform", Engine::COMPONENTID::ID_DYNAMIC);

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;
	Engine::_vec3	vMove = *pTransform->Get_Angle();

	vMove.z += fMove;
	m_fAngleZ = vMove.z;
	pTransform->Set_Angle(&vMove);

	UpdateData(FALSE);
}

void CTerrainMeshTool::OnBnClickedTerrainMeshClone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolTerrain* pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
	pTerrain->Make_TerrainMesh(m_TerrainMeshName.GetString());
}

void CTerrainMeshTool::OnEnChangeTerrainMeshName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}


void CTerrainMeshTool::OnBnClickedTerrainSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L".terrain", L".terrain", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Terrain Files(*.terrain)|*.terrain||", this);

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

		DWORD dwBytes = 0;
		CToolTerrain* pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
		const wstring& tempStr = pTerrain->Get_RenderKey();

		Engine::CTransform* pTransform = pTerrain->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);

		// 이름 출력
		Engine::_int iSize = static_cast<Engine::_int>(tempStr.size());
		WriteFile(hFile, &iSize, static_cast<DWORD>(sizeof(Engine::_int)), &dwBytes, NULL);
		WriteFile(hFile, tempStr.c_str(), static_cast<DWORD>(sizeof(TCHAR) * tempStr.size()), &dwBytes, NULL);

		// 정보 출력
		WriteFile(hFile, pTransform->Get_Info(Engine::INFO::INFO_POS), sizeof(Engine::_vec3), &dwBytes, NULL);
		WriteFile(hFile, pTransform->Get_Scale(), sizeof(Engine::_vec3), &dwBytes, NULL);
		WriteFile(hFile, pTransform->Get_Angle(), sizeof(Engine::_vec3), &dwBytes, NULL);

		CloseHandle(hFile);
	}
}


void CTerrainMeshTool::OnBnClickedTerrainLoadButton()
{
	CFileDialog Dlg(TRUE, L".terrain", L".terrain", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Terrain Files(*.terrain)|*.terrain||", this);

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

		DWORD dwBytes = 0;
		CToolTerrain* pTerrain = DLL::pObjMgr->Get_Obj<CToolTerrain>(L"Terrain", L"Terrain");
		const wstring& tempStr = pTerrain->Get_RenderKey();

		Engine::CTransform* pTransform = pTerrain->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);

		// 이름 출력

		const int iMaxStr = 256;
		TCHAR szName[iMaxStr]{};

		Engine::_int iSize = static_cast<Engine::_int>(tempStr.size());
		ReadFile(hFile, &iSize, sizeof(Engine::_int), &dwBytes, NULL);

		ReadFile(hFile, szName, sizeof(TCHAR) * iSize, &dwBytes, NULL);

		pTerrain->Make_TerrainMesh(szName);
		m_TerrainMeshName = szName;

		Engine::_vec3 vData;
		// 정보 출력
		ReadFile(hFile, &vData, sizeof(Engine::_vec3), &dwBytes, NULL);
		pTransform->Set_Info(Engine::INFO::INFO_POS, &vData);
		m_fPosX = vData.x;
		m_fPosY = vData.y;
		m_fPosZ = vData.z;

		ReadFile(hFile, &vData, sizeof(Engine::_vec3), &dwBytes, NULL);
		pTransform->Set_Scale(&vData);
		m_fScaleX = vData.x;
		m_fScaleY = vData.y;
		m_fScaleZ = vData.z;

		ReadFile(hFile, &vData, sizeof(Engine::_vec3), &dwBytes, NULL);
		pTransform->Set_Angle(&vData);
		m_fAngleX = vData.x;
		m_fAngleY = vData.y;
		m_fAngleZ = vData.z;

		CloseHandle(hFile);
	}
	UpdateData(FALSE);
}
