#include "stdafx.h"
#include "TitleTexture.h"

USING(Engine)

CTitleText::CTitleText(void)
	: CGameObject()
{
}

CTitleText::~CTitleText(void)
{
}

HRESULT CTitleText::Late_Initialize()
{
	return S_OK;
}

HRESULT CTitleText::Initialize_GameObject()
{
	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);

	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_LOGO, L"PressEnter"));

	m_vScale = _vec3(75.f, 20.f, 0.f);
	m_vPos = _vec3(0.f, -100.f, 0.f);

	m_pTransform->Set_Pos(&m_vPos);
	m_pTransform->Set_Scale(&m_vScale);

	return S_OK;
}

Engine::_int CTitleText::Update_GameObject(const _float & fTimeDelta)
{
	m_fCurTime += fTimeDelta;

	if (m_fCurTime >= m_fChangeTime)
	{
		m_fCurTime = 0.f;
		m_bPlusScale = !m_bPlusScale;
	}

	const _float fDeltaScale = 25.f * fTimeDelta;
	if (m_bPlusScale)
	{
		m_vScale.x += fDeltaScale * 2;
		m_vScale.y += fDeltaScale * 0.5f;
	}
	else
	{
		m_vScale.x -= fDeltaScale * 2;
		m_vScale.y -= fDeltaScale * 0.5f;
	}
	m_pTransform->Set_Scale(&m_vScale);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CTitleText::Render_GameObject()
{
	auto pGraphic = DLL::pGraphicDev->GetDevice();

	pGraphic->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	m_pTexture->Render_Texture();
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CTitleText * CTitleText::Create(void)
{
	CTitleText* pInstance = new CTitleText;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTitleText::LoadData(HANDLE hFile)
{
}

CGameObject * CTitleText::Clone(const _vec3 * pPos)
{
	return nullptr;
}
