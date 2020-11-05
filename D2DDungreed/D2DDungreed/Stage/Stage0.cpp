#include "stdafx.h"
#include "Stage0.h"

#include "../Object/Player.h"
#include "../Object/Terrain/Terrain.h"

#include "../Object/Item/Hecate.h"

CStage0::CStage0()
{
	CTerrain* pTerrain = CTerrain::Create(L"../Data/Stage0.dat");

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_TERRAIN,
		pTerrain
	);
	CSINGLETON::pSoundMgr->PlayBGM(L"BGM_IceField.wav");
}


CStage0::~CStage0()
{
	Release();
}

CStage0 * CStage0::Create()
{
	CStage0*	pInstance = new CStage0;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}

int CStage0::Update()
{
	m_iEvent = CSINGLETON::pObjectMgr->Update();

	if (CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front()->GetPos().x >= 1300.f)
	{
		CSINGLETON::pObjectMgr->Release();
		CSINGLETON::pSceneMgr->SceneChange(SCENE_STAGE_0, SCENE_STAGE_1);
		m_iEvent = SCENE_CHANGE;
	}
	return m_iEvent;
}

void CStage0::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CStage0::Render()
{
	CSINGLETON::pObjectMgr->Render();
}

HRESULT CStage0::Initialize()
{
	FAILED_CHECK_RETURN
	(SetSpawnPlayer
		(
			D3DXVECTOR3(440.f, 740.f, 0.f), 
			D3DXVECTOR3(static_cast<FLOAT>(MAX_MAPSIZE_X - 2000), static_cast<FLOAT>(MAX_MAPSIZE_Y - 700), 0.f)
		), E_FAIL
	);

	SpawnLayer();

	SpawnBasicBox(D3DXVECTOR3(800.f, 745.f, 0.f), CHecate::Create());

	SpawnDoor(D3DXVECTOR3(440.f, 660.f, 0.f), true);
	
	return S_OK;
}

void CStage0::Release()
{
}
