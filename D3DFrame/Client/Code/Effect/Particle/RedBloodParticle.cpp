#include "stdafx.h"
#include "RedBloodParticle.h"

USING(Engine)

CRedBloodParticle::CRedBloodParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBloodParticleBase(pGraphicDev)
{
	set_Name(L"RedBlood");
}

CRedBloodParticle::CRedBloodParticle(const CRedBloodParticle & rhs)
	: CBloodParticleBase(rhs)
{
}

CRedBloodParticle * CRedBloodParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRedBloodParticle* pInstance = new CRedBloodParticle(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->set_Texture(D3DXCOLOR(1.f, 0.f, 0.f, 1.f));

	return pInstance;
}

Engine::CGameObject * CRedBloodParticle::Clone(void)
{
	return new CRedBloodParticle(*this);
}
