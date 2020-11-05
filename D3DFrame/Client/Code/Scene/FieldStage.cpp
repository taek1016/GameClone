#include "stdafx.h"
#include "FieldStage.h"

#include "LoadingThread.h"

#include "Objects/DynamicCamera.h"
#include "Objects/FirstPersonView.h"
#include "Objects/Terrain.h"

#include "UI/PlayerUI.h"
#include "UI/TargetUI.h"
#include "UI/UICollector.h"
#include "UI/SkillSlotUI.h"
#include "UI/InventoryUI.h"
#include "UI/SelectionCircle.h"
#include "UI/CoolTimeUI.h"
#include "UI/HPWarning.h"

USING(Engine)

CFieldStage::CFieldStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_fBGMVolume(0.2f)
{
	DLL::pSoundMgr->PlayBGM(L"OrgrimmarIntro.wav");
	DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fBGMVolume);
	m_eCurBGM = BGM_BOAR;
}

CFieldStage::~CFieldStage(void)
{
}

HRESULT CFieldStage::Initialize_Scene(void)
{
	setUp_Camera();
	initialize_UI();
	initialize_StageLight();


	DLL::pItemMgr->Initialize_Items(m_pGraphicDev);
	DLL::pSkillMgr->Initialize_Skills(m_pGraphicDev);

	DLL::pCameraMgr->Set_Object(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	DLL::pMouseMgr->Set_Activate();

	DLL::pDataMgr->Clone_Skybox(L"FieldStageSkybox");

	return S_OK;
}

Engine::_int CFieldStage::Update_Scene(const Engine::_float & fTimeDelta)
{
	play_BGM(fTimeDelta);

	_int iExit = DLL::pObjMgr->Update_Objects(fTimeDelta);


	return iExit;
}

void CFieldStage::Render_Scene(void)
{

}

void CFieldStage::play_BGM(const Engine::_float & fTimeDelta)
{
	if (DLL::pQuestMgr->Is_Cleared(L"KodoBeast"))
	{
		if (m_fBGMVolume > 0.f)
		{
			m_fBGMVolume -= 0.1f * fTimeDelta;
		}
		else if (m_eCurBGM != BGM_NEFARIAN)
		{
			m_eCurBGM = BGM_NEFARIAN;
			m_fBGMVolume = 0.05f;
			DLL::pSoundMgr->StopSound(CSoundMgr::BGM);
			DLL::pSoundMgr->PlayBGM(L"OrgrimmarNefarian.wav");
			DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fBGMVolume);
		}
	}
	else if (DLL::pQuestMgr->Is_Cleared(L"Boar"))
	{
		if (m_fBGMVolume > 0.f)
		{
			m_fBGMVolume -= 0.1f * fTimeDelta;
		}
		else if (m_eCurBGM != BGM_KODOBEAST)
		{
			m_eCurBGM = BGM_KODOBEAST;
			m_fBGMVolume = 0.1f;
			DLL::pSoundMgr->StopSound(CSoundMgr::BGM);
			DLL::pSoundMgr->PlayBGM(L"OrgrimmarKodoBeast.wav");
			DLL::pSoundMgr->SetVolume(CSoundMgr::BGM, m_fBGMVolume);
		}
	}
}

void CFieldStage::setUp_Camera(void)
{
	DLL::pCameraMgr->Add_Camera<CDynamicCamera>(CAMERA_ENUM::DYNAMIC_CAMERA, D3DXToRadian(90.f), 800.f / 600.f, 0.01f, 1000.f);

	Engine::_vec3	vEye(0.f, 3.f, -3.f);
	Engine::_vec3	vAt(0.f, 0.f, 0.f);
	Engine::_vec3	vUp(0.f, 1.f, 0.f);

	DLL::pCameraMgr->Add_Camera<CFirstPersonView>(CAMERA_ENUM::STATIC_CAMERA, D3DXToRadian(90.f), 800.f / 600.f, 0.01f, 1000.f);
	DLL::pCameraMgr->Set_CurCamera(CAMERA_ENUM::STATIC_CAMERA);

	DLL::pCameraMgr->Late_Initialize(&vEye, &vAt, &vUp);
}

void CFieldStage::initialize_UI(void)
{
	const _float fHalf = 0.5f;
	const _float fHalfWindowWidth = WINCX * fHalf;
	const _float fHalfWindowHeight = WINCY * fHalf;
	_vec3 vPos(-fHalfWindowWidth * 0.6f, fHalfWindowHeight * 0.8f, 0.f);
	_vec3 vScale(fHalfWindowWidth* 0.8f, fHalfWindowHeight * 0.4f, 1.f);

	DLL::pUIMgr->Add_UI(L"PlayerUI", CPlayerUI::Create(m_pGraphicDev, &vPos, &vScale));

	vPos = { fHalfWindowHeight * 0.6f, fHalfWindowHeight * 0.8f, 0.f };
	DLL::pUIMgr->Add_UI(L"TargetUI", CTargetUI::Create(m_pGraphicDev, &vPos, &vScale));

	vPos.x = fHalfWindowWidth * 0.8f;
	vPos.y = -fHalfWindowHeight * 0.95f;
	vScale.x = fHalfWindowWidth * 0.6f;
	vScale.y = fHalfWindowHeight * 0.1f;
	DLL::pUIMgr->Add_UI(L"UICollector", CUICollector::Create(m_pGraphicDev, &vPos, &vScale));

	vPos.y += 50.f;
	DLL::pUIMgr->Add_UI(L"InventoryUI", CInventoryUI::Create(m_pGraphicDev, &vPos, &vScale));

	vPos.x = 0;
	vPos.y = -fHalfWindowHeight * 0.85f;

	vScale.x = WINCX * 0.5f;
	vScale.y = fHalfWindowHeight * 0.3f;

	DLL::pUIMgr->Add_UI(L"SkillUI", CSkillSlotUI::Create(m_pGraphicDev, &vPos, &vScale));

	DLL::pUIMgr->Add_UI(L"SelectionCircle", CSelectionCircle::Create(m_pGraphicDev));

	vScale.x = 300.f;
	vScale.y = 100.f;

	vPos.x = 0.f;
	vPos.y = -WINCY * 0.5f * 0.5f;
	
	DLL::pUIMgr->Add_UI(L"CoolTimeUI", CCoolTimeUI::Create(m_pGraphicDev, &vPos, &vScale));

	DLL::pUIMgr->Add_UI(L"LowHealth", CHPWarning::Create(m_pGraphicDev));

	DLL::pUIMgr->Set_Act();
}

HRESULT CFieldStage::initialize_StageLight(void)
{
	D3DLIGHT9			tLightInfo;
	ZeroMemory(&tLightInfo, sizeof(D3DLIGHT9));

	tLightInfo.Type = D3DLIGHT_DIRECTIONAL;

	tLightInfo.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.f);
	tLightInfo.Direction = _vec3(1.f, -1.f, 1.f);

	FAILED_CHECK_RETURN(DLL::pLightMgr->Initialize_Light(m_pGraphicDev, &tLightInfo, 0), E_FAIL);


	tLightInfo.Type = D3DLIGHT_POINT;

	tLightInfo.Diffuse = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(0.f, 1.f, 0.f, 1.f);
	tLightInfo.Position = _vec3(10.f, 2.f, 10.f);
	tLightInfo.Range = 3.f;

	FAILED_CHECK_RETURN(DLL::pLightMgr->Initialize_Light(m_pGraphicDev, &tLightInfo, 1), E_FAIL);


	tLightInfo.Type = D3DLIGHT_POINT;

	tLightInfo.Diffuse = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Specular = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Ambient = D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	tLightInfo.Position = _vec3(30.f, 5.f, 10.f);
	tLightInfo.Range = 3.f;

	FAILED_CHECK_RETURN(DLL::pLightMgr->Initialize_Light(m_pGraphicDev, &tLightInfo, 2), E_FAIL);

	return S_OK;
}

CFieldStage * CFieldStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CFieldStage* pInstance = new CFieldStage(pGraphicDev);

	if (FAILED(pInstance->Initialize_Scene()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CFieldStage::Free(void)
{
	CScene::Free();
}