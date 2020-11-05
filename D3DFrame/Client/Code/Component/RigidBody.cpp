#include "stdafx.h"
#include "RigidBody.h"

USING(Engine)

CRigidBody::CRigidBody(const Engine::_float& fDefaultPower, const Engine::_float& fMaxPower)
	: CComponent()
	, m_bActivated(false)
	, m_fPower(fDefaultPower)
	, m_fAccTime(0.f)
	, m_pTargetTransform(nullptr)

	, m_fDefaultPower(fDefaultPower)
	, m_fMaxPower(fMaxPower)
{
}

CRigidBody::CRigidBody(const CRigidBody & rhs)
	: CComponent(rhs)
	, m_bActivated(false)
	, m_fPower(0.f)
	, m_fAccTime(0.f)
	, m_pTargetTransform(nullptr)

	, m_fDefaultPower(rhs.m_fDefaultPower)
	, m_fMaxPower(rhs.m_fMaxPower)
{
}

Engine::_int CRigidBody::Update_Component(const Engine::_float & fTimeDelta)
{
	if (true == m_bActivated)
	{
		m_fAccTime += fTimeDelta;

		m_fPower += m_fMaxPower * fTimeDelta;
		if (m_fPower >= m_fMaxPower)
		{
			m_fPower = m_fMaxPower;
		}
	}

	return 0;
}

HRESULT CRigidBody::Attach(const _tchar * pKey, CGameObject * pObj, COMPONENTID com_ID)
{
	CComponent::Attach(pKey, pObj, com_ID);

	m_pTargetTransform = pObj->Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTargetTransform->AddRef();

	return S_OK;
}

void CRigidBody::Activate(const Engine::_bool & bActivate)
{
	m_bActivated = bActivate;

	if (false == m_bActivated)
	{
		m_fAccTime = 0.f;
		m_fPower = m_fDefaultPower;
	}
}

const Engine::_float CRigidBody::Get_YPos(void)
{
	const _float fHalf = 0.5f;
	const _float fGravity = 9.8f;

	return m_fPower * m_fAccTime - fHalf * fGravity * powf(m_fAccTime, 2.f);
}

CRigidBody * CRigidBody::Create(const Engine::_float& fDefaultPower, const Engine::_float& fMaxPower)
{
	return new CRigidBody(fDefaultPower, fMaxPower);
}

Engine::CComponent * CRigidBody::Clone(void)
{
	return new CRigidBody(*this);
}

inline void CRigidBody::Free(void)
{
	CComponent::Free();

	Safe_Release(m_pTargetTransform);
}
