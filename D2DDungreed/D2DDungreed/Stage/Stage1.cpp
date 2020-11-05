#include "stdafx.h"
#include "Stage1.h"

#include "../Object/Player.h"
#include "../Object/Layer/LargeLayer.h"
#include "../Object/Layer/MyLayer.h"

CStage1::CStage1()
	: m_bSpawned(false)
	, m_bAfterSpawn(false)
	, m_bAllKilled(false)
{
	CTerrain* pTerrain = CTerrain::Create(L"../Data/Stage1.dat");

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_TERRAIN,
		pTerrain
	);
}


CStage1::~CStage1()
{
	Release();
}

CStage1 * CStage1::Create()
{
	CStage1*	pInstance = new CStage1;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}

int CStage1::Update()
{
	CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();
	
	int iCurMonster = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER)->size();
	if(!m_bSpawned && pPlayer->GetPos().x >= 100)
	{
		m_bSpawned = true;
		SpawnMonster();

		D3DXVECTOR3 vecSize(180.f / 66.f, 50.f / 20.f, 0.f);
		SpawnSealBlock(D3DXVECTOR3(100.f, 400.f, 0.f), vecSize, D3DXToRadian(90.f));
		SpawnSealBlock(D3DXVECTOR3(940.f, 400.f, 0.f), vecSize, D3DXToRadian(270.f));

		CSINGLETON::pSoundMgr->PlaySound(L"SpawnMonster.wav", CSoundMgr::CHANNEL_ID::EFFECT);
	}

	if (iCurMonster == 0)
	{
		m_bAllKilled = true;
	}

	m_iEvent = CSINGLETON::pObjectMgr->Update();

	if (pPlayer->GetPos().x >= 1000.f)
	{
		CSINGLETON::pObjectMgr->Release();
		CSINGLETON::pSceneMgr->SceneChange(SCENE_STAGE_1, SCENE_STAGE_2);
		m_iEvent = SCENE_CHANGE;
	}
	if (m_bSpawned && (!m_bAfterSpawn) && iCurMonster == 0 && m_bAllKilled)
	{
		static float fDelta = 0.f;
		fDelta += CSINGLETON::pTimeMgr->GetDelta();

		if (fDelta < 2.f)
		{
			return m_iEvent;
		}
		m_bAfterSpawn = true;
		SpawnResult();
	}
	return m_iEvent;
}

void CStage1::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CStage1::Render()
{
	CSINGLETON::pObjectMgr->Render();
}

HRESULT CStage1::Initialize()
{
	FAILED_CHECK_RETURN(SetSpawnPlayer
	(
		D3DXVECTOR3(80.f, 440.f, 0.f),
		D3DXVECTOR3
		(
			static_cast<FLOAT>(1000),
			static_cast<FLOAT>(600),
			0.f
		)
	), E_FAIL
	);

	SpawnLayer();

	return S_OK;
}

void CStage1::Release()
{
}

void CStage1::SpawnMonster()
{
	SetSpawnEffect(D3DXVECTOR3(280.f, 460.f, 0.f), MONSTER_TYPE::BIG_SKEL);
	SetSpawnEffect(D3DXVECTOR3(400.f, 300.f, 0.f), MONSTER_TYPE::ICE_MAGICIAN);
	SetSpawnEffect(D3DXVECTOR3(700.f, 460.f, 0.f), MONSTER_TYPE::BIG_SKEL);
	SetSpawnEffect(D3DXVECTOR3(400.f, 460.f, 0.f), MONSTER_TYPE::BIG_SKEL);
	SetSpawnEffect(D3DXVECTOR3(500.f, 300.f, 0.f), MONSTER_TYPE::BANSHEE);
}

void CStage1::SpawnResult()
{
	SpawnFairy(D3DXVECTOR3(500.f, 300.f, 0.f), FAIRY_SIZE::FAIRY_SMALL);
}