#include "CameraMgr.h"

#include "Transform.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr(void)
	: CBase()
	, m_iMaxCamera(0)
	, m_iCurCamera(0)

	, m_fWidth(0.f)
	, m_fHeight(0.f)
{
}

CCameraMgr::~CCameraMgr(void)
{
	Free();
}

const _int CCameraMgr::Get_CurCamera(void)
{
	return m_iCurCamera;
}

const _vec3 * CCameraMgr::Get_At() const
{
	return m_vecCamera[m_iCurCamera]->Get_At();
}

const _vec3 * CCameraMgr::Get_Eye() const
{
	return m_vecCamera[m_iCurCamera]->Get_Eye();
}

const _matrix * CCameraMgr::Get_ViewSpace(void)
{
	return m_vecCamera[m_iCurCamera]->Get_ViewSpace();
}

const _matrix * CCameraMgr::Get_Projection(void)
{
	return m_vecCamera[m_iCurCamera]->Get_Projection();
}

void CCameraMgr::Set_Window(const _float & fWidth, const _float & fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
}

void CCameraMgr::Initialize_CameraMgr(const _int& iMaxCamera)
{
	Free();
	m_iMaxCamera = iMaxCamera;
	m_vecCamera.resize(m_iMaxCamera);

	//m_pGraphicDev = Get_GraphicDev()->GetDevice();
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

_int CCameraMgr::Update_Camera(const _float& fTimeDelta)
{
	return m_vecCamera[m_iCurCamera]->Update_GameObject(fTimeDelta);
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
		iter->Set_Transform(pObj->Get_Component<CTransform>(L"Transform", ID_DYNAMIC));
	}

	return S_OK;
}

void CCameraMgr::Ready_NormalView()
{
}

void CCameraMgr::Make_Billboard(CTransform* pTransform)
{
	_matrix matBillBoard = Get_Billboard(pTransform);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matBillBoard);
}

_matrix CCameraMgr::Get_Billboard(CTransform* pTransform)
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

	return matView;
}

inline void CCameraMgr::Free()
{
	for (_int i = 0; i < m_iMaxCamera; ++i)
	{
		Safe_Release(m_vecCamera[i]);
	}
	m_vecCamera.clear();
}