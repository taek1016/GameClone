#include "stdafx.h"
#include "Barricade.h"
#include <iostream>

USING(Engine)

CBarricade::CBarricade()
	:CPickableObject()
{
}

CBarricade::CBarricade(const CBarricade & rhs)
	:CPickableObject(rhs)
{
}

_int CBarricade::Update_GameObject(const _float & fTimeDelta)
{
	CPickableObject::Update_GameObject(fTimeDelta);

	return _int();
}

void CBarricade::Render_GameObject()
{
	if (!m_bIsPicked)
	{
		DLL::pCameraMgr->Make_Billboard(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
		m_matBill = DLL::pCameraMgr->Get_Billboard(Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
	}
	else
	{
		CTransform* transform = Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC);
		transform->Set_Scale(1, 1, 1);
		DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, &(*Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_World()));
	}
	Get_Component<CTexture>(TEXTURE, ID_STATIC)->Render_Texture();

	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

HRESULT CBarricade::Initialize_GameObject()
{
	CPickableObject::Initialize_GameObject();
	CComponent* pComponent = nullptr;

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	dynamic_cast<CTransform*>(pComponent)->Set_Scale(&_vec3(6, 6, 1));

	pComponent = DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Barricade");
	pComponent->Attach(this, ID_STATIC);

	pComponent = CSphere::Create(1.5f);
	pComponent->Attach(this, ID_DYNAMIC);
	return S_OK;
}

CGameObject * CBarricade::Clone(const Engine::_vec3 * pPos)
{
	CBarricade*	pInstance = new CBarricade(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	_tchar wName[MAX_STR]{};

	wsprintf(wName, L"%s%d", Get_Name(), m_iCloneNum++);

	pInstance->SetName(wName);

	if (nullptr != pPos)
	{
		pInstance->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos->x, pPos->y, pPos->z);
	}
	pInstance->Late_Initialize();
	DLL::pColMgr->Add_Obj(pInstance);

	return pInstance;
}

CBarricade * CBarricade::Create()
{
	CBarricade*	pInstance = new CBarricade;
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CBarricade::freeMem()
{
	CInGameObject::freeMem();
}

HRESULT CBarricade::Late_Initialize()
{
	m_pPlayerCol = DLL::pSearchMgr->Get_Object(L"Player")->Get_Component<CCollider>(COLLIDER, ID_DYNAMIC);
	m_pMyCol = Get_Component<CSphere>(COLLIDER, ID_DYNAMIC);
	m_pMyCol->Late_Initialize();
	return S_OK;
}

bool CBarricade::IsPicked()
{

	return false;
}
