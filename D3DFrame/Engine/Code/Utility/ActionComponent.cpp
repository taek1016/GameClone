#include "ActionComponent.h"

USING(Engine)

CActionCom::CActionCom(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pName, const _float& fCoolTime)
	: CSphereCollider(pGraphicDev)
	, m_wStrActionName(pName)
	, m_fCoolTime(fCoolTime)
	, m_fCurTime(fCoolTime)
	, m_bCanAction(true)
{
}

CActionCom::CActionCom(const CActionCom& rhs)
	: CSphereCollider(rhs)
	, m_wStrActionName(rhs.m_wStrActionName)
	, m_fCoolTime(rhs.m_fCoolTime)
	, m_fCurTime(rhs.m_fCoolTime)
	, m_bCanAction(true)
{
}

CActionCom::~CActionCom(void)
{
}

HRESULT CActionCom::Initialize_Collider(const _float & fRadius, const _ulong & dwSlice, const _ulong & dwStack, const _matrix* pWorld)
{
	m_fRadius = fRadius;
	D3DXCreateSphere(m_pGraphicDev, m_fRadius, dwSlice, dwStack, &m_pMesh, nullptr);

	m_pWorld = pWorld;

	set_Material();
	set_Texture();

	return S_OK;
}

_int CActionCom::Update_Component(const _float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;
	m_bCanAction = false;
	if (m_fCurTime >= m_fCoolTime)
	{
		m_bCanAction = true;
	}

	return 0;
}

const _bool CActionCom::Can_Act(void)
{
	_bool bCanAct = m_bCanAction;

	if (bCanAct)
	{
		Reset_Act();
	}

	return bCanAct;
}

void CActionCom::Reset_Act(void)
{
	m_fCurTime = 0.f;
	m_bCanAction = false;
}

const _float* CActionCom::Get_CoolTime(void) const
{
	return &m_fCoolTime;
}

const _tchar * CActionCom::Get_Name(void) const
{
	return m_wStrActionName.c_str();
}

CActionCom * CActionCom::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar * pName, const _float & fCoolTime, const _float & fRadius, const _ulong & dwSlice, const _ulong & dwStack, const _matrix* pWorld)
{
	CActionCom* pInstance = new CActionCom(pGraphicDev, pName, fCoolTime);

	if (FAILED(pInstance->Initialize_Collider(fRadius, dwSlice, dwStack, pWorld)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CActionCom::Clone(void)
{
	CActionCom* pInstance = new CActionCom(*this);

	if (FAILED(pInstance->Initialize_Collider(m_fRadius, 10, 10, m_pWorld)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}