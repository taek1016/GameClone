#include "stdafx.h"
#include "Menu.h"

#include "UI/Background.h"
#include "UI/Button.h"

#include "Scene/SceneChanger.h"

USING(Engine)

CMenu::CMenu(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_pBackground(nullptr)
	, m_pMenuButton{ nullptr }
	, m_fVolume(0.1f)
	, m_bStartClicked(false)
	, m_bEndClicked(false)
{
	DLL::pSoundMgr->PlayBGM(L"WowMainTheme.wav");
	DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fVolume);
}

CMenu::~CMenu(void)
{
	DLL::pSoundMgr->StopAll();
}

HRESULT CMenu::Initialize_Scene(void)
{
	DLL::pFontMgr->Activate_Font(L"KOverwatch");

	DLL::Initialize_Mouse();

	m_pBackground = CBackground::Create(m_pGraphicDev, L"MenuBackground");

	_vec3 vPos(0.f, -WINCY * 0.25f, 0.f);
	_vec3 vScale(WINCX * 0.25f, WINCY * 0.1f, 1.f);

	const _tchar* pButtonNames[] = { L"시작하기", L"종료하기" };

	for (_int i = 0; i < BUTTON_END; ++i)
	{
		vPos.y -= i * WINCY * 0.1f;

		m_pMenuButton[i] = CButton::Create(m_pGraphicDev, L"MainMenuButton", &vPos, &vScale);
		m_pMenuButton[i]->Print_Content(pButtonNames[i]);
	}

	DLL::pMouseMgr->Set_Activate();
	DLL::pInventory->Initialize_Inventory(m_pGraphicDev);

	return S_OK;
}

Engine::_int CMenu::Update_Scene(const Engine::_float & fTimeDelta)
{
	m_pBackground->Update_GameObject(fTimeDelta);

	for (_int i = 0; i < BUTTON_END; ++i)
	{
		m_pMenuButton[i]->Update_GameObject(fTimeDelta);
	}

	if (m_bStartClicked || m_pMenuButton[BUTTON_START]->Get_Clicked())
	{
		m_bStartClicked = true;
		if (m_fVolume > 0.f)
		{
			m_fVolume -= 0.1f * fTimeDelta;
			DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fVolume);
		}
		else
		{
			DLL::pSoundMgr->StopAll();

			CSceneChanger* pSceneChanger = DLL::pManagement->SetUp_Scene<CSceneChanger>(m_pGraphicDev);
			pSceneChanger->SetUp_Scene(LOADING_FIELD, L"BlackWingRaid");
			DLL::pMouseMgr->Set_Activate();

			return -1;
		}
	}
	else if (m_bEndClicked || m_pMenuButton[BUTTON_EXIT]->Get_Clicked())
	{
		m_bEndClicked = true;
		if (m_fVolume > 0.f)
		{
			m_fVolume -= 0.1f * fTimeDelta;
			DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fVolume);
		}
		else
		{
			DestroyWindow(g_hWnd);
			return -1;
		}
	}

	return 0;
}

void CMenu::Render_Scene(void)
{
}

CMenu * CMenu::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMenu* pInstance = new CMenu(pGraphicDev);

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMenu::Free(void)
{
	CScene::Free();
	Safe_Release(m_pBackground);

	for (_int i = 0; i < BUTTON_EXIT; ++i)
	{
		Safe_Release(m_pMenuButton[i]);
	}
}
