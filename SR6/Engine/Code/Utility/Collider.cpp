#include "Collider.h"

#include "Engine_Entry.h"
#include "Transform.h"
USING(Engine)

CCollider::CCollider(void)
	: CResources()
{
}

CCollider::CCollider(const CCollider& rhs)
	: CResources(rhs)
	, m_eColType(rhs.m_eColType)
	, m_eIsCollision(rhs.m_eIsCollision)
{
}

CCollider::~CCollider(void)
{
}

_int CCollider::Update_Component(const _float& fTimeDelta)
{
	if (m_pTransform)
	{
		m_vPos = *m_pTransform->Get_Info(INFO_POS);
	}

	return 0;
}

HRESULT CCollider::Late_Initialize()
{
	m_pTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	return S_OK;
}

HRESULT CCollider::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::COLLIDER, this, ID_DYNAMIC);

	return S_OK;
}

void CCollider::Set_Transform(CTransform * pTransform)
{
	m_pTransform = pTransform;
}

void CCollider::freeMem(void)
{
	CComponent::freeMem();
	m_pTransform = nullptr;
}
