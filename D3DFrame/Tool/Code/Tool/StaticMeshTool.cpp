// D:\Codes\D3DFrame\Tool\Code\View\StaticMeshTab.cpp : 구현 파일입니다.
//


#include "stdafx.h"
#include "Tool.h"
#include "StaticMeshTool.h"
#include "afxdialogex.h"

#include "Object/ToolStaticObject.h"
#include "Object/ToolStaticObjectCtrl.h"
#include "ActionComponent.h"
#include "Sphere.h"
#include "Transform.h"
// CStaticMeshTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStaticMeshTool, CDialogEx)

CStaticMeshTool::CStaticMeshTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STATIC_MESH_DLG, pParent)
	, m_bActivated(false)
	, m_strKey(_T(""))
	, m_pStaticMeshCtrl(nullptr)
	, m_fPosX(0)
	, m_fPosY(0)
	, m_fPosZ(0)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fRotZ(0)
	, m_fRadius(0)
{

}

CStaticMeshTool::~CStaticMeshTool()
{
	Engine::Safe_Release(m_pStaticMeshCtrl);

	for (auto iter : m_LoadNameList)
	{
		Engine::Safe_Delete_Array(iter);
	}
	m_LoadNameList.clear();
}

void CStaticMeshTool::Activate(void)
{
	m_bActivated = true;

	m_TreeCtrl.DeleteAllItems();

	auto pMap = DLL::pObjMgr->Get_PrefabMap();

	HTREEITEM hParentItem;

	const map<const Engine::_tchar*, Engine::CGameObject*>* pObjects = nullptr;
	for (auto iterList : *pMap)
	{
		hParentItem = m_TreeCtrl.InsertItem(iterList.second->Get_Name());

		pObjects = DLL::pObjMgr->Get_Map(iterList.second->Get_Name());

		if (nullptr == pObjects)
		{
			continue;
		}

		for (auto iter : *pObjects)
		{
			m_TreeCtrl.InsertItem(iter.second->Get_Name(), hParentItem, hParentItem);
		}
	}
}

void CStaticMeshTool::DeActivate(void)
{
	m_bActivated = false;
}

Engine::_bool CStaticMeshTool::GetActivated(void) const
{
	return m_bActivated;
}

void CStaticMeshTool::KeyInput(void)
{
	m_pStaticMeshCtrl->KeyInput();
}

void CStaticMeshTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_STATIC_OBJ, m_TreeCtrl);
	DDX_Text(pDX, IDC_STATIC_MESH_POS_X, m_fPosX);
	DDX_Text(pDX, IDC_STATIC_MESH_POS_Y_EDIT, m_fPosY);
	DDX_Text(pDX, IDC_STATIC_MESH_POS_Z_EDIT, m_fPosZ);
	DDX_Text(pDX, IDC_STATIC_MESH_SCALE_POS_X, m_fScaleX);
	DDX_Text(pDX, IDC_STATIC_MESH_POS_Y_SCALE, m_fScaleY);
	DDX_Text(pDX, IDC_STATIC_MESH_SCALE_Z, m_fScaleZ);
	DDX_Text(pDX, IDC_STATIC_MESH_LOOK_X, m_fRotX);
	DDX_Text(pDX, IDC_STATIC_MESH_LOOK_Y, m_fRotY);
	DDX_Text(pDX, IDC_STATIC_MESH_LOOK_Z, m_fRotZ);
	DDX_Text(pDX, IDC_STATIC_SPHERE_RADIUS_EDIT, m_fRadius);
}

CToolStaticObject * CStaticMeshTool::get_SelectedObj(void)
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);

	const Engine::_int iMaxStr = 256;
	TCHAR szParent[iMaxStr]{};
	TCHAR szItemName[iMaxStr]{};

	wsprintf(szParent, L"%s", m_TreeCtrl.GetItemText(hParentItem));
	wsprintf(szItemName, L"%s", m_TreeCtrl.GetItemText(hItem));

	return DLL::pObjMgr->Get_Obj<CToolStaticObject>(szParent, szItemName);
}


BEGIN_MESSAGE_MAP(CStaticMeshTool, CDialogEx)
	ON_EN_CHANGE(IDC_STATIC_MESH_POS_X, &CStaticMeshTool::OnEnChangeStaticMeshPosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_POS_X_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshPosXSpin)
	ON_EN_CHANGE(IDC_STATIC_MESH_POS_Y_EDIT, &CStaticMeshTool::OnEnChangeStaticMeshPosYEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_Y_POS_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshYPosSpin)
	ON_EN_CHANGE(IDC_STATIC_MESH_POS_Z_EDIT, &CStaticMeshTool::OnEnChangeStaticMeshPosZEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_Z_POS_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshZPosSpin)

	ON_EN_CHANGE(IDC_STATIC_MESH_SCALE_POS_X, &CStaticMeshTool::OnEnChangeStaticMeshScalePosX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_SCALE_X_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshScaleXSpin)
	ON_EN_CHANGE(IDC_STATIC_MESH_POS_Y_SCALE, &CStaticMeshTool::OnEnChangeStaticMeshPosYScale)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_SCALE_Y_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshScaleYSpin)
	ON_EN_CHANGE(IDC_STATIC_MESH_SCALE_Z, &CStaticMeshTool::OnEnChangeStaticMeshScaleZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_SPIN_Z, &CStaticMeshTool::OnDeltaposStaticMeshScaleSpinZ)

	ON_EN_CHANGE(IDC_STATIC_MESH_LOOK_X, &CStaticMeshTool::OnEnChangeStaticMeshRotX)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_SPIN_X, &CStaticMeshTool::OnDeltaposStaticMeshRotSpinX)
	ON_EN_CHANGE(IDC_STATIC_MESH_LOOK_Y, &CStaticMeshTool::OnEnChangeStaticMeshRotY)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_SPIN_Y, &CStaticMeshTool::OnDeltaposStaticMeshRotSpinY)
	ON_EN_CHANGE(IDC_STATIC_MESH_LOOK_Z, &CStaticMeshTool::OnEnChangeStaticMeshRotZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_MESH_LOOK_Z_SPIN, &CStaticMeshTool::OnDeltaposStaticMeshRotZSpin)

	ON_BN_CLICKED(IDC_BUTTON_STATIC_MESH_CLONE, &CStaticMeshTool::OnBnClickedButtonClone)

	ON_BN_CLICKED(IDC_STATIC_MESH_DELETE, &CStaticMeshTool::OnBnClickedStaticMeshDelete)

	ON_BN_CLICKED(IDC_STATIC_MESH_SAVE, &CStaticMeshTool::OnBnClickedStaticMeshSave)
	ON_BN_CLICKED(IDC_STATIC_MESH_LOAD, &CStaticMeshTool::OnBnClickedStaticMeshLoad)

	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_STATIC_OBJ, &CStaticMeshTool::OnTvnSelchangedTreeStaticObj)

	ON_EN_CHANGE(IDC_STATIC_SPHERE_RADIUS_EDIT, &CStaticMeshTool::OnEnChangeStaticSphereRadiusEdit)

	ON_NOTIFY(UDN_DELTAPOS, IDC_STATIC_SPHERE_RADIUS_SPIN, &CStaticMeshTool::OnDeltaposStaticSphereRadiusSpin)

	ON_BN_CLICKED(IDC_STATIC_MESH_SPHERE_CREATE_BUTTON, &CStaticMeshTool::OnBnClickedStaticMeshSphereCreateButton)

	ON_BN_CLICKED(IDC_COL_RENDER_CHECK, &CStaticMeshTool::OnBnClickedColRenderCheck)
END_MESSAGE_MAP()


// CStaticMeshTab 메시지 처리기입니다.


void CStaticMeshTool::OnEnChangeStaticMeshPosX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();
	Engine::_vec3	vPos = *pSelected->Get_Pos();
	vPos.x = m_fPosX;
	pSelected->Set_Pos(&vPos);

	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshPosXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Move_X(fMove);
		m_fPosX = pSelected->Get_Pos()->x;
	}
	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshPosYEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	Engine::_vec3	vPos = *pSelected->Get_Pos();
	vPos.y = m_fPosY;
	pSelected->Set_Pos(&vPos);

	UpdateData(FALSE);

}


void CStaticMeshTool::OnDeltaposStaticMeshYPosSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Move_Y(fMove);
		m_fPosY = pSelected->Get_Pos()->y;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshPosZEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	Engine::_vec3	vPos = *pSelected->Get_Pos();
	vPos.z = m_fPosZ;
	pSelected->Set_Pos(&vPos);

	UpdateData(FALSE);

}


void CStaticMeshTool::OnDeltaposStaticMeshZPosSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Move_Z(fMove);
		m_fPosZ = pSelected->Get_Pos()->z;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshScalePosX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();
	Engine::_vec3 vScale = *pSelected->Get_Scale();
	vScale.x = m_fScaleX;
	pSelected->Set_Scale(&vScale);
	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{

		pSelected->Scale_X(fMove);
		m_fScaleX = pSelected->Get_Scale()->x;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshPosYScale()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	Engine::_vec3 vScale = *pSelected->Get_Scale();
	vScale.y = m_fScaleY;
	pSelected->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Scale_Y(fMove);
		m_fScaleY = pSelected->Get_Scale()->y;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshScaleZ()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	Engine::_vec3 vScale = *pSelected->Get_Scale();
	vScale.z = m_fScaleZ;
	pSelected->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshScaleSpinZ(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Scale_Z(fMove);
		m_fScaleZ = pSelected->Get_Scale()->z;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshRotX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);
	auto pSelected = get_SelectedObj();

	pSelected->Set_Rotation(Engine::ROT_X, m_fRotX);
	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshRotSpinX(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Rot_X(fMove);
		m_fRotX = pSelected->Get_Angle()->x;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshRotY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	pSelected->Set_Rotation(Engine::ROT_Y, m_fRotY);

	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshRotSpinY(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Rot_Y(fMove);
		m_fRotY = pSelected->Get_Angle()->y;
	}

	UpdateData(FALSE);
}


void CStaticMeshTool::OnEnChangeStaticMeshRotZ()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	auto pSelected = get_SelectedObj();

	pSelected->Set_Rotation(Engine::ROT_Z, m_fRotZ);

	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticMeshRotZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Engine::_float	fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	auto pSelected = get_SelectedObj();

	if (nullptr != pSelected)
	{
		pSelected->Rot_Z(fMove);
		m_fRotZ = pSelected->Get_Angle()->z;
	}

	UpdateData(FALSE);
}

BOOL CStaticMeshTool::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pStaticMeshCtrl = CToolStaticObjectCtrl::Create();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CStaticMeshTool::OnBnClickedButtonClone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	HTREEITEM hParentItem = m_TreeCtrl.GetSelectedItem();

	CToolStaticObject* pObj = dynamic_cast<CToolStaticObject*>(DLL::pObjMgr->Clone(m_strSelKey));
	pObj->Late_Initialize();

	m_TreeCtrl.InsertItem(pObj->Get_Name(), hParentItem, hParentItem);

	DLL::pObjMgr->Add_ObjList(pObj->Get_RenderKey(), pObj->Get_Name(), pObj);

	UpdateData(FALSE);
}

void CStaticMeshTool::OnBnClickedStaticMeshAdd()
{
	UpdateData(TRUE);

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	m_TreeCtrl.InsertItem(m_strKey);
	CToolStaticObject* pObj = CToolStaticObject::Create(pGraphicDev, m_strKey);
	pObj->Set_Name(m_strKey.GetString());
	pObj->Late_Initialize();

	DLL::pObjMgr->Add_Prefab(m_strKey.GetString(), pObj);
	m_TypeList.push_back(m_strKey.GetString());

	UpdateData(FALSE);
}


void CStaticMeshTool::OnBnClickedStaticMeshDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString strName = m_TreeCtrl.GetItemText(hItem);

	HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);
	CString strParentName = m_TreeCtrl.GetItemText(hParentItem);

	DLL::pObjMgr->Delete_Obj(strParentName.GetString(), strName.GetString());
	m_TreeCtrl.DeleteItem(hItem);
}

void CStaticMeshTool::OnBnClickedStaticMeshSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L".staticMeshdat", L".staticMeshdat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Static Mesh Data Files(*.staticMeshdat)|*.staticMeshdat||", this);

	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	Engine::_int iCount = 0;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 0, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		// 종류별로 갖고오기
		const map<const Engine::_tchar*, Engine::CGameObject*>* pObjMap = nullptr;

		// 종류별 map을 순회하면서 저장
		OBJECT_INFO			tInfo;
		CToolStaticObject*	pObj = nullptr;
		DWORD dwBytes = 0;

		auto pStaticPrefab = DLL::pDataMgr->Get_DataList(L"StaticMesh");

		for (auto iterType : *pStaticPrefab)
		{
			pObjMap = DLL::pObjMgr->Get_Map(iterType->wStrName.c_str());
			
			if (nullptr == pObjMap)
			{
				continue;
			}
			tInfo.wStrRenderKey = iterType->wStrName;

			for (auto iter : *pObjMap)
			{
				pObj = dynamic_cast<CToolStaticObject*>(iter.second);

				// 위치, 확대, 회전 데이터 복제
				tInfo.tInfo.vPos = *pObj->Get_Pos();
				tInfo.tInfo.vScale = *pObj->Get_Scale();
				tInfo.tInfo.vAngle = *pObj->Get_Angle();

				WriteFile(hFile, &tInfo.tInfo, sizeof(OBJECTBASE_INFO), &dwBytes, nullptr);

				Engine::_int iLength = static_cast<Engine::_int>(tInfo.wStrRenderKey.size());
				WriteFile(hFile, &iLength, sizeof(Engine::_int), &dwBytes, nullptr);
				WriteFile(hFile, tInfo.wStrRenderKey.c_str(), sizeof(Engine::_tchar) * iLength, &dwBytes, nullptr);

				WriteFile(hFile, &pObj->Get_Radius(), sizeof(Engine::_float), &dwBytes, nullptr);

				iCount++;
			}
		}

		CloseHandle(hFile);
	}

	TCHAR szFileName[iMaxStr]{};

	wsprintf(szFileName, L"%s\\%s", szCurrentDir, L"StageStaticObj.count");

	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	DWORD dwByte = 0;
	WriteFile(hFile, &iCount, sizeof(Engine::_int), &dwByte, NULL);

	CloseHandle(hFile);
}


void CStaticMeshTool::OnBnClickedStaticMeshLoad()
{
	CFileDialog Dlg(TRUE, L".staticMeshdat", L".staticMeshdat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Static Mesh Data Files(*.staticMeshdat)|*.staticMeshdat||", this);

	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	Dlg.m_ofn.lpstrInitialDir = szCurrentDir;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 0, nullptr,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		// 종류별로 갖고오기
		OBJECT_INFO			tInfo;
		CToolStaticObject*	pObj = nullptr;
		const int iMaxStr = 256;
		DWORD dwBytes = 0;
		

		m_TreeCtrl.DeleteAllItems();
		m_TypeList.clear();
		HTREEITEM hRootItem = nullptr;

		auto pPrefabList = DLL::pDataMgr->Get_DataList(L"StaticMesh");

		int iSize = static_cast<int>(pPrefabList->size());

		HTREEITEM* pParentItems = new HTREEITEM[iSize];

		int iCurIdx = 0;

		m_TreeCtrl.DeleteAllItems();
		for (auto iter : *pPrefabList)
		{
			pParentItems[iCurIdx++] = m_TreeCtrl.InsertItem(iter->wStrName.c_str());
		}

		CString strTest;

		auto pGraphicDev = DLL::pGraphicDev->GetDevice();

		TCHAR* szRenderKey = nullptr;
		while (true)
		{
			ReadFile(hFile, &tInfo.tInfo, sizeof(OBJECTBASE_INFO), &dwBytes, nullptr);

			if (0 == dwBytes)
			{
				break;
			}
			Engine::_int iLength = 0;
			ReadFile(hFile, &iLength, sizeof(Engine::_int), &dwBytes, nullptr);
			szRenderKey = new TCHAR[iLength + 1];
			
			ReadFile(hFile, szRenderKey, sizeof(Engine::_tchar) * iLength, &dwBytes, nullptr);
			szRenderKey[iLength] = '\0';
			
			tInfo.wStrRenderKey = szRenderKey;
			m_LoadNameList.push_back(szRenderKey);

			pObj = dynamic_cast<CToolStaticObject*>(DLL::pObjMgr->Clone(tInfo.wStrRenderKey.c_str()));

			Engine::_float fRadius = 0.f;
			ReadFile(hFile, &fRadius, sizeof(Engine::_float), &dwBytes, nullptr);

			int iFindIdx = 0;
			for (int i = 0; i < iCurIdx; ++i)
			{
				strTest = m_TreeCtrl.GetItemText(pParentItems[i]);

				if (strTest == tInfo.wStrRenderKey.c_str())
				{
					pObj = dynamic_cast<CToolStaticObject*>(DLL::pObjMgr->Clone(strTest));

					pObj->Late_Initialize();
					pObj->Set_Info(tInfo);

					if (fRadius != 0.f)
					{
						pObj->Add_Collider(Engine::CSphereCollider::Create(pGraphicDev, fRadius, 10, 10, pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_STATIC)->Get_World()), fRadius);
					}

					DLL::pObjMgr->Add_ObjList(szRenderKey, pObj->Get_Name(), pObj);

					m_TreeCtrl.InsertItem(pObj->Get_Name(), pParentItems[i], pParentItems[i]);
					break;
				}
			}
		}

		Engine::Safe_Delete_Array(pParentItems);
		CloseHandle(hFile);
	}
}


void CStaticMeshTool::OnTvnSelchangedTreeStaticObj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	m_strSelKey = m_TreeCtrl.GetItemText(hItem);

	HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);
	CString strParentName = m_TreeCtrl.GetItemText(hParentItem);

	auto pObj = DLL::pObjMgr->Get_Obj<CToolStaticObject>(strParentName, m_strSelKey);
	if (nullptr != pObj)
	{
		auto pPos = pObj->Get_Pos();
		Engine::_tchar szName[256]{};
		memcpy(szName, m_strSelKey, sizeof(Engine::_tchar) * m_strSelKey.GetLength());
		printf("%ws Position : %f %f %f\n", szName, pPos->x, pPos->y, pPos->z);
	}
}


void CStaticMeshTool::OnEnChangeStaticSphereRadiusEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CStaticMeshTool::OnDeltaposStaticSphereRadiusSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;


}


void CStaticMeshTool::OnBnClickedStaticMeshSphereCreateButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto pObj = DLL::pObjMgr->Get_PrefabObj<CToolStaticObject>(m_strSelKey.GetString());
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	// 선택된게 Prefab이 아닐 경우
	if (nullptr == pObj)
	{
		pObj = get_SelectedObj();

		
		pObj->Add_Collider(Engine::CSphereCollider::Create(pGraphicDev, m_fRadius, 10, 10, pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_STATIC)->Get_World()), m_fRadius);
	}
}


void CStaticMeshTool::OnBnClickedColRenderCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bColliderRender = !bColliderRender;
}
