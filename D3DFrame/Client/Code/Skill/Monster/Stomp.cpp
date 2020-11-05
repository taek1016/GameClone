#include "stdafx.h"
#include "Stomp.h"

#include "Character/Player.h"

USING(Engine)

CStomp::CStomp(LPDIRECT3DDEVICE9 pGraphicDev)
	: CAttackSkillBase(pGraphicDev)
	, m_fCurTime(0.f)
	, m_bGiveDamage(false)
{
	set_Name(L"Stomp");
	Set_Damage(14);
}

CStomp::CStomp(const CStomp & rhs)
	: CAttackSkillBase(rhs)
	, m_fCurTime(0.f)
	, m_bGiveDamage(false)
{
}

HRESULT CStomp::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CDynamicMesh>(RESOURCE_DYNAMIC, m_wStrName.c_str())->Attach(L"Mesh", this, ID_STATIC);
	DLL::pShaderMgr->Clone_Shader(L"Shader_Mesh")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CStomp::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pMesh = Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pShaderCom = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

void CStomp::Attack(CGameObject * pTarget)
{
	dynamic_cast<CCharacterBase*>(pTarget)->Hit(m_iDamage);
	dynamic_cast<CPlayer*>(pTarget)->Stun();
}

void CStomp::act_Determine(const Engine::_float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;

	if (m_fCurTime >= 3.f)
	{
		m_bDead = true;
	}

	if (false == m_bGiveDamage)
	{
		auto pPlayer = (DLL::pObjMgr->Get_ObjList(L"Player")->front());
		Attack(pPlayer);
		m_bGiveDamage = true;
	}
}

void CStomp::check_DeadCondition(void)
{
}

void CStomp::dead_Effect(void)
{
}

CStomp * CStomp::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStomp* pInstance = new CStomp(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CStomp::Clone(void)
{
	CStomp* pInstance = new CStomp(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
