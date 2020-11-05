#include "stdafx.h"
#include "BackGround.h"

USING(Engine)

CBackGround::CBackGround(void)
	: CGameObject()
{
}

CBackGround::~CBackGround(void)
{
}

HRESULT CBackGround::Initialize_GameObject(void)
{
	m_pTransformCom = CTransform::Create();
	m_pTransformCom->Attach(this, ID_DYNAMIC);

	m_pTransformCom->Set_Scale(static_cast<_float>(WINCX), static_cast<_float>(WINCY), 1.f);

	return S_OK;
}

_int CBackGround::Update_GameObject(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDER_UI, this);

	return 0;
}

void CBackGround::Render_GameObject(void)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	DLL::pResourceMgr->Render_Texture(RESOURCE_LOGO, m_wStrKey.c_str());
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

void CBackGround::SetKey(const wstring & wStrKey)
{
	m_wStrKey = wStrKey;
}

CBackGround * CBackGround::Create(const wstring & wstrKey)
{
	CBackGround*	pInstance = new CBackGround;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Engine::Safe_Release(pInstance);
	}
	pInstance->SetKey(wstrKey);
	return pInstance;
}

void CBackGround::freeMem(void)
{
	CGameObject::freeMem();
	m_pTransformCom = nullptr;
}

void CBackGround::LoadData(HANDLE hFile)
{
}

CGameObject * CBackGround::Clone(const _vec3 * pPos)
{
	return nullptr;
}
