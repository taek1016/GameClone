#include "stdafx.h"
#include "HitBox.h"

USING(Engine)

CHitBox::CHitBox(void)
	: CUIBase()
{
}

CHitBox::~CHitBox(void)
{
}

HRESULT CHitBox::Late_Initialize()
{
	_vec3 vScale(800.f, 600.f, 1.f);
	_vec3 vPos(0.f, 0.f, 0.f);

	_matrix matScale, matTrans;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	D3DXMatrixTranslation(&matTrans, vPos.x, vPos.y, vPos.z);

	m_matWorld = matScale * matTrans;

	return S_OK;
}

Engine::_int CHitBox::Update_GameObject(const Engine::_float & fTimeDelta)
{
	Engine::_int iExit = CGameObject::Update_GameObject(fTimeDelta);			//컴포넌트 를 담고 잇는 벡터를 순회 하는 코드이다

	DLL::pRenderer->Add_RenderGroup(Engine::RENDERID::RENDER_UI, this);

	return iExit;
}

void CHitBox::Render_GameObject()
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, &m_matWorld);

	DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, L"Hit");
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
}

CHitBox * CHitBox::Create(void)
{
	CHitBox*	pInstance = new CHitBox;

	return pInstance;
}

void CHitBox::LoadData(HANDLE hFile)
{
}

Engine::CGameObject * CHitBox::Clone(const Engine::_vec3 * pPos)
{
	return nullptr;
}
