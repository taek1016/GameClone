#include "ControllerBase.h"

#include "Transform.h"
#include "DynamicMesh.h"

USING(Engine)

CControllerBase::CControllerBase(CGameObject* pTarget)
	: m_pTarget(pTarget)
	, m_pTargetDynamicMesh(nullptr)
	, m_pTargetTransform(nullptr)
{
	m_pTarget->AddRef();

}

CControllerBase::CControllerBase(const CControllerBase & rhs)
	: CComponent(rhs)
	, m_pTarget(rhs.m_pTarget)
{
	m_pTarget->AddRef();
}

CControllerBase::~CControllerBase(void)
{
}

HRESULT CControllerBase::Late_Initialize(void)
{
	m_pTargetTransform = m_pTarget->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTargetTransform->AddRef();

	m_pTargetDynamicMesh = m_pTarget->Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC);
	m_pTargetDynamicMesh->AddRef();

	return S_OK;
}

void CControllerBase::get_TargetLook(void)
{
	m_vDir = *m_pTargetTransform->Get_Info(INFO::INFO_LOOK);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

inline void CControllerBase::Free(void)
{
	CComponent::Free();
	Safe_Release(m_pTargetTransform);
	Safe_Release(m_pTargetDynamicMesh);
	Safe_Release(m_pTarget);
}
