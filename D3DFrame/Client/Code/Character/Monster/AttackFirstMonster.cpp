#include "stdafx.h"
#include "AttackFirstMonster.h"

USING(Engine)

CAttackFirstMonster::CAttackFirstMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonsterBase(pGraphicDev)
{
}

CAttackFirstMonster::CAttackFirstMonster(const CAttackFirstMonster & rhs)
	: CMonsterBase(rhs)
{
}
