#include "stdafx.h"
#include "FirstPersonView.h"

USING(Engine)

CFirstPersonView::CFirstPersonView(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCamera(pGraphicDev)
	, m_fDistance(20.f)
	
	, m_vRotAxis(0.f, 0.f, 0.f)
	, m_vTargetEye(0.f, 0.f, 0.f)
	, m_vPreviousEye(0.f, 0.f, 0.f)

	, m_fAngle(0.f)
	, m_fAngleX(0.f)
	, m_fAngleY(0.f)
	
	, m_bAutoCamera(true)
{
}

CFirstPersonView::CFirstPersonView(const CFirstPersonView & rhs)
	: CCamera(rhs)
{
}

CFirstPersonView::~CFirstPersonView(void)
{
}

HRESULT CFirstPersonView::Late_Initialize(const Engine::_vec3 * pEye, const Engine::_vec3 * pAt, const Engine::_vec3 * pUp)
{
	set_ViewData(pEye, pAt, pUp);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	Set_Distance(m_fDistance);

	return S_OK;
}

Engine::_int CFirstPersonView::Update_GameObject(const Engine::_float & fTimeDelta)
{
	key_Input(fTimeDelta);
	target_Renewal(fTimeDelta);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return 0;
}

void CFirstPersonView::Set_Transform(Engine::CTransform * pTransform)
{
	CCamera::Set_Transform(pTransform);

	get_TargetBehind(1.f);
	target_Renewal(1.f);
}

void CFirstPersonView::get_FrontShot(const Engine::_float & fTimeDelta)
{
	m_vTargetEye = *m_pTargetTransform->Get_Info(INFO_LOOK);
	m_vRotAxis = *m_pTargetTransform->Get_Info(INFO_RIGHT);
	m_fAngle = -60.f;
}

void CFirstPersonView::get_TargetBehind(const Engine::_float & fTimeDelta)
{
	m_vPreviousEye = m_vEye;
	m_vTargetEye = *m_pTargetTransform->Get_Info(INFO_LOOK) * -1.f;
	m_vRotAxis = *m_pTargetTransform->Get_Info(INFO_RIGHT);
	m_fAngle = 60.f;
	m_bAutoCamera = true;
}

void CFirstPersonView::key_Input(const Engine::_float & fTimeDelta)
{
	_long dwMove = 0;
	if (dwMove = DLL::pInputMgr->Get_MouseMove(MOUSEMOVESTATE::DIMS_Z))
	{
		_float fWheelMovePerSec = 50.f;

		if (dwMove < 0)
		{
			fWheelMovePerSec = -fWheelMovePerSec;
		}

		m_fDistance += fWheelMovePerSec * fTimeDelta;

		const _float fMinLimit = 10.f;
		const _float fMaxLimit = 30.f;
		if (m_fDistance < fMinLimit)
		{
			m_fDistance = fMinLimit;
		}

		if (m_fDistance > fMaxLimit)
		{
			m_fDistance = fMaxLimit;
		}
	}

	if (DLL::pInputMgr->KeyPressing(DIK_W) || DLL::pInputMgr->KeyPressing(DIK_S))
	{
		get_TargetBehind(fTimeDelta);
	}
	
	else if (DLL::pInputMgr->MousePress(DIM_RB))
	{
		if (m_bAutoCamera)
		{
			m_fAngleX = m_fAngle;
			m_fAngleY = m_fAngle;
		}

		m_bAutoCamera = false;

		_long dwMove = 0;
		const _float fRotationSpeed = 120.f * fTimeDelta;
		_float fWay = 1.f;

		if (dwMove = DLL::pInputMgr->Get_MouseMove(DIMS_Y))
		{
			if (dwMove < 0)
			{
				fWay = -1.f;
			}
			m_fAngleX += fRotationSpeed * fWay;

			const _float fLimitUp = 80.f;
			const _float fLimitDown = -80.f;

			if (m_fAngleX >= fLimitUp)
			{
				m_fAngleX = fLimitUp;
			}
			else if (m_fAngleX <= fLimitDown)
			{
				m_fAngleX = fLimitDown;
			}
		}

		if (dwMove = DLL::pInputMgr->Get_MouseMove(DIMS_X))
		{
			if (dwMove < 0)
			{
				fWay = -1.f;
			}

			m_fAngleY += fRotationSpeed * fWay;
		}
	}
}

void CFirstPersonView::target_Renewal(const Engine::_float & fTimeDelta)
{
	m_vEye = m_vTargetEye;
	D3DXVec3Normalize(&m_vEye, &m_vEye);

	m_vEye *= m_fDistance;
	_matrix	matRotAxis;

	if (m_bAutoCamera)
	{
		D3DXMatrixRotationAxis(&matRotAxis, &m_vRotAxis, D3DXToRadian(m_fAngle));
	}
	else
	{
		_matrix matRotX, matRotY;

		D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngleX));

		D3DXMatrixRotationY(&matRotY,  D3DXToRadian(m_fAngleY));

		matRotAxis = matRotX * matRotY;
	}

	const _vec3* pPos = m_pTargetTransform->Get_Info(INFO_POS);

	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	m_vEye += *pPos;
	D3DXVec3Lerp(&m_vEye, &m_vPreviousEye, &m_vEye, fTimeDelta * 4.f);
	m_vPreviousEye = m_vEye;
	m_vAt = *pPos;
}

CFirstPersonView * CFirstPersonView::Create(const Engine::_float & fFovY, const Engine::_float & fAspect, const Engine::_float & fNear, const Engine::_float & fFar)
{
	CFirstPersonView* pInstance = new CFirstPersonView(DLL::pGraphicDev->GetDevice());

	if (FAILED(pInstance->Initialize_Camera(fFovY, fAspect, fNear, fFar)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CFirstPersonView::Clone()
{
	return nullptr;
}
