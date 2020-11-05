#include "stdafx.h"
#include "AttackSkillBase.h"

USING(Engine)

CAttackSkillBase::CAttackSkillBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSkillBase(pGraphicDev)
	, m_pMesh(nullptr)
	, m_fSpeed(0.f)
	, m_bDead(false)
{
}

CAttackSkillBase::CAttackSkillBase(const CAttackSkillBase & rhs)
	: CSkillBase(rhs)
	, m_pMesh(nullptr)
	, m_fSpeed(rhs.m_fSpeed)
	, m_bDead(false)
{
	if (rhs.m_pMesh)
	{
		m_pMesh = dynamic_cast<CDynamicMesh*>(rhs.m_pMesh->Clone());
		m_pMesh->Attach(L"Mesh", this, ID_STATIC);
	}
}

CAttackSkillBase::~CAttackSkillBase(void)
{
}

Engine::_int CAttackSkillBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (m_bDead)
	{
		return DEAD_OBJ;
	}

	act_Determine(fTimeDelta);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_pMesh->Play_Animation(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CAttackSkillBase::Render_GameObject(void)
{
	LPD3DXEFFECT	pEffect = m_pShaderCom->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;

	FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);

	pEffect->BeginPass(0);

	m_pMesh->Render_Meshes(pEffect);

	pEffect->EndPass();

	pEffect->End();

	Safe_Release(pEffect);

	if (g_bCollider)
	{
		m_pCollider->Render_Collider(m_eCollType, m_pTransform->Get_World());
	}
}

void CAttackSkillBase::set_Speed(const Engine::_float & fSpeed)
{
	m_fSpeed = fSpeed;
}
