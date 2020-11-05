#include "stdafx.h"
#include "Title.h"

#include "MyButton.h"
#include "Scene/Stage.h"
#include "LogoObject/BackGround.h"
#include "LogoObject/TitleTexture.h"

USING(Engine)

CTitle::CTitle(void)
	: CScene()
{
	DLL::pSoundMgr->PlayBGM(L"Unturned_TitleBGM.mp3");
}

CTitle::CTitle(const CTitle & rhs)
	: CScene(rhs)
{
}

CTitle::~CTitle(void)
{
}

HRESULT CTitle::Initialize_Scene(void)
{
	_vec3 vStartPos(0.f, 0.f, 0.f);
	_vec3 vBtnSize(100.f, 100.f, 1.f);
	_vec3 vExitPos(0.f, 1.f, 0.f);

	_float fWidth = 20.f;
	_float fHeight = 20.f;

	m_pBackGround = CBackGround::Create(L"TitleBack");
	m_pText = CTitleText::Create();

	return S_OK;
}

Engine::_int CTitle::Update_Scene(const Engine::_float & fTimeDelta)
{
	m_pBackGround->Update_GameObject(fTimeDelta);

	m_pText->Update_GameObject(fTimeDelta);
	if (DLL::pDirectInput->KeyDown(DIK_RETURN))
	{
		DLL::pManagement->SetUp_Scene<CStage>();
		return -1;
	}

	return 0;
}

void CTitle::Render_Scene(void)
{
}

CTitle* CTitle::Create(void)
{
	CTitle*	pInstance = new CTitle;

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTitle::freeMem(void)
{
	Safe_Release(m_pBackGround);
	Safe_Release(m_pText);
}
