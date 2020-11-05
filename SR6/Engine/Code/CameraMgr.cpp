#include "CameraMgr.h"

#include "Transform.h"

#include "Engine_Entry.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::~CCameraMgr(void)
{
	freeMem();
}

void CCameraMgr::Initialize_CameraMgr(const _int & iMaxCamera)
{
	freeMem();
	m_iMaxCamera = iMaxCamera;
	m_vecCamera.resize(m_iMaxCamera);

	m_pGraphicDev = Ready_GraphicDev()->GetDevice();
}
void CCameraMgr::Rebound_Camera()
{
	m_vecCamera[m_iCurCamera]->Rebound_Camera();
}

void CCameraMgr::Late_Initialize(const _vec3* pEye, const _vec3* pAt, const _vec3* pUp)
{
	for (auto& iter : m_vecCamera)
	{
		if (nullptr == iter)
		{
			continue;
		}
		// 実特
		iter->Late_Initialize(pEye, pAt, pUp);
	}
}

_int CCameraMgr::Update_Camera(const _float fTimeDelta)
{
	return m_vecCamera[m_iCurCamera]->Update_Component(fTimeDelta);
}

HRESULT CCameraMgr::Set_Object(CGameObject* pObj)
{
	for (auto& iter : m_vecCamera)
	{
		if (nullptr == iter)
		{
			continue;
		}
		// 実特
		iter->Set_Transform(pObj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC));
	}

	return S_OK;
}

void CCameraMgr::Ready_UI()
{
	if (this == nullptr)
	{
		return;
	}
	_float fNear = 0.f;
	_float fFar = 1.f;

	_float fHalf = 0.5f;

	_matrix matProj, matView;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixOrthoLH(&matProj, m_fWidth * fHalf, m_fHeight * fHalf, fNear, fFar);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}

void CCameraMgr::End_UI()
{
	if (nullptr == this)
	{
		return;
	}
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CCameraMgr::Ready_NormalView()
{
	if (m_vecCamera[m_iCurCamera])
	{
		m_vecCamera[m_iCurCamera]->Ready_NormalView(m_pGraphicDev);
	}
}

void CCameraMgr::Make_Billboard(CTransform* pTransform)
{
	_matrix matView;
	D3DXMatrixIdentity(&matView);
	matView = *Get_ViewSpace();

	memset(matView.m[3], 0, sizeof(_vec3));
	D3DXMatrixInverse(&matView, 0, &matView);

	_vec3 vBillPos = *pTransform->Get_Info(INFO_POS);
	_vec3 vScale = *pTransform->Get_Scale();
	vScale.z = 1.f;

	memcpy(&matView._41, &vBillPos, sizeof(_vec3));

	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			matView.m[i][j] *= vScale[i];
		}
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matView);
}

_matrix CCameraMgr::Get_Billboard(CTransform * pTransform)
{
	_matrix matView;
	D3DXMatrixIdentity(&matView);
	matView = *Get_ViewSpace();

	memset(matView.m[3], 0, sizeof(_vec3));
	D3DXMatrixInverse(&matView, 0, &matView);

	_vec3 vBillPos = *pTransform->Get_Info(INFO_POS);
	_vec3 vScale = *pTransform->Get_Scale();
	vScale.z = 1.f;

	memcpy(&matView._41, &vBillPos, sizeof(_vec3));

	for (_int i = 0; i < 3; ++i)
	{
		for (_int j = 0; j < 4; ++j)
		{
			matView.m[i][j] *= vScale[i];
		}
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matView);

	return matView;
}

void CCameraMgr::Shake_Camera(_int range)
{
	m_vecCamera[m_iCurCamera]->Shake_Camera(range);
}

inline void CCameraMgr::freeMem()
{
	for (_int i = 0; i < m_iMaxCamera; ++i)
	{
		Safe_Release(m_vecCamera[i]);
	}
	m_vecCamera.clear();
}