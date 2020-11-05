#include "Component.h"

USING(Engine)

Engine::CComponent::CComponent(void)
{
}

CComponent::CComponent(const CComponent& rhs)
	: m_pGameObject(rhs.m_pGameObject),
	m_eComType(rhs.m_eComType)
{
}

Engine::CComponent::~CComponent(void)
{
}

void CComponent::Set_ComType(COMPONENT_TYPE eType)
{
	m_eComType = eType;
}

void CComponent::freeMem(void)
{
	m_pGameObject = nullptr;
}