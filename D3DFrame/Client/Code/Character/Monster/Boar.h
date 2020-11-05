#ifndef Boar_h__
#define Boar_h__

#include "AttackSecondMonster.h"

class CBoar : public CAttackSecondMonster
{
private:
	explicit		CBoar(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CBoar(const CBoar& rhs);
	virtual			~CBoar(void);

private:
	virtual void					print_Name(void) override;
	virtual void					make_Weapon(Engine::CGameObject* pTarget);
	virtual void					initialize_Bones(void) override;

	virtual void					act_AfterHit(const Engine::_float& fTimeDelta) override;

public:
	static CBoar*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // Boar_h__
