#include "stdafx.h"
#include "RangeMonster.h"


CRangeMonster::CRangeMonster()
	: CMonster()
{
}

CRangeMonster::~CRangeMonster()
{
}

void CRangeMonster::Act()
{
	SetPreStatus();

	if (m_bAction)
	{
		return;
	}

	SetCurStatus(OBJECT_STATUS::IDLE);

	if (!m_pPlayer)
	{
		return;
	}

	InitializeMove();

	if (m_pAttackRect->GetCanAct())
	{
		if (m_fAttackCool.GetNextCool())
		{
			Attack();
		}
	}
}
