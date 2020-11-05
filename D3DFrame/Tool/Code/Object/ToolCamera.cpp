#include "stdafx.h"
#include "ToolCamera.h"

USING(Engine)

CToolCamera::CToolCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CCamera(pGraphicDev)
	, m_fSpeed(0.f)
{
}

CToolCamera::~CToolCamera(void)
{
}

HRESULT CToolCamera::Late_Initialize(const Engine::_vec3* pEye, const Engine::_vec3* pAt, const Engine::_vec3* pUp)
{
	set_ViewData(pEye, pAt, pUp);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovY, m_fAspect, m_fNear, m_fFar);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_matProj);

	Set_Speed(20.f);

	return S_OK;
}


_int CToolCamera::Update_GameObject(const Engine::_float & fTimeDelta)
{
	target_Renewal(fTimeDelta);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

	return 0;
}

void CToolCamera::Set_Speed(const Engine::_float & fSpeed)
{
	m_fSpeed = fSpeed;
}

void CToolCamera::target_Renewal(const Engine::_float & fTimeDelta)
{
	_matrix	matCamWorld;
	D3DXMatrixInverse(&matCamWorld, NULL, &m_matView);

	if (DLL::pInputMgr->KeyPressing(DIK_W))
	{
		_vec3	vLook(0.f, 0.f, 1.f);
		memcpy(&vLook, matCamWorld.m[2], sizeof(_vec3));
		vLook.y = 0.f;

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * 0.5f;

		m_vEye += vLength;
		m_vAt += vLength;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_S))
	{
		_vec3	vLook(0.f, 0.f, 1.f);
		memcpy(&vLook, matCamWorld.m[2], sizeof(_vec3));
		vLook.y = 0.f;

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * 0.5f;

		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_R))
	{
		_vec3	vLook;
		memcpy(&vLook, matCamWorld.m[2], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * 0.5f;

		m_vEye += vLength;
		m_vAt += vLength;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_F))
	{
		_vec3	vLook;
		memcpy(&vLook, matCamWorld.m[2], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * 0.5f;

		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_A))
	{
		_vec3	vRight;
		memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * 0.5f;

		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_D))
	{
		_vec3	vRight;
		memcpy(&vRight, &matCamWorld.m[0][0], sizeof(_vec3));

		_vec3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * 0.5f;

		m_vEye += vLength;
		m_vAt += vLength;
	}

	_float fDeltaAngle = 45.f;
	fDeltaAngle *= fTimeDelta;
	if (DLL::pInputMgr->KeyPressing(DIK_E))
	{
		_vec3	vUp;
		memcpy(&vUp, &matCamWorld.m[1][0], sizeof(_vec3));

		_vec3	vLook = m_vAt - m_vEye;

		_matrix		matRotAxis;
		D3DXMatrixRotationAxis(&matRotAxis, &vUp, D3DXToRadian(fDeltaAngle));

		D3DXVec3TransformNormal(&vLook, &vLook, &matRotAxis);

		m_vAt = m_vEye + vLook;

	}
	else if (DLL::pInputMgr->KeyPressing(DIK_Q))
	{
		_vec3	vUp;
		memcpy(&vUp, &matCamWorld.m[1][0], sizeof(_vec3));

		_vec3	vLook = m_vAt - m_vEye;

		_matrix		matRotAxis;
		D3DXMatrixRotationAxis(&matRotAxis, &vUp, D3DXToRadian(-fDeltaAngle));

		D3DXVec3TransformNormal(&vLook, &vLook, &matRotAxis);

		m_vAt = m_vEye + vLook;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_Z))
	{
		_vec3 vRight;
		memcpy(&vRight, matCamWorld.m[0], sizeof(_vec3));

		_vec3 vLook = m_vAt - m_vEye;

		_matrix matRotAxis;
		D3DXMatrixRotationAxis(&matRotAxis, &vRight, D3DXToRadian(fDeltaAngle));
		
		D3DXVec3TransformNormal(&vLook, &vLook, &matRotAxis);

		m_vAt = m_vEye + vLook;
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_X))
	{
		_vec3 vRight;
		memcpy(&vRight, matCamWorld.m[0], sizeof(_vec3));

		_vec3 vLook = m_vAt - m_vEye;

		_matrix matRotAxis;
		D3DXMatrixRotationAxis(&matRotAxis, &vRight, D3DXToRadian(-fDeltaAngle));

		D3DXVec3TransformNormal(&vLook, &vLook, &matRotAxis);

		m_vAt = m_vEye + vLook;
	}
}

CToolCamera * CToolCamera::Create(const Engine::_float& fFovY, const Engine::_float& fAspect, const Engine::_float& fNear, const Engine::_float& fFar)
{
	CToolCamera* pInstance = new CToolCamera(DLL::pGraphicDev->GetDevice());

	if (FAILED(pInstance->Initialize_Camera(fFovY, fAspect, fNear, fFar)))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CToolCamera::Clone()
{
	return nullptr;
}
