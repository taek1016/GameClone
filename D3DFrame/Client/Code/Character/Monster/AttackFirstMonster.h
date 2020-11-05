#ifndef AttackFirstMonster_h__
#define AttackFirstMonster_h__

#include "../Monster.h"

class CAttackFirstMonster : public CMonsterBase
{
protected:
	explicit		CAttackFirstMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit		CAttackFirstMonster(const CAttackFirstMonster& rhs);
	virtual			~CAttackFirstMonster(void) = default;

public:
};

#endif // AttackFirstMonster_h__
