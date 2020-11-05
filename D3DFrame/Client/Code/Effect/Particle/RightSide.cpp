#include "stdafx.h"
#include "RightSide.h"

USING(Engine)

CRightSide::CRightSide(LPDIRECT3DDEVICE9 pGraphicDev)
	: CYellowParticle(pGraphicDev)
{
	set_Name(L"RightSide");
}

CRightSide::CRightSide(const CRightSide & rhs)
	: CYellowParticle(rhs)
{
}

void CRightSide::move_Particle(const Engine::_float & fTimeDelta)
{
	_vec3 vPos = m_vTargetPos;

	vPos.x += sinf(m_fAngle)* 2.f;
	vPos.z += sinf(m_fAngle)* 2.f;

	m_pTransform->Set_Info(INFO_POS, &vPos);
}

CRightSide * CRightSide::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRightSide* pInstance = new CRightSide(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CRightSide::Clone(void)
{
	CRightSide* pInstance = new CRightSide(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
