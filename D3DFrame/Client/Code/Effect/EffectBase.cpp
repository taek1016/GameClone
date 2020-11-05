#include "stdafx.h"
#include "EffectBase.h"

USING(Engine)

CEffectBase::CEffectBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CEffectBase::CEffectBase(const CEffectBase & rhs)
	: CGameObject(rhs)
{
}