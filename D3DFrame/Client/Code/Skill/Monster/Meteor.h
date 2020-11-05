#ifndef Meteor_h__
#define Meteor_h__

#include "../AttackSkillBase.h"
class CMeteor : public CAttackSkillBase
{
private:
	explicit						CMeteor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CMeteor(const CMeteor& rhs);
	virtual							~CMeteor(void) = default;

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;
	virtual void					Attack(CGameObject* pTarget) override;

protected:
	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	virtual void					check_DeadCondition(void) override;
	virtual void					dead_Effect(void) override;

public:
	static CMeteor*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // Meteor_h__
