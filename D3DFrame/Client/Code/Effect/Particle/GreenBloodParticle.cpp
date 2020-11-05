#include "stdafx.h"
#include "GreenBloodParticle.h"

USING(Engine)

CGreenBloodParticle::CGreenBloodParticle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBloodParticleBase(pGraphicDev)
{
	set_Name(L"GreenBlood");
}

CGreenBloodParticle::CGreenBloodParticle(const CGreenBloodParticle & rhs)
	: CBloodParticleBase(rhs)
{
}

CGreenBloodParticle * CGreenBloodParticle::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGreenBloodParticle* pInstance = new CGreenBloodParticle(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->set_Texture(D3DXCOLOR(0.f, 1.f, 0.f, 1.f));

	return pInstance;
}

Engine::CGameObject * CGreenBloodParticle::Clone(void)
{
	return new CGreenBloodParticle(*this);
}
