#include "ArmorBase.h"

#include "Transform.h"
USING(Engine)

CArmorBase::CArmorBase(void)
	: CItemBase()
{
}

CArmorBase::CArmorBase(const CArmorBase& rhs)
	: CItemBase(rhs)
{
}

CArmorBase::~CArmorBase(void)
{
}

_int CArmorBase::Update_GameObject(const _float & fTimeDelta)
{
	if (m_pGameObject)
	{
		_vec3 vPos = *m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);

		if (m_vecComponent[ID_DYNAMIC][TRANSFORM])
		{
			Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Set_Pos(vPos.x, vPos.y, vPos.z);
		}
	}

	return CGameObject::Update_GameObject(fTimeDelta);
}

void CArmorBase::Set_Item(CGameObject* pObj)
{
	m_pGameObject = pObj;
	if (m_pGameObject)
	{
		m_pGameObject->Set_Armor(this);
	}
}