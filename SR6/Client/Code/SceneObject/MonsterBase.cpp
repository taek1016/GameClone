#include "stdafx.h"
#include "MonsterBase.h"

#include "Player.h"

#include "Effect/BloodParticle.h"

USING(Engine)

CMonster::CMonster(void)
	: CPickableObject()
{
	m_eType = Engine::IS_MONSTER::OBJ_MONSTER;
}

CMonster::CMonster(const CMonster& rhs)
	: CPickableObject(rhs)
	, m_iHP(rhs.m_iHP)
	, m_iMaxHP(rhs.m_iMaxHP)
{
	m_eType = Engine::IS_MONSTER::OBJ_MONSTER;
}

CMonster::~CMonster(void)
{
}

HRESULT CMonster::Late_Initialize(void)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pSearchMgr->Get_Object(L"Player"));

	if (nullptr != pPlayer)
	{
		m_pPlayer = pPlayer;
	}

	for (_int i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_vecComponent[i])
		{
			if (nullptr == iter)
			{
				continue;
			}

			if (FAILED(iter->Late_Initialize()))
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT CMonster::Initialize_GameObject(void)
{
	CPickableObject::Initialize_GameObject();

	return S_OK;
}

Engine::_int CMonster::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_iHP <= 0)
	{
		DLL::pPickMgr->Delete_Object(Get_Name());
		return DEAD_OBJ;
	}
	m_fCurFrame += fTimeDelta * m_fMaxFrame;

	if (m_fCurFrame >= m_fMaxFrame)
	{
		m_fCurFrame = 0.f;
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	ChangeStatus();

	DLL::pColMgr->Collide_Push_Obj(this, 2.f);
	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CMonster::Take_Damage(const _float & fDamage)
{
	m_iHP -= static_cast<_int>(fDamage);

	CBloodParticle* particle = dynamic_cast<CBloodParticle*>(DLL::pPoolMgr->Get_Pool<CBloodParticle>(POOL_PARTICLE));
	DLL::pObjMgr->Add_GameObject(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_PARTICLE, particle);
	CTransform* transform = Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	particle->SetEmitPoint(*transform->Get_Info(INFO_POS));
	particle->Reset_AllParticles();
}

void CMonster::SetCurStatus(const OBJECT_STATUS & eStatus)
{
	m_eCurStatus = eStatus;
}

void CMonster::SetPreStatus(void)
{
	m_ePreStatus = m_eCurStatus;
}

void CMonster::ChangeStatus()
{
	if (m_eCurStatus != m_ePreStatus)
	{
		SetStatus();
		SetFrame();
	}
}

void CMonster::SetStatus()
{
	switch (m_eCurStatus)
	{
	case ATTACK:
		m_pCurTexture = m_pTexture[ATTACK];
		break;
	case IDLE:
		m_pCurTexture = m_pTexture[IDLE];
		break;
	case DIE:
		m_pCurTexture = m_pTexture[DIE];
		break;
	case MOVE:
		m_pCurTexture = m_pTexture[MOVE];
		break;
	}
}

void CMonster::SetFrame()
{
	m_fMaxFrame = static_cast<_float>(m_iStatusAction[m_eCurStatus]);
	m_fCurFrame = 0.f;
}

void CMonster::Initialize_Texture(const _tchar * pKey)
{
	_tchar	szName[MAX_STR]{};
	_tchar*	szTypes[OBJECT_STATUS::STATUS_END] = { L"Attack", L"Idle", L"Die", L"Move" };

	for (_int i = 0; i < static_cast<_int>(OBJECT_STATUS::STATUS_END); ++i)
	{
		wsprintf(szName, L"%s%s", pKey, szTypes[i]);
		m_pTexture[i] = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, szName));
	}

}

void CMonster::freeMem()
{
	CGameObject::freeMem();
	
	m_pPlayer = nullptr;
}