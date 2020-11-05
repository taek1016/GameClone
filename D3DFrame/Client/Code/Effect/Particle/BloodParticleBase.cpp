#include "stdafx.h"
#include "BloodParticleBase.h"

USING(Engine)

CBloodParticleBase::CBloodParticleBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CParticleBase(pGraphicDev)
{
	set_Speed(1.f);
}

CBloodParticleBase::CBloodParticleBase(const CBloodParticleBase & rhs)
	: CParticleBase(rhs)
{
}

HRESULT CBloodParticleBase::Initialize_GameObject(void)
{
	CParticleBase::Initialize_GameObject();

	CRigidBody::Create(-1.f, 2.f)->Attach(L"RigidBody", this, ID_DYNAMIC);

	set_DeadTime(2.f);

	return S_OK;
}

HRESULT CBloodParticleBase::Late_Initialize(void)
{
	CParticleBase::Late_Initialize();

	m_pRigidBody = Get_Component<CRigidBody>(L"RigidBody", ID_DYNAMIC);
	m_pRigidBody->Activate(true);

	return S_OK;
}

void CBloodParticleBase::Ready_ToGo(void)
{
	m_fCurTime = 0.f;
	m_fFrameCnt = 0.f;
}


void CBloodParticleBase::move_Particle(const Engine::_float & fTimeDelta)
{
	_vec3 vDir = m_vDir;

	vDir = vDir * m_fSpeed * fTimeDelta;
	
	vDir.y += m_pRigidBody->Get_YPos();

	D3DXVec3Normalize(&vDir, &vDir);

	m_pTransform->Move_Pos(&vDir);
}
