#ifndef KodoBeast_h__
#define KodoBeast_h__

#include "AttackFirstMonster.h"

class CKodoBeast : public CAttackFirstMonster
{
	enum KODO_PATTERN				{ KODO_ATTACK, KODO_HIT, KODO_END };

private:
	explicit						CKodoBeast(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CKodoBeast(const CKodoBeast& rhs);
	virtual							~CKodoBeast(void) = default;

private:
	virtual void					print_Name(void) override;
	virtual void					make_Weapon(Engine::CGameObject* pTarget) override;
	void							initialize_ActionCols(void);

	virtual void					act_Determine(const Engine::_float& fTimeDelta) override;
	void							attack_Target(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							hit_Action(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);
	void							move_Pattern(Engine::CGameObject* pPlayer, const Engine::_float& fTimeDelta);

	Engine::_int					m_iCurPattern;

public:
	static CKodoBeast*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // KodoBeast_h__
