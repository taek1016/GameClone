#include "stdafx.h"
#include "SkyBox.h"

USING(Engine)
CSkyBox::CSkyBox(void)
	: CGameObject()
{
	SetName(L"SkyBox");
}

CSkyBox::~CSkyBox(void)
{
}

HRESULT CSkyBox::Initialize_GameObject()
{
	Engine::CComponent*		pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<Engine::CCubeTex*>(DLL::pResourceMgr->Clone(RESOURCE_STATIC, L"Buffer_CubeTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Attach(this, ID_STATIC);

	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Texture_SkyBox"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Attach(this, ID_STATIC);

	pComponent = m_pTransformCom = Engine::CTransform::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->Attach(this, ID_DYNAMIC);

	m_pTransformCom->Set_Scale(40.f, 40.f, 40.f);

	return S_OK;
}

Engine::_int CSkyBox::Update_GameObject(const _float & fTimeDelta)
{
	_matrix	matCamWorld;
	DLL::pGraphicDev->GetDevice()->GetTransform(D3DTS_VIEW, &matCamWorld);

	D3DXMatrixInverse(&matCamWorld, NULL, &matCamWorld);

	m_pTransformCom->Set_Pos(matCamWorld._41, matCamWorld._42 + 3.f, matCamWorld._43);

	Engine::CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDER_PRIORITY, this);

	return 0;
}

void CSkyBox::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();
	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pTextureCom->Render_Texture();
	m_pBufferCom->Render_Buffer();
}

CSkyBox * CSkyBox::Create(void)
{
	CSkyBox*	pInstance = new CSkyBox();

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
