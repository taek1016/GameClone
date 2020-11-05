#ifndef SummonMeteor_h__
#define SummonMeteor_h__

#include "../TextureSkillBase.h"

class CSummonMeteor : public CTextureSkillBase
{
private:
	explicit						CSummonMeteor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CSummonMeteor(const CSummonMeteor& rhs);
	virtual							~CSummonMeteor(void) = default;

private:
	virtual void					check_TextureIndex(const Engine::_float& fTimeDelta) override;
	virtual void					dead_Action(const Engine::_float& fTimeDelta) override;
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;

	void							summon_Meteor(const Engine::_vec3* pPos);

	Engine::_float					m_fLifeTime;

public:
	static CSummonMeteor*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // SummonMeteor_h__
