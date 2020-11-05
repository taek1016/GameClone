#include "stdafx.h"
#include "PersonCamera.h"

USING(Engine)
CPersonCamera::CPersonCamera(void)
{

}

CPersonCamera::~CPersonCamera(void)
{

}

HRESULT CPersonCamera::Late_Initialize(const _vec3 * pEye, const _vec3 * pAt, const _vec3 * pUp)
{
	m_vEye = *pEye;
	m_vAt = *pAt;
	m_vUp = *pUp;

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_pGameObject = DLL::pSearchMgr->Get_Object(L"Player");
	m_iCurBoundInterval = 1;
	return S_OK;
}

Engine::_int CPersonCamera::Update_Component(const Engine::_float& fTimeDelta)
{
	Target_Renewal(fTimeDelta);

	Mouse_Move(fTimeDelta);
	//Mouse_Fix();

	m_pTargetTransform->Rotation(ROT_Y, D3DXToRadian(m_fShakeOffsetY / 2.5));
	m_pTargetTransform->Rotation(ROT_X, D3DXToRadian(m_fShakeOffsetX / 2.5));

	if (m_iCurBoundInterval != 0 && !m_bBackBound)
		m_pTargetTransform->Rotation(ROT_X, D3DXToRadian((-70 / (m_iCurBoundInterval += 10))));

	if (m_iCurBoundInterval >= 30 && !m_bBackBound)
	{
		m_iCurBoundInterval = 1;
		m_bBackBound = true;
	}

	if (m_bBackBound)
	{
		m_pTargetTransform->Rotation(ROT_X, D3DXToRadian((10 / (m_iCurBoundInterval += 1))));
	}
	if (m_bBackBound && m_iCurBoundInterval >= 30)
	{
		m_iCurBoundInterval = 0;
		m_bBackBound = false;
	}

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	m_fShakeOffsetX = 0;
	m_fShakeOffsetY = 0;
	return 0;
}

void CPersonCamera::Mouse_Fix(void)
{
	POINT      ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

void CPersonCamera::Mouse_Move(const Engine::_float & fTimeDelta)
{
	_long   dwMouseMove = 0;

	if (dwMouseMove = DLL::pDirectInput->Get_MouseMove(Engine::DIMS_Y))
	{
		_float   fDegree = dwMouseMove / 10.f;

		m_pTargetTransform->Rotation(ROT_X, D3DXToRadian(fDegree));

		_float   fXDegree = m_pTargetTransform->Get_Angle()->x;

		_float   fMinDegree = 43.f;
		_float   fMaxDegree = 44.f;

		if (fMinDegree > fXDegree)
			m_pTargetTransform->Set_Angle(ROT_X, fMinDegree);

		if (fMaxDegree < fXDegree)
			m_pTargetTransform->Set_Angle(ROT_X, fMaxDegree);
	}

	if (dwMouseMove = DLL::pDirectInput->Get_MouseMove(Engine::DIMS_X))
	{
		_float   fDegree = dwMouseMove / 10.f;

		m_pTargetTransform->Rotation(ROT_Y, D3DXToRadian(fDegree));
	}
}

void CPersonCamera::Target_Renewal(const Engine::_float& fTimeDelta)
{
	_vec3 vPlayerPos = *m_pTargetTransform->Get_Info(INFO_POS);
	_vec3 vPlayerLook = *m_pTargetTransform->Get_Info(INFO_LOOK);

	m_vEye = *m_pTargetTransform->Get_Info(Engine::INFO_POS);
	m_vEye.y += 0.5f;
	m_vAt = vPlayerPos + vPlayerLook;
}

CPersonCamera * CPersonCamera::Create(const Engine::_float & fFovY, const Engine::_float & fAspect, const Engine::_float & fNear, const Engine::_float & fFar)
{
	CPersonCamera* pInstance = new CPersonCamera();

	if (FAILED(pInstance->Initialize_Camera(fFovY, fAspect, fNear, fFar)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPersonCamera::freeMem(void)
{
	CCamera::freeMem();
}
