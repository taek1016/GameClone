#include "stdafx.h"
#include "LoadingBar.h"

#include "LoadingThread.h"

USING(Engine)

CLoadingBar::CLoadingBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTransformCom{ nullptr }
	, m_pBuffer{ nullptr }
	, m_pLoadingThread(nullptr)
	, m_pTexture{ nullptr }
{
}

CLoadingBar::~CLoadingBar(void)
{
}

HRESULT CLoadingBar::Initialize_GameObject(void)
{
	CTransform::Create()->Attach(L"FrameTransform", this, ID_DYNAMIC);
	CTransform::Create()->Attach(L"BarTransform", this, ID_DYNAMIC);

	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, L"LoadingBarFill")->Attach(L"BarTexture", this, ID_STATIC);
	DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, L"LoadingBarFrame")->Attach(L"FrameTexture", this, ID_STATIC);

	CRcTex::Create(m_pGraphicDev)->Attach(L"FrameBuffer", this, ID_STATIC);
	CRcTex::Create(m_pGraphicDev)->Attach(L"BarBuffer", this, ID_STATIC);

	return S_OK;
}

HRESULT CLoadingBar::Late_Initialize(void)
{
	m_pTransformCom[LOADBAR_BACKGROUND] = Get_Component<CTransform>(L"FrameTransform", ID_DYNAMIC);
	m_pTransformCom[LOADBAR_SPARK] = Get_Component<CTransform>(L"BarTransform", ID_DYNAMIC);

	m_pTexture[LOADBAR_BACKGROUND] = Get_Component<CTexture>(L"FrameTexture", ID_STATIC);
	m_pTexture[LOADBAR_SPARK] = Get_Component<CTexture>(L"BarTexture", ID_STATIC);

	m_pBuffer[LOADBAR_BACKGROUND] = Get_Component<CRcTex>(L"FrameBuffer", ID_STATIC);
	m_pBuffer[LOADBAR_SPARK] = Get_Component<CRcTex>(L"BarBuffer", ID_STATIC);

	_vec3 vScale(WINCX * 0.75f, WINCY * 0.1f, 1.f);
	_vec3 vPos(0.f, -WINCY * 0.425f, 0.f);

	m_pTransformCom[LOADBAR_BACKGROUND]->Set_Info(INFO_POS, &vPos);
	m_pTransformCom[LOADBAR_BACKGROUND]->Set_Scale(&vScale);

	vScale = { 0.f, 30.f, 1.f };
	vPos = { 0.f, -WINCY * 0.425f, 0.f };
	m_pTransformCom[LOADBAR_SPARK]->Set_Info(INFO_POS, &vPos);
	m_pTransformCom[LOADBAR_SPARK]->Set_Scale(&vScale);


	return S_OK;
}

Engine::_int CLoadingBar::Update_GameObject(const _float & fTimeDelta)
{
	const _float fPercent = m_pLoadingThread->Get_Percent();
	const _float fMaxScaleX = WINCX * 0.65f;

	_vec3 vScale = *m_pTransformCom[LOADBAR_SPARK]->Get_Scale();

	if (fPercent > 0.f)
	{
		vScale.x = fMaxScaleX * fPercent;
	}
	else if (fPercent >= 1.f)
	{
		vScale.x = fMaxScaleX;
	}
	else
	{
		vScale.x = 0.f;
	}

	m_pTransformCom[LOADBAR_SPARK]->Set_Scale(&vScale);

	_vec3 vPos = *m_pTransformCom[LOADBAR_SPARK]->Get_Info(INFO_POS);
	const _float fHalf = 0.5f;
	vPos.x = -fMaxScaleX * fHalf + fPercent * fMaxScaleX * fHalf;

	m_pTransformCom[LOADBAR_SPARK]->Set_Info(INFO_POS, &vPos);

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CLoadingBar::Render_GameObject(void)
{
	for (_int i = 0; i < LOADBAR_END; ++i)
	{
		m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom[i]->Get_World());

		m_pTexture[i]->Render_Texture();
		m_pBuffer[i]->Render_Buffer();
	}
}

void CLoadingBar::set_LoadingThread(CLoading * pLoadingThread)
{
	m_pLoadingThread = pLoadingThread;
	m_pLoadingThread->AddRef();
}

CLoadingBar * CLoadingBar::Create(LPDIRECT3DDEVICE9 pGraphicDev, CLoading* pLoadingThread)
{
	CLoadingBar* pInstance = new CLoadingBar(pGraphicDev);

	pInstance->set_LoadingThread(pLoadingThread);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

Engine::CGameObject * CLoadingBar::Clone(void)
{
	CLoadingBar* pInstance = new CLoadingBar(*this);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	return pInstance;
}

inline void CLoadingBar::Free(void)
{
	CGameObject::Free();
	Safe_Release(m_pLoadingThread);
}
