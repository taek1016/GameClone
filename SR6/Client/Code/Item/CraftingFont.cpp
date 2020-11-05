#include "stdafx.h"
#include "CraftingFont.h"

USING(Engine)

CCraftFont::CCraftFont(void)
	: CGameObject()
{
}

CCraftFont::~CCraftFont(void)
{
}

HRESULT CCraftFont::Initialize_GameObject()
{
	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);

	m_vScale = _vec3(200.f, 50.f, 1.f);
	m_pTransform->Set_Scale(&m_vScale);

	m_vPos = { 0.f, -20.f, 0.f };
	m_pTransform->Set_Pos(&m_vPos);

	return S_OK;
}

Engine::_int CCraftFont::Update_GameObject(const Engine::_float & fTimeDelta)
{
	//if (!m_bActivate)
	//{
	//	return 0;
	//}
	m_fCurTime += fTimeDelta;
	if (m_fCurTime >= m_fEndTime)
	{
		m_fCurTime = 0.f;
		m_bActivate = false;
		DLL::pCraftingMgr->Finish_Craft();
	}

	Engine::_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CCraftFont::Render_GameObject()
{
	DLL::pGraphicDev->GetDevice()->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, m_wstrRenderKey.c_str());
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CCraftFont::Set_Failed()
{
	m_bFailed = true;
	m_bActivate = true;
	m_bFailed == true ? m_wstrRenderKey = L"CannotMake" : m_wstrRenderKey = L"Making";
	m_pTransform->Set_Pos(&m_vPos);
}

void CCraftFont::Set_Succeed()
{
	m_bFailed = false;
	m_bActivate = true;
	m_bFailed == true ? m_wstrRenderKey = L"CannotMake" : m_wstrRenderKey = L"Making";
	m_pTransform->Set_Pos(&m_vPos);
}

CCraftFont * CCraftFont::Create(void)
{
	CCraftFont*	pInstance = new CCraftFont;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CCraftFont::LoadData(HANDLE hFile)
{
}

CGameObject * CCraftFont::Clone(const _vec3 * pPos)
{
	return nullptr;
}
