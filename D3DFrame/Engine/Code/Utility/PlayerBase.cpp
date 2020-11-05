#include "PlayerBase.h"

USING(Engine)

CPlayerBase::CPlayerBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CPlayerBase::CPlayerBase(const CPlayerBase & rhs)
	: CGameObject(rhs)
{
}

CPlayerBase::~CPlayerBase(void)
{
}
