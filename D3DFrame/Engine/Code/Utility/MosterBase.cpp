#include "stdafx.h"
#include "MosterBase.h"

USING(Engine)

CMonsterBase::CMonsterBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCharacterBase(pGraphicDev)
{
}

CMonsterBase::CMonsterBase(const CMonsterBase & rhs)
	: CCharacterBase(rhs)
{
}

CMonsterBase::~CMonsterBase(void)
{
}
