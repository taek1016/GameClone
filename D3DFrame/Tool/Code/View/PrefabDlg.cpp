// D:\Codes\D3DFrame\Tool\Code\View\PrefabDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"

#include "View\PrefabDlg.h"
#include "Object\ToolDynamicObject.h"

#include "afxdialogex.h"
#include "Transform.h"
#include "ActionComponent.h"
// CPrefabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPrefabDlg, CDialogEx)

CPrefabDlg::CPrefabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PREFAB_DLG, pParent)
	, m_pDynamicObj(nullptr)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_bInitialized(false)
	, m_strAnimationName(_T(""))
	, m_strPrefabName(_T(""))
	, m_strBoneName(_T(""))
	, m_fSphereRadius(0)
	, m_fBoxMin(0)
	, m_fBoxMax(0)
	, m_strMakeActionName(_T(""))
	, m_fActionCool(0)
	, m_fActionRadius(0)
{

}

CPrefabDlg::~CPrefabDlg()
{
}

void CPrefabDlg::Initialize_Names(void)
{
	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto& iter : *pList)
	{
		m_PrefabComboBox.AddString(iter->wStrName.c_str());
	}
}

Engine::_bool CPrefabDlg::Get_Initialized(void)
{
	return m_bInitialized;
}

void CPrefabDlg::Initialize_Prefab(void)
{
	m_bInitialized = true;

	make_Prefabs();
}

void CPrefabDlg::save_PrefabData(HANDLE hFile, CToolDynamicObject * pObj)
{
	DWORD dwBytes = 0;
	// 스케일 값 저장
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	WriteFile(hFile, pTransform->Get_Scale(), sizeof(Engine::_vec3), &dwBytes, NULL);

	const wstring& wStrColliderBoneName = pObj->Get_ColliderBoneName();

	Engine::_int iSize = static_cast<Engine::_int>(wStrColliderBoneName.size());

	// 충돌체 핵심 이름 저장.
	WriteFile(hFile, &iSize, sizeof(Engine::_int), &dwBytes, NULL);
	WriteFile(hFile, wStrColliderBoneName.c_str(), sizeof(Engine::_tchar) * iSize, &dwBytes, NULL);

	// 메인 충돌체 반지름 갖고오기.
	auto pSphere = pObj->Get_Component<Engine::CSphereCollider>(L"SphereCollider", Engine::ID_STATIC);
	WriteFile(hFile, pSphere->Get_Radius(), sizeof(Engine::_float), &dwBytes, NULL);

	auto pActionMap = pObj->Get_ActionMap();

	for (auto iter : *pActionMap)
	{
		// 이름, 충돌체 쿨타임, 반지름 넣기.
		// 이름
		iSize = static_cast<Engine::_int>(iter.first.size());
		WriteFile(hFile, &iSize, sizeof(Engine::_int), &dwBytes, NULL);
		WriteFile(hFile, iter.first.c_str(), sizeof(Engine::_tchar) * iSize, &dwBytes, NULL);

		// 충돌체 쿨타임
		WriteFile(hFile, iter.second->Get_CoolTime(), sizeof(Engine::_float), &dwBytes, NULL);
		// 충돌체 반지름
		WriteFile(hFile, iter.second->Get_Radius(), sizeof(Engine::_float), &dwBytes, NULL);
	}

}

void CPrefabDlg::save_AnimationData(HANDLE hFile, CToolDynamicObject * pObj)
{
	unsigned short sMark = 0xFEFF;
	DWORD dwBytes = 0;

	const int iMaxStr = 256;
	TCHAR szContent[iMaxStr]{};

	auto pMap = pObj->Get_AnimationKey();

	WriteFile(hFile, &sMark, sizeof(unsigned short), &dwBytes, NULL);

	for (auto iter : *pMap)
	{
		::ZeroMemory(szContent, sizeof(TCHAR) * iMaxStr);

		wsprintf(szContent, L"%s\t\t%d\n", iter.first.c_str(), iter.second);
		WriteFile(hFile, szContent, static_cast<DWORD>(sizeof(TCHAR) * wcslen(szContent)), &dwBytes, NULL);
	}
}

void CPrefabDlg::save_BoneData(HANDLE hFile, CToolDynamicObject * pObj)
{
	unsigned short sMark = 0xFEFF;
	DWORD dwBytes = 0;

	const int iMaxStr = 256;
	TCHAR szContent[iMaxStr]{};

	auto pList = pObj->Get_BoneList();

	WriteFile(hFile, &sMark, sizeof(unsigned short), &dwBytes, NULL);

	for (auto iter : *pList)
	{
		::ZeroMemory(szContent, sizeof(TCHAR) * iMaxStr);

		lstrcpy(szContent, iter.c_str());
		lstrcat(szContent, L"\n");
		WriteFile(hFile, szContent, static_cast<DWORD>(sizeof(TCHAR) * wcslen(szContent)), &dwBytes, NULL);
	}
}

void CPrefabDlg::make_Prefabs(void)
{
	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	for (auto iter : *pList)
	{
		auto pObj = CToolDynamicObject::Create(pGraphicDev, iter->wStrName.c_str());
		pObj->Late_Initialize();
		DLL::pObjMgr->Add_Prefab(iter->wStrName.c_str(), pObj);
	}
}

void CPrefabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PREFAB_SCALE_X_EDIT, m_fScaleX);
	DDX_Text(pDX, IDC_PREFAB_SCALE_Y_EDIT, m_fScaleY);
	DDX_Text(pDX, IDC_PREFAB_SCLAE_Z_EDIT, m_fScaleZ);
	DDX_Control(pDX, IDC_PREFAB_ACTION_COMBO, m_AnimationComboBox);
	DDX_Control(pDX, IDC_COMBO2, m_PrefabComboBox);
	DDX_CBString(pDX, IDC_PREFAB_ACTION_COMBO, m_strAnimationName);
	DDX_CBString(pDX, IDC_COMBO2, m_strPrefabName);
	DDX_Control(pDX, IDC_COMBO3, m_BoneComboBox);
	DDX_CBString(pDX, IDC_COMBO3, m_strBoneName);
	DDX_Text(pDX, IDC_COLLIDER_RADIUS_EDIT, m_fSphereRadius);
	DDX_Text(pDX, IDC_ACTION_NAME_EDIT, m_strMakeActionName);
	DDX_Text(pDX, IDC_COOL_TIME_EDIT, m_fActionCool);
	DDX_Control(pDX, IDC_ACTION_COL_COMBO, m_ActionComboBox);
	DDX_Text(pDX, IDC_EDIT3, m_fActionRadius);
}

void CPrefabDlg::applyPrefabChange(void)
{
	m_PrefabComboBox.ResetContent();

	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto iterFileInfo : *pList)
	{
		m_PrefabComboBox.AddString(iterFileInfo->wStrName.c_str());
	}
}

BEGIN_MESSAGE_MAP(CPrefabDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PREFAB_CHANGE_APPLY_BUTTON, &CPrefabDlg::OnBnClickedPrefabChangeApplyButton)
	ON_BN_CLICKED(IDC_ANIMATE_BUTTON, &CPrefabDlg::OnBnClickedAnimateButton)
	ON_BN_CLICKED(IDC_BONE_COLLIDER_APPLY_BUTTON, &CPrefabDlg::OnBnClickedBoneColliderApplyButton)
	ON_BN_CLICKED(IDC_BONE_COLLIDER_DELETE_BUTTON, &CPrefabDlg::OnBnClickedBoneColliderDeleteButton)
	ON_BN_CLICKED(IDC_PREFAB_SAVE_BUTTON, &CPrefabDlg::OnBnClickedPrefabSaveButton)
	ON_BN_CLICKED(IDC_PREFAB_LOAD_BUTTON, &CPrefabDlg::OnBnClickedPrefabLoadButton)
	ON_EN_CHANGE(IDC_COLLIDER_RADIUS_EDIT, &CPrefabDlg::OnEnChangeColliderRadiusEdit)
	ON_EN_CHANGE(IDC_PREFAB_SCALE_X_EDIT, &CPrefabDlg::OnEnChangePrefabScaleXEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PREFAB_SCALE_X_SPIN, &CPrefabDlg::OnDeltaposPrefabScaleXSpin)
	ON_EN_CHANGE(IDC_PREFAB_SCALE_Y_EDIT, &CPrefabDlg::OnEnChangePrefabScaleYEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PREFAB_SCALE_Y_SPIN, &CPrefabDlg::OnDeltaposPrefabScaleYSpin)
	ON_EN_CHANGE(IDC_PREFAB_SCLAE_Z_EDIT, &CPrefabDlg::OnEnChangePrefabSclaeZEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PREFAB_SCALE_Z_SPIN, &CPrefabDlg::OnDeltaposPrefabScaleZSpin)
	ON_CBN_SELCHANGE(IDC_PREFAB_ACTION_COMBO, &CPrefabDlg::OnCbnSelchangePrefabActionCombo)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CPrefabDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CPrefabDlg::OnCbnSelchangeCombo3)
	ON_EN_CHANGE(IDC_ACTION_NAME_EDIT, &CPrefabDlg::OnEnChangeActionNameEdit)
	ON_EN_CHANGE(IDC_COOL_TIME_EDIT, &CPrefabDlg::OnEnChangeCoolTimeEdit)
	ON_BN_CLICKED(IDC_BUTTON1, &CPrefabDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_ACTION_COL_COMBO, &CPrefabDlg::OnCbnSelchangeActionColCombo)
	ON_EN_CHANGE(IDC_EDIT3, &CPrefabDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CPrefabDlg 메시지 처리기입니다.


void CPrefabDlg::OnBnClickedCallPrefabButton()
{

}


void CPrefabDlg::OnBnClickedPrefabChangeApplyButton()
{
	Engine::_int iSel = m_PrefabComboBox.GetCurSel();

	const int iMaxStr = 256;
	CString strSelectedText;
	m_PrefabComboBox.GetLBText(iSel, strSelectedText);

	DLL::pObjMgr->Set_PrefabObj(strSelectedText.GetString());
}


void CPrefabDlg::OnBnClickedAnimateButton()
{
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());

	if (nullptr == pObj)
	{
		return;
	}

	pObj->Play_Animation(m_strAnimationName);
}

void CPrefabDlg::OnBnClickedBoneColliderApplyButton()
{
	CToolDynamicObject* pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());

	if (nullptr == pObj)
	{
		return;
	}

	if (m_strBoneName.IsEmpty())
	{
		return;
	}

	pObj->Add_SphereCollider(m_fSphereRadius);
}


void CPrefabDlg::OnBnClickedBoneColliderDeleteButton()
{
	auto pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName);

	pObj->Delete_ActionCol(m_strMakeActionName);
	m_ActionComboBox.DeleteString(m_ActionComboBox.GetCurSel());
}


void CPrefabDlg::OnBnClickedPrefabSaveButton()
{
	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data\\PrefabData\\");

	TCHAR* szExtensions[] = { L".prefab", L"_Anim.txt", L"_Bone.txt" };
	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");
	HANDLE hFile = nullptr;

	TCHAR szFileName[iMaxStr]{};

	CToolDynamicObject* pObj = nullptr;

	pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());

	if (nullptr == pObj)
	{
		return;
	}

	::ZeroMemory(szFileName, sizeof(TCHAR) * iMaxStr);

	// prefab 데이터 저장
	wsprintf(szFileName, L"%s%s%s", szCurrentDir, m_strPrefabName.GetString(), szExtensions[0]);

	hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	save_PrefabData(hFile, pObj);
	CloseHandle(hFile);

	// 애니메이션 추출
	wsprintf(szFileName, L"%s%s%s", szCurrentDir, m_strPrefabName.GetString(), szExtensions[1]);

	hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	save_AnimationData(hFile, pObj);
	CloseHandle(hFile);

	// 뼈 이름 추출
	wsprintf(szFileName, L"%s%s%s", szCurrentDir, m_strPrefabName.GetString(), szExtensions[2]);

	hFile = CreateFile(szFileName, GENERIC_WRITE, 0, nullptr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}
	save_BoneData(hFile, pObj);


	CloseHandle(hFile);

	TCHAR szStrings[1024]{};
	lstrcpy(szStrings, m_strPrefabName);
	lstrcat(szStrings, L" Prefab Save Complete");
	MessageBox(szStrings);
}


void CPrefabDlg::OnBnClickedPrefabLoadButton()
{
	const int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data\\PrefabData\\");

	TCHAR* szExtensions = L".prefab";
	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");
	HANDLE hFile = nullptr;

	TCHAR szFileName[iMaxStr]{};

	CToolDynamicObject* pObj = nullptr;

	DWORD dwBytes = 0;
	Engine::_vec3 vScale;

	TCHAR szNames[iMaxStr]{};
	Engine::_int iNameSize;

	wsprintf(szFileName, L"%s%s%s", szCurrentDir, m_strPrefabName.GetString(), szExtensions);

	hFile = CreateFile(szFileName, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());

	// 스케일 값 저장
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);

	ReadFile(hFile, &vScale, sizeof(Engine::_vec3), &dwBytes, NULL);
	pTransform->Set_Scale(&vScale);

	::ZeroMemory(szNames, sizeof(TCHAR) * iMaxStr);

	// 충돌체 핵심 이름 불러오기.
	ReadFile(hFile, &iNameSize, sizeof(Engine::_int), &dwBytes, NULL);
	ReadFile(hFile, szNames, sizeof(Engine::_tchar) * iNameSize, &dwBytes, NULL);

	pObj->Set_ColliderBoneName(szNames);

	Engine::_float fCoolTime, fRadius;
	// 메인 충돌체 반지름 갖고오기.
	ReadFile(hFile, &fRadius, sizeof(Engine::_float), &dwBytes, NULL);
	pObj->Add_SphereCollider(fRadius);

	while (true)
	{
		ReadFile(hFile, &iNameSize, sizeof(Engine::_int), &dwBytes, NULL);
		if (0 == dwBytes)
		{
			break;
		}
		::ZeroMemory(szNames, sizeof(TCHAR) * iMaxStr);
		ReadFile(hFile, szNames, sizeof(Engine::_tchar) * iNameSize, &dwBytes, NULL);

		ReadFile(hFile, &fCoolTime, sizeof(Engine::_float), &dwBytes, NULL);
		ReadFile(hFile, &fRadius, sizeof(Engine::_float), &dwBytes, NULL);

		pObj->Add_ActionCol(szNames, fCoolTime, fRadius);
	}

	CloseHandle(hFile);

	TCHAR szStrings[1024]{};
	lstrcpy(szStrings, m_strPrefabName);
	lstrcat(szStrings, L" Prefab Load Complete");
	MessageBox(szStrings);
}

void CPrefabDlg::OnEnChangePrefabKeyEdit()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CPrefabDlg::OnEnChangeAnimationNumberEdit()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CPrefabDlg::OnEnChangeAnimationKeyStringEdit()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}

void CPrefabDlg::OnBnClickedBoneNameSaveButton()
{
	const Engine::_int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	TCHAR szPathName[iMaxStr]{};
	HANDLE hFile = nullptr;

	// 0xFEFF면 유니코드 인식.
	unsigned short sMark = 0xFEFF;
	DWORD dwBytes = 0;

	TCHAR szContent[iMaxStr]{};

	auto pList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto iterList : *pList)
	{
		ZeroMemory(szPathName, sizeof(TCHAR) * iMaxStr);
		::PathCombine(szPathName, szCurrentDir, iterList->wStrName.c_str());
		lstrcat(szPathName, L"_Bone.txt");

		hFile = CreateFile(szPathName, GENERIC_WRITE, 0, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		WriteFile(hFile, &sMark, sizeof(unsigned short), &dwBytes, NULL);

		auto pBoneList = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(iterList->wStrName.c_str())->Get_BoneList();

		for (auto iter : *pBoneList)
		{
			::ZeroMemory(szContent, sizeof(TCHAR) * iMaxStr);

			lstrcpy(szContent, iter.c_str());
			lstrcat(szContent, L"\n");
			WriteFile(hFile, szContent, static_cast<DWORD>(sizeof(TCHAR) * wcslen(szContent)), &dwBytes, NULL);
		}

		CloseHandle(hFile);
	}

	MessageBox(L"Bone name save complete");
}

void CPrefabDlg::OnBnClickedBoneNameLoadButton()
{
	//initialize_BoneName();
	MessageBoxW(L"Bone Name Load Complete");
}

void CPrefabDlg::OnBnClickedExportKeyButton()
{
	const Engine::_int iMaxStr = 256;
	TCHAR szCurrentDir[iMaxStr] = L"";

	::GetCurrentDirectory(iMaxStr, szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathRemoveFileSpec(szCurrentDir);
	::PathCombine(szCurrentDir, szCurrentDir, L"Data");

	TCHAR szPathName[iMaxStr]{};
	HANDLE hFile = nullptr;

	// 0xFEFF면 유니코드 인식.
	unsigned short sMark = 0xFEFF;
	DWORD dwBytes = 0;

	TCHAR szContent[iMaxStr]{};

	ZeroMemory(szPathName, sizeof(TCHAR) * iMaxStr);

	auto pDataList = DLL::pDataMgr->Get_DataList(L"DynamicMesh");

	for (auto iterList : *pDataList)
	{
		::PathCombine(szPathName, szCurrentDir, iterList->wStrName.c_str());
		lstrcat(szPathName, L"_Anim.txt");

		hFile = CreateFile(szPathName, GENERIC_WRITE, 0, nullptr,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			return;
		}

		WriteFile(hFile, &sMark, sizeof(unsigned short), &dwBytes, NULL);

		auto pAnimationList = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(iterList->wStrName.c_str())->Get_AnimationKey();

		for (auto iter : *pAnimationList)
		{
			::ZeroMemory(szContent, sizeof(TCHAR) * iMaxStr);

			wsprintf(szContent, L"%d %s\n", iter.first, iter.second);
			WriteFile(hFile, szContent, static_cast<DWORD>(sizeof(TCHAR) * wcslen(szContent)), &dwBytes, NULL);
		}

		CloseHandle(hFile);
	}
	MessageBox(L"Animation index, name save complete");
}


void CPrefabDlg::OnEnChangeMainColEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPrefabDlg::OnBnClickedMainColApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());

	//pObj->Add_MainCollider(m_fMainCol);
}

void CPrefabDlg::OnEnChangeColliderRadiusEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void CPrefabDlg::OnEnChangePrefabScaleXEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}
	UpdateData(TRUE);

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.x = m_fScaleX;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CPrefabDlg::OnDeltaposPrefabScaleXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}

	const Engine::_float fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.x += fMove;

	m_fScaleX = vScale.x;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CPrefabDlg::OnEnChangePrefabScaleYEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}

	UpdateData(TRUE);

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.y = m_fScaleY;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CPrefabDlg::OnDeltaposPrefabScaleYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}
	const Engine::_float fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.y += fMove;

	m_fScaleY = vScale.y;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);

}


void CPrefabDlg::OnEnChangePrefabSclaeZEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}

	UpdateData(TRUE);

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.z = m_fScaleZ;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CPrefabDlg::OnDeltaposPrefabScaleZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CToolDynamicObject* pObj = dynamic_cast<CToolDynamicObject*>(DLL::pObjMgr->Get_CurPrefabObj());
	if (nullptr == pObj)
	{
		return;
	}
	auto pTransform = pObj->Get_Component<Engine::CTransform>(L"Transform", Engine::ID_DYNAMIC);
	if (nullptr == pTransform)
	{
		return;
	}
	const Engine::_float fTick = 0.01f;
	Engine::_float	fMove = pNMUpDown->iDelta * -1.f * fTick;

	Engine::_vec3 vScale = *pTransform->Get_Scale();
	vScale.z += fMove;

	m_fScaleZ = vScale.z;
	pTransform->Set_Scale(&vScale);

	UpdateData(FALSE);
}


void CPrefabDlg::OnCbnSelchangePrefabActionCombo()
{
	m_AnimationComboBox.GetLBText(m_AnimationComboBox.GetCurSel(), m_strAnimationName);
}


void CPrefabDlg::OnCbnSelchangeCombo2()
{
	m_PrefabComboBox.GetLBText(m_PrefabComboBox.GetCurSel(), m_strPrefabName);

	m_BoneComboBox.ResetContent();

	m_AnimationComboBox.ResetContent();

	m_ActionComboBox.ResetContent();

	auto pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());
	auto pBoneList = pObj->Get_BoneList();

	for (auto iter : *pBoneList)
	{
		m_BoneComboBox.AddString(iter.c_str());
	}

	auto pAnimationMap = pObj->Get_AnimationKey();

	for (auto iter : *pAnimationMap)
	{
		m_AnimationComboBox.AddString(iter.first.c_str());
	}

	auto pActionMap = pObj->Get_ActionMap();

	for (auto iter : *pActionMap)
	{
		m_ActionComboBox.AddString(iter.first.c_str());
	}
}


void CPrefabDlg::OnCbnSelchangeCombo3()
{
	m_BoneComboBox.GetLBText(m_BoneComboBox.GetCurSel(), m_strBoneName);

	CToolDynamicObject* pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());

	pObj->Set_ColliderBoneName(m_strBoneName);
}


void CPrefabDlg::OnBnClickedBoxColApplyButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CPrefabDlg::OnEnChangeMinEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPrefabDlg::OnEnChangeMaxEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPrefabDlg::OnEnChangeActionNameEdit()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPrefabDlg::OnEnChangeCoolTimeEdit()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void CPrefabDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto pObj = DLL::pObjMgr->Get_PrefabObj<CToolDynamicObject>(m_strPrefabName.GetString());

	pObj->Add_ActionCol(m_strMakeActionName, m_fActionCool, m_fActionRadius);

	m_ActionComboBox.AddString(m_strMakeActionName);
}


void CPrefabDlg::OnCbnSelchangeActionColCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ActionComboBox.GetLBText(m_ActionComboBox.GetCurSel(), m_strMakeActionName);
}


void CPrefabDlg::OnEnChangeEdit3()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}
