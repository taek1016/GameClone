#include "stdafx.h"
#include "ItemBase.h"

USING(Engine)

CItemBase::CItemBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pShaderCom(nullptr)
{
}

CItemBase::CItemBase(const CItemBase& rhs)
	: CGameObject(rhs)
	, m_pShaderCom(nullptr)
{
}

CItemBase::~CItemBase(void)
{
}
