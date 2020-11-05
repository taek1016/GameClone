#ifndef FrostBolt_h__
#define FrostBolt_h__

#include "../AttackSkillBase.h"

class CFrostBolt : public CAttackSkillBase
{
private:
	explicit						CFrostBolt(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CFrostBolt(const CFrostBolt& rhs);
	virtual							~CFrostBolt(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual void					Attack(CGameObject* pTarget) override;

private:
	void							set_Damage(const Engine::_int& iDamage);
	void							set_Target(void);
	virtual void					check_DeadCondition(void) override;
	virtual void					dead_Effect(void) override;

	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;

	Engine::_float					m_fSpeed;
	Engine::CGameObject*			m_pTarget;

public:
	static CFrostBolt*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_float& fRadius);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // FrostBolt_h__
