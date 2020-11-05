#include "stdafx.h"
#include "MouseBase.h"

USING(Engine)

CMouseBase::CMouseBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pBuffer(nullptr)
	, m_pTexture(nullptr)
{
}

HRESULT CMouseBase::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);
	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, Get_Name())->Attach(L"Texture", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CMouseBase::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	m_pTexture = Get_Component<CTexture>(L"Texture", ID_STATIC);
	m_pBuffer = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	return S_OK;
}

Engine::_int CMouseBase::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CMouseBase::Render_GameObject(void)
{
}

Engine::CGameObject * CMouseBase::Clone(void)
{
	return nullptr;
}