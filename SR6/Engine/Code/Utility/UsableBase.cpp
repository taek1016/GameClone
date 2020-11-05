#include "UsableBase.h"

USING(Engine)

CUsableBase::CUsableBase(void)
	: CItemBase()
{
}

CUsableBase::CUsableBase(const CUsableBase & rhs)
	: CItemBase(rhs)
{
}

CUsableBase::~CUsableBase(void)
{
}

_int CUsableBase::Update_Component(const _float & fTimeDelta)
{
	return 0;
}

void CUsableBase::Use()
{
	if (m_pGameObject)
	{

	}
}

void CUsableBase::Set_Item(CGameObject * pObj)
{
}

void CUsableBase::LoadData(HANDLE hFile)
{
}