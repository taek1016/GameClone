#include "stdafx.h"
#include "Logo.h"

bool CLogo::m_bLogoLoading = false;

CLogo::CLogo()
	: CScene()
{
	SetSceneName(L"Logo");
	SetStatus(L"Logo");

	D3DXMatrixIdentity(&m_tWorld);

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_END);

	CTextureMgr::GetInstance()->LoadTexture
	(
		CSINGLETON::pDirectMgr->GetDevice(),
		TEXTURE_MULTI,
		L"../Texture/Logo/Logo/%d.png",
		L"Logo",
		L"Logo",
		1
	);

	CSINGLETON::pSoundMgr->PlayBGM(L"BGM_LOGO.wav");
}

CLogo::~CLogo()
{
	Release();
}

int CLogo::Update()
{
	if (CSINGLETON::pKeyMgr->KeyDown(KEY_RETURN))
	{
		WaitForSingleObject(m_hLoadingThread, INFINITE);

		m_iEvent = SCENE_CHANGE;
		CSINGLETON::pSoundMgr->StopAll();
		CSINGLETON::pSceneMgr->SceneChange(SCENE_LOGO, SCENE_MENU);
	}

	return m_iEvent;
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrName, m_wStrStatus);

	CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&m_tWorld);
	CSINGLETON::pDirectMgr->GetSprite()->Draw(
		pTexInfo->pTexture,
		nullptr,
		nullptr,
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

HRESULT CLogo::Initialize()
{
	m_hLoadingThread = (HANDLE)(_beginthreadex(nullptr, 0, LoadTextures, nullptr, 0, nullptr));
	NULL_CHECK_RETURN(m_hLoadingThread, E_FAIL);

	const TEX_INFO*	pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wstrName, m_wStrStatus);

	m_tWorld._11 = static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowWidth()) / pTexInfo->tImgInfo.Width;
	m_tWorld._22 = static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowHeight()) / pTexInfo->tImgInfo.Height;

	return S_OK;
}

void CLogo::Release()
{
	if (m_hLoadingThread)
	{
		CloseHandle(m_hLoadingThread);
	}
}

unsigned CLogo::LoadTextures(void * pParam)
{
	pParam;

	HRESULT hr = CSINGLETON::pTextureMgr->LoadTextrueFromPathInfo
	(
		CSINGLETON::pDirectMgr->GetDevice(),
		L"../Data/PathInfo.txt"
	);

	FAILED_CHECK_RETURN(hr, 1);

	return 0;
}

CLogo* CLogo::Create()
{
	CLogo*	pInstance = new CLogo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}