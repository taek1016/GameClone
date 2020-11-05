#include "stdafx.h"
#include "YellowParticle.h"

USING(Engine)

CYellowParticle::CYellowParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CParticleBase(pGraphicDev)
	, m_fAngle(0.f)
	, m_vTargetPos(0.f, 0.f, 0.f)
{
}

CYellowParticle::CYellowParticle(const CYellowParticle & rhs)
	: CParticleBase(rhs)
	, m_fAngle(0.f)
	, m_vTargetPos(0.f, 0.f, 0.f)
{
}

HRESULT CYellowParticle::Initialize_GameObject(void)
{
	CParticleBase::Initialize_GameObject();

	set_Texture(D3DXCOLOR(1.f, 1.f, 0.f, 1.f));
	set_MaxFrame(0.f);
	set_Speed(5.f);
	set_DeadTime(3.f);
	
	return S_OK;
}

HRESULT CYellowParticle::Late_Initialize(void)
{
	CParticleBase::Late_Initialize();

	const _float fScaleValue = 0.3f;
	m_pTransform->Set_Scale(&_vec3(fScaleValue, fScaleValue, fScaleValue));

	return S_OK;
}

void CYellowParticle::Set_Data(const Engine::_float& fAngle, const Engine::_vec3* pPos)
{
	set_Angle(fAngle);
	set_TargetPos(pPos);
}

void CYellowParticle::Ready_ToGo(void)
{
	m_fCurTime = 0.f;
	m_fAngle = 0.f;
	m_bDead = false;
}

void CYellowParticle::set_Angle(const Engine::_float & fAngle)
{
	m_fAngle = fAngle;

	const _float fFullRadian = D3DXToRadian(360.f);
	if (m_fAngle >= fFullRadian)
	{
		m_fAngle -= fFullRadian;
	}
}

void CYellowParticle::set_TargetPos(const Engine::_vec3 * pPos)
{
	m_vTargetPos = *pPos;
}
