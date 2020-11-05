#ifndef DoomGuard_h__
#define DoomGuard_h__

#include "AttackFirstMonster.h"

class CDoomGuard : public CAttackFirstMonster
{
	enum DOOM_ACT					{ DOOM_ATTACK, DOOM_STOMP, DOOM_END};

protected:
	explicit						CDoomGuard(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CDoomGuard(const CDoomGuard& rhs);
	virtual							~CDoomGuard(void);

public:
	virtual HRESULT					Initialize_GameObject() override;


private:
	virtual void					make_Weapon(Engine::CGameObject* pTarget);
	void							initialize_ActionCol(void);
	virtual void					print_Name(void) override;
	virtual void					initialize_Bones(void) override;
	virtual void					set_AttackAnimation(void) override;

	void							melee_Attack(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							stomp_Attack(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							move_Pattern(Engine::CGameObject* pPlayer, const Engine::_float & fTimeDelta);

	virtual void					act_Determine(const Engine::_float& fTimeDelta);
	virtual Engine::_bool			skill_Act(void) override;
	virtual Engine::_bool			attack_Act(void) override;

public:
	static CDoomGuard*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // DoomGuard_h__
