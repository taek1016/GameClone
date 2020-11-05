#include "Camera.h"

#include "Transform.h"

USING(Engine)

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CCamera::CCamera(const CCamera& rhs)
	: CGameObject(rhs)
{
}

CCamera::~CCamera(void)
{
}

HRESULT CCamera::Initialize_Camera(const _float & fFovY, const _float & fAspect, const _float & fNear, const _float & fFar)
{
	set_ProjData(fFovY, fAspect, fNear, fFar);

	return S_OK;
}

void CCamera::set_ProjData(const _float& fFovY, const _float& fAspect, const _float& fNear, const _float& fFar)
{
	m_fFovY = fFovY;
	m_fAspect = fAspect;
	m_fNear = fNear;
	m_fFar = fFar;
}

void CCamera::set_ViewData(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp)
{
	m_vEye = *pEye;
	m_vAt = *pAt;
	m_vUp = *pUp;
}

const _matrix * CCamera::Get_ViewSpace(void)
{
	return &m_matView;
}

const _matrix * CCamera::Get_Projection(void)
{
	return &m_matProj;
}

const _vec3* CCamera::Get_At() const
{
	return &m_vAt;
}

const _vec3* CCamera::Get_Eye() const
{
	return &m_vEye;
}

void CCamera::Set_Transform(CTransform* pTransform)
{
	m_pTargetTransform = pTransform;
	m_pTargetTransform->AddRef();
}

void CCamera::Set_Distance(const _float& fDistance)
{
	m_fDistance = fDistance;
}

void CCamera::Free(void)
{
	CGameObject::Free();
	Safe_Release(m_pTargetTransform);
}