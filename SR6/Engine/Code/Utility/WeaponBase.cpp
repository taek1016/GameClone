#include "WeaponBase.h"

#include "Transform.h"

USING(Engine)

CWeaponBase::CWeaponBase(void)
	: CItemBase()
{
}

CWeaponBase::CWeaponBase(const CWeaponBase & rhs)
	: CItemBase(rhs)
{
}

CWeaponBase::~CWeaponBase(void)
{
}

_int CWeaponBase::Update_GameObject(const _float & fTimeDelta)
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

void CWeaponBase::Set_Obj(CGameObject * pOwnObj)
{
	m_pGameObject = pOwnObj;
}
