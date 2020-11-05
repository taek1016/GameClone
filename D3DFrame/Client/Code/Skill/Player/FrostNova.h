#ifndef FrostNova_h__
#define FrostNova_h__

#include "../AttackSkillBase.h"

class CFrostNova : public CAttackSkillBase
{
private:
	explicit						CFrostNova(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CFrostNova(const CFrostNova& rhs);
	virtual							~CFrostNova(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Attack(CGameObject* pTarget) override;

private:
	void							set_Damage(const Engine::_int& iDamage);
	virtual void					check_DeadCondition(void) override;
	virtual void					dead_Effect(void) override;

	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;

	void							set_Radius(const Engine::_float& fRaidius);

	Engine::_float					m_fColRadius;
	Engine::_bool					m_bAttack;
	Engine::_float					m_fDuration;
	Engine::_float					m_fCurTime;

public:
	static CFrostNova*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_float& fRadius);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // FrostNova_h__
