#include "stdafx.h"
#include "LeftSide.h"

USING(Engine)

CLeftSide::CLeftSide(LPDIRECT3DDEVICE9 pGraphicDev)
	: CYellowParticle(pGraphicDev)
{
	set_Name(L"LeftSide");
}

CLeftSide::CLeftSide(const CLeftSide & rhs)
	: CYellowParticle(rhs)
{
}

void CLeftSide::move_Particle(const Engine::_float & fTimeDelta)
{
	_vec3 vPos = m_vTargetPos;
	
	vPos.x -= sinf(m_fAngle/* - D3DXToRadian(90.f)*/) * 2.f;
	vPos.z -= sinf(m_fAngle)* 2.f;

	m_pTransform->Set_Info(INFO_POS, &vPos);
}

CLeftSide * CLeftSide::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLeftSide* pInstance = new CLeftSide(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	
	return pInstance;
}

Engine::CGameObject * CLeftSide::Clone(void)
{
	CLeftSide* pInstance = new CLeftSide(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
