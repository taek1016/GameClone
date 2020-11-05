#ifndef InfernalDeathEffect_h__
#define InfernalDeathEffect_h__

#include "MeshEffectBase.h"

class CInfernalDeathEffect : public CMeshEffectBase
{
private:
	explicit						CInfernalDeathEffect(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CInfernalDeathEffect(const CInfernalDeathEffect& rhs);
	virtual							~CInfernalDeathEffect(void) = default;

public:
	virtual void					Ready_ToGo(void) override;

private:
	virtual void					act_Determine(const Engine::_float& fTimeDelta);

public:
	static CInfernalDeathEffect*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // InfernalDeathEffect_h__
