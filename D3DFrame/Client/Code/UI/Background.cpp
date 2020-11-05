#include "stdafx.h"
#include "Background.h"

USING(Engine)

CBackground::CBackground(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTextures(nullptr)
	, m_pRcTex(nullptr)
	, m_pShader(nullptr)
{
}

CBackground::CBackground(const CBackground & rhs)
	: CGameObject(rhs)
	, m_pTextures(nullptr)
	, m_pRcTex(nullptr)
	, m_pShader(nullptr)
{
}

CBackground::~CBackground(void)
{
}

HRESULT CBackground::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"Transform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, Get_Name())->Attach(L"Texture", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"Buffer", this, ID_STATIC);

	DLL::pShaderMgr->Clone_Shader(L"Shader_Sample")->Attach(L"Shader", this, ID_STATIC);

	return S_OK;
}

HRESULT CBackground::Late_Initialize(void)
{
	m_pTransform = Get_Component<CTransform>(L"Transform", ID_DYNAMIC);
	
	m_pTextures = Get_Component<CTexture>(L"Texture", ID_STATIC);
	
	m_pRcTex = Get_Component<CRcTex>(L"Buffer", ID_STATIC);

	m_pTransform->Set_Scale(&_vec3(WINCX, WINCY, 1.f));
	
	m_pShader = Get_Component<CShader>(L"Shader", ID_STATIC);

	return S_OK;
}

Engine::_int CBackground::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(Engine::RENDER_UI, this);

	return iExit;
}

HRESULT CBackground::SetUp_ConstantTable(LPD3DXEFFECT& pEffect)
{
	_matrix			matWorld, matView, matProj;

	matWorld = *m_pTransform->Get_World();
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &matProj);

	pEffect->SetMatrix("g_matWorld", &matWorld);
	pEffect->SetMatrix("g_matView", &matView);
	pEffect->SetMatrix("g_matProj", &matProj);

	m_pTextures->Set_Texture(pEffect, "g_BaseTexture", (_uint)0);

	return S_OK;
}

void CBackground::Render_GameObject(void)
{
	//m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());
	//
	//m_pTextures->Render_Texture();
	//m_pRcTex->Render_Buffer();
	LPD3DXEFFECT	pEffect = m_pShader->Get_EffectHandle();
	NULL_CHECK(pEffect);
	pEffect->AddRef();

	_uint	iPassMax = 0;


	FAILED_CHECK_RETURN(SetUp_ConstantTable(pEffect), );

	pEffect->Begin(&iPassMax, 0);	// 1인자 : 현재 쉐이더 파일 갖고 있는 최대 패스의 개수

	pEffect->BeginPass(0);

	m_pRcTex->Render_Buffer();

	pEffect->EndPass();

	pEffect->End();

	Engine::Safe_Release(pEffect);

}

void CBackground::Set_Scale(const _vec3 * pScale)
{
	m_pTransform->Set_Scale(pScale);
}

CBackground * CBackground::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar * pKey)
{
	CBackground* pInstance = new CBackground(pGraphicDev);

	pInstance->set_Name(pKey);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (nullptr != pInstance)
	{
		pInstance->Late_Initialize();
	}

	return pInstance;
}

Engine::CGameObject * CBackground::Clone(void)
{
	CBackground* pInstance = new CBackground(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
