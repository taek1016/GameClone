#include "stdafx.h"
#include "StaticCamera.h"

USING(Engine)
CStaticCamera::CStaticCamera(void)
{

}

CStaticCamera::~CStaticCamera(void)
{

}

HRESULT CStaticCamera::Late_Initialize(const _vec3 * pEye, const _vec3 * pAt, const _vec3 * pUp)
{
	m_vEye = *pEye;
	m_vAt = *pAt;
	m_vUp = *pUp;

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return S_OK;
}

Engine::_int CStaticCamera::Update_Component(const Engine::_float& fTimeDelta)
{
	Target_Renewal(fTimeDelta);

	Mouse_Move(fTimeDelta);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return 0;
}

void CStaticCamera::Mouse_Move(const Engine::_float & fTimeDelta)
{
	_long	dwMouseMove = 0;

	// 가까운 3인칭 카메라는 x축 카메라 회전은 안 되야 정상.
	//if (dwMouseMove = DLL::pDirectInput->Get_MouseMove(Engine::DIMS_Y))
	//{
	//	_float	fDegree = dwMouseMove / 10.f * fTimeDelta;

	//	m_pTargetTransform->Rotation(ROT_X, fDegree);

	//	_float	fXDegree = m_pTargetTransform->Get_Angle()->x;

	//	_float	fMinDegree = 43.f;
	//	_float	fMaxDegree = 44.5f;

	//	if (fMinDegree > fXDegree)
	//		m_pTargetTransform->Set_Angle(ROT_X, fMinDegree);

	//	if (fMaxDegree < fXDegree)
	//		m_pTargetTransform->Set_Angle(ROT_X, fMaxDegree);

	//}

	if (dwMouseMove = DLL::pDirectInput->Get_MouseMove(Engine::DIMS_X))
	{
		_float	fDegree = dwMouseMove / 10.f * fTimeDelta;

		m_pTargetTransform->Rotation(ROT_Y, fDegree);
	}
}

void CStaticCamera::Target_Renewal(const Engine::_float& fTimeDelta)
{
	_vec3 vPlayerPos = *m_pTargetTransform->Get_Info(INFO_POS);
	_vec3 vPlayerLook = *m_pTargetTransform->Get_Info(INFO_LOOK);

	m_vAt = vPlayerLook;

	const _float CAMERA_OFFSET = 5.f;

	m_vEye = *D3DXVec3Normalize(&vPlayerLook, &vPlayerLook) * -CAMERA_OFFSET;
	m_vEye *= m_fDistance;
	m_vEye.y += CAMERA_OFFSET;

	m_vEye *= m_fDistance;

	_vec3 vLook;
	m_vAt = *D3DXVec3Normalize(&m_vAt, &m_vAt) + vPlayerPos;
	m_vEye += vPlayerPos;
}

CStaticCamera * CStaticCamera::Create(const Engine::_float & fFovY, const Engine::_float & fAspect, const Engine::_float & fNear, const Engine::_float & fFar)
{
	CStaticCamera* pInstance = new CStaticCamera();

	if (FAILED(pInstance->Initialize_Camera(fFovY, fAspect, fNear, fFar)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CStaticCamera::freeMem(void)
{
	CCamera::freeMem();
}

