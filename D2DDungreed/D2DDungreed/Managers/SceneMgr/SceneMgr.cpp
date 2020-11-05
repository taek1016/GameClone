#include "stdafx.h"
#include "SceneMgr.h"

#include "Logo.h"
#include "Menu.h"
#include "Stage.h"
#include "../../Stage/Stage0.h"
#include "../../Stage/Stage1.h"
#include "../../Stage/Stage2.h"
#include "../../Stage/Stage3.h"
#include "Village.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
	, m_iEvent(NO_EVENT)
{
	assert(nullptr == m_pScene);
}


CSceneMgr::~CSceneMgr()
{
	Release();
	assert(nullptr == m_pScene);
}

HRESULT CSceneMgr::SceneChange(SCENE_TYPE eCurType, SCENE_TYPE eNextType)
{
	if (eCurType != eNextType)
	{
		if (eCurType != SCENE_END)
		{
			SafeDelete(m_pScene);
		}

		switch (eNextType)
		{
		case SCENE_LOGO:
			m_pScene = CLogo::Create();
			break;

		case SCENE_MENU:
			m_pScene = CMenu::Create();
			break;

		case SCENE_VILLAGE:
			m_pScene = CVillage::Create();
			break;

		case SCENE_STAGE_0:
			m_pScene = CStage0::Create();
			break;

		case SCENE_STAGE_1:
			m_pScene = CStage1::Create();
			break;

		case SCENE_STAGE_2:
			m_pScene = CStage2::Create();
			break;

		case SCENE_STAGE_3:
			m_pScene = CStage3::Create();
			break;
		}
		assert(nullptr != m_pScene);
		NULL_CHECK_RETURN(m_pScene, E_FAIL);
	}
	return S_OK;
}

int CSceneMgr::Update()
{
	m_iEvent = m_pScene->Update();
	return m_iEvent;
}

void CSceneMgr::LateUpdate()
{
	if (SCENE_CHANGE == m_iEvent)
	{
		return;
	}
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	if (SCENE_CHANGE == m_iEvent)
	{
		return;
	}

	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
