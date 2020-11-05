#ifndef DragonBreath_h__
#define DragonBreath_h__

#include "../TextureSkillBase.h"

class CDragonBreath : public CTextureSkillBase
{
private:
	explicit						CDragonBreath(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CDragonBreath(const CDragonBreath& rhs);
	virtual							~CDragonBreath(void) = default;

private:
	Engine::_bool					collide_Object(const Engine::_vec3* pPos);
	virtual void					check_TextureIndex(const Engine::_float& fTimeDelta) override;
	virtual void					dead_Action(const Engine::_float& fTimeDelta) override;
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;

	Engine::_bool					m_bDamageGive;
	Engine::_float					m_fLength;

public:
	static CDragonBreath*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // DragonBreath_h__
