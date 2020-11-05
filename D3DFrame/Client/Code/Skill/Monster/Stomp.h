#ifndef Stomp_h__
#define Stomp_h__

#include "../AttackSkillBase.h"

class CStomp : public CAttackSkillBase
{
private:
	explicit						CStomp(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CStomp(const CStomp& rhs);
	virtual							~CStomp(void) = default;

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual void					Attack(CGameObject* pTarget) override;

protected:
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	virtual void					check_DeadCondition(void) override;
	virtual void					dead_Effect(void) override;

	Engine::_bool					m_bGiveDamage;
	Engine::_float					m_fCurTime;

public:
	static CStomp*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // Stomp_h__
