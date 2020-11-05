#include "Component.h"

USING(Engine)

CComponent::CComponent(void)
	: CBase()
{
}

CComponent::CComponent(const CComponent& rhs)
	: CBase()
{
}

CComponent::~CComponent(void)
{
}

HRESULT CComponent::Attach(const _tchar* pKey, CGameObject* pObj, COMPONENTID com_ID)
{
	auto iter = pObj->Add_Component(pKey, this, com_ID);

	if (nullptr == iter)
	{
		return E_FAIL;
	}

	return S_OK;
}

inline void CComponent::Free(void)
{
	m_pGameObject = nullptr;
}