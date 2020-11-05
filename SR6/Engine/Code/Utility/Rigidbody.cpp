#include "Rigidbody.h"

#include "Transform.h"
USING(Engine)

const _float CRigidBody::m_fGravity = 9.8f;

CRigidBody::CRigidBody(void)
	: CComponent()
	, m_bJump(true)
	, m_tGravityInfo()
{
}

CRigidBody::CRigidBody(const CRigidBody & rhs)
	: CComponent(rhs)
	, m_bJump(rhs.m_bJump)
{
}

CRigidBody::~CRigidBody(void)
{
}

HRESULT CRigidBody::Late_Initialize()
{
	m_pTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);

	return S_OK;
}

HRESULT CRigidBody::Initialize_Component()
{

	return S_OK;
}

_int CRigidBody::Update_Component(const _float & fTimeDelta)
{
	if (!m_bJump)
	{
		m_tGravityInfo.SetInitial();
	}

	return 0;
}

void CRigidBody::LoadData(HANDLE hFile)
{
}

HRESULT CRigidBody::Attach(CGameObject * pObj, COMPONENTID eID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::RIGIDBODY, this, eID);

	return S_OK;
}

_float CRigidBody::Get_Height(const _float& fTimeDelta)
{
	static const _float fGravity = 9.8f;
	static const _float fMaxAcc = 1.0f;

	static _float fAccPerFrame = 1.5f * fTimeDelta;

	m_tGravityInfo.SetAcc(m_tGravityInfo.fAcc + fAccPerFrame);
	if (m_tGravityInfo.fAcc >= fMaxAcc)
	{
		m_tGravityInfo.SetAcc(fMaxAcc);
	}

	const _float fMoveY = -m_tGravityInfo.fPower + fGravity * powf(m_tGravityInfo.fAcc, 2.f) * 0.5f;

	return fMoveY;
}

CRigidBody * CRigidBody::Create(void)
{
	CRigidBody* pInstance = new CRigidBody;

	return pInstance;
}