#ifndef Infernal_h__
#define Infernal_h__

#include "AttackFirstMonster.h"

class CInfernal : public CAttackFirstMonster
{
	enum INFERNAL_ACT	{ INFERNAL_STAND, INFERNAL_ATTACK, INFERNAL_DIE, INFERNAL_HIT, INFERNAL_END };

private:
	explicit						CInfernal(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CInfernal(const CInfernal& rhs);
	virtual							~CInfernal(void) = default;

private:
	virtual void					print_Name(void) override;
	virtual void					make_Weapon(Engine::CGameObject* pTarget);
	void							initialize_ActionCols(void);

	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	void							attack_Target(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							hit_Action(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							move_Pattern(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);

	Engine::_int					m_iCurPattern;

public:
	static CInfernal*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // Infernal_h__