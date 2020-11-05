#include "stdafx.h"
#include "Zombie.h"

#include "Component/MonsterController.h"

USING(Engine)

CZombie::CZombie(void)
	: CMonster()
{
	SetName(L"Zombie");
}

CZombie::CZombie(const CZombie & rhs)
	: CMonster(rhs)
{
}

CZombie::~CZombie(void)
{
}

HRESULT CZombie::Initialize_GameObject(void)
{
	CMonster::Initialize_GameObject();
	Engine::CComponent*	pComponent = nullptr;

	pComponent = CMonsterController::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CSphere::Create(0.3f);
	pComponent->Attach(this, ID_DYNAMIC);

	pComponent = CTransform::Create();
	pComponent->Attach(this, ID_DYNAMIC);

	m_iMaxHP = m_iHP = 10;

	m_fDamage = 2.f;

	m_iStatusAction[ATTACK] = 3;
	m_iStatusAction[MOVE] = 8;
	m_iStatusAction[IDLE] = 3;
	m_iStatusAction[DIE] = 3;

	return S_OK;
}

void CZombie::Render_GameObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = DLL::pGraphicDev->GetDevice();

	CTransform* pTransform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	DLL::pCameraMgr->Make_Billboard(pTransform);
	m_matBill = DLL::pCameraMgr->Get_Billboard(pTransform);

	m_pCurTexture->Render_Texture(static_cast<_int>(m_fCurFrame));
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CZombie * CZombie::Create(void)
{
	CZombie*	pInstance = new CZombie();

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CZombie::Clone(const Engine::_vec3 * pPos)
{
	CZombie*	pInstance = new CZombie(*this);
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

	DLL::pColMgr->Add_Obj(pInstance);

	pInstance->Initialize_Texture(L"Zombie");

	return pInstance;
}
