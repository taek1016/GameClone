#include "ItemBase.h"

#include "Transform.h"

USING(Engine)

CItemBase::CItemBase(void)
	: CGameObject()
{
}

CItemBase::CItemBase(const CItemBase& rhs)
	: CGameObject(rhs)
{
}

CItemBase::~CItemBase(void)
{
}

void CItemBase::Set_Pos(const Engine::_vec3 * pPos)
{
	if (m_vecComponent[ID_DYNAMIC][TRANSFORM])
	{
		Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Pos(pPos);
	}
}

void CItemBase::freeMem(void)
{
	CGameObject::freeMem();
	m_pGameObject = nullptr;
}