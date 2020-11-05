#include "Camera.h"

USING(Engine)

CCamera::CCamera(void)
	: CComponent()
{
}

CCamera::~CCamera(void)
{
}
void CCamera::Rebound_Camera()
{
	m_iCurBoundInterval = 1;
}
HRESULT CCamera::Initialize_Camera(const _float & fFovY, const _float & fAspect, const _float & fNear, const _float & fFar)
{
	m_fFovY = fFovY;
	m_fAspect = fAspect;
	m_fNear = fNear;
	m_fFar = fFar;

	return S_OK;
}

void CCamera::Set_Distance(const _float & fDistance)
{
	m_fDistance = fDistance;
}

void CCamera::Set_Transform(CTransform * pTransform)
{
	m_pTargetTransform = pTransform;
}

void CCamera::Ready_NormalView(LPDIRECT3DDEVICE9 pGraphicDev)
{
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

inline void CCamera::freeMem(void)
{
	CComponent::freeMem();
}

void CCamera::Shake_Camera(int range)
{
	if (range <= 0)
		return;
	m_fShakeOffsetX = (rand() % (range * 2)) - range;
	m_fShakeOffsetY = (rand() % (range * 2)) - range;
}