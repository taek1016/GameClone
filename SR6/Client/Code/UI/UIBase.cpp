#include "stdafx.h"
#include "UIBase.h"

CUIBase::CUIBase(void)
	: CGameObject()
{
}

CUIBase::~CUIBase(void)
{
}

void CUIBase::freeMem(void)
{
	CGameObject::freeMem();
	m_pTarget = nullptr;
}
