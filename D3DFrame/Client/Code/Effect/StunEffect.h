#ifndef StunEffect_h__
#define StunEffect_h__

#include "MeshEffectBase.h"

class CStunEffect : public CMeshEffectBase
{
private:
	explicit						CStunEffect(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CStunEffect(const CStunEffect& rhs);
	virtual							~CStunEffect(void) = default;

public:
	virtual void					Ready_ToGo(void) override;

private:
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;

	Engine::_float					m_fStunTime;

public:
	static CStunEffect*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // StunEffect_h__
