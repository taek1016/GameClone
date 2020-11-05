#include "stdafx.h"
#include "NPCBase.h"

#include "UI/UIBase.h"

USING(Engine)

CNPCBase::CNPCBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
	, m_pUI(nullptr)
	, m_bUIActivate(false)
{
}

CNPCBase::CNPCBase(const CNPCBase & rhs)
	: CCharacterBase(rhs)
	, m_pUI(rhs.m_pUI)
	, m_bUIActivate(false)
{
}

HRESULT CNPCBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, Get_Name())->Attach(L"Mesh", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"MeshShader", this, ID_STATIC);

	initialize_Animation();

	return S_OK;
}

HRESULT CNPCBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTransform->Set_Scale(&_vec3(5.f, 5.f, 5.f));

	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"MeshShader", ID_STATIC);

	initialize_NPCUI();

	return S_OK;
}

Engine::_int CNPCBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	mouse_Click(fTimeDelta);

	if (m_pMesh->Is_AnimationSetEnd())
	{
		m_pMesh->Set_AnimationSet(m_mapAnimationIndexMap[L"Stand"]);
	}

	m_pMesh->Play_Animation(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_NONALPHA, this);

	if (m_bUIActivate)
	{
		m_pUI->Update_GameObject(fTimeDelta);
	}
	
	act();

	return iExit;
}

void CNPCBase::read_Data(void)
{
	_vec3 vScale;
	vScale.x = get_ReadData(L"ScaleX");
	vScale.y = get_ReadData(L"ScaleY");
	vScale.z = get_ReadData(L"ScaleZ");

	m_pTransform->Set_Scale(&vScale);

	m_fMainColSize = get_ReadData(L"MainCol");
}

Engine::_float CNPCBase::get_ReadData(const Engine::_tchar * pKey)
{
	const _int iMaxStr = 256;
	_tchar szValue[iMaxStr]{};
	GetPrivateProfileString(m_wStrName.c_str(), pKey, L"0.f", szValue, iMaxStr, L"../../Data/PrefabData/NPCPrefab.ini");

	return static_cast<_float>(_wtof(szValue));
}

void CNPCBase::mouse_Click(const Engine::_float& fTimeDelta)
{
	auto pPlayer = DLL::pObjMgr->Get_ObjList(L"Player")->front();
	if (m_pMainSphereCollider)
	{
		if (CollideFunc::SphereToMouse(m_pGraphicDev, DLL::pMouseMgr->Get_ViewspaceMouse(), m_pTransform->Get_Info(INFO_POS), m_pMainSphereCollider->Get_Radius()))
		{
			DLL::pMouseMgr->Set_MouseMode(MOUSE_BUY);
			if (DLL::pInputMgr->MouseDown(DIM_LB))
			{
				m_bUIActivate = true;
				DLL::pMouseMgr->Set_PickTarget(this);
				m_pTransform->Compute_LookAtTarget(pPlayer->Get_Pos());

				m_pMesh->Set_AnimationSet(m_mapAnimationIndexMap[L"Deal"]);
			}
		}
	}

	_float fDistance = D3DXVec3Length(&(*pPlayer->Get_Pos() - *m_pTransform->Get_Info(INFO_POS)));

	const _float fEndDistance = 15.f;
	if (m_bUIActivate && fDistance >= fEndDistance)
	{
		m_bUIActivate = false;
		m_pTransform->Compute_LookAtTarget(pPlayer->Get_Pos());
		m_pMesh->Set_AnimationSet(m_mapAnimationIndexMap[L"GoodBye"]);
	}
}

inline void CNPCBase::Free(void)
{
	CCharacterBase::Free();

	Safe_Release(m_pUI);
}