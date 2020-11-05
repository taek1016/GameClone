#ifndef AttackSecondMonster_h__
#define AttackSecondMonster_h__

#include "../Monster.h"

class CAttackSecondMonster : public CMonsterBase
{
protected:
	explicit		CAttackSecondMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CAttackSecondMonster(const CAttackSecondMonster& rhs);
	virtual			~CAttackSecondMonster(void) = default;

protected:
	virtual void	act_AfterHit(const Engine::_float& fTimeDelta) PURE;
	virtual void	act_Determine(const Engine::_float& fTimeDelta);

};

#endif // AttackSecondMonster_h__
