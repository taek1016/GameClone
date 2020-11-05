#include "stdafx.h"
#include "Stage2.h"


CStage2::CStage2()
	: m_bSpawned(false)
	, m_bAfterSpawn(false)
{
	CTerrain* pTerrain = CTerrain::Create(L"../Data/Stage2.dat");

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_TERRAIN,
		pTerrain
	);
}

void CStage2::SpawnMonster()
{
	SetSpawnEffect(D3DXVECTOR3(600.f, 450.f, 0.f), MONSTER_TYPE::BIG_SKILL_SKEL);
	SetSpawnEffect(D3DXVECTOR3(900.f, 450.f, 0.f), MONSTER_TYPE::BIG_SKILL_SKEL);
}

void CStage2::SpawnResult()
{
	SpawnFairy(D3DXVECTOR3(600.f, 450.f, 0.f), FAIRY_SIZE::FAIRY_LARGE);
}


CStage2::~CStage2()
{
	Release();
}

CStage2 * CStage2::Create()
{
	CStage2*	pInstance = new CStage2;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}

int CStage2::Update()
{
	m_iEvent = CSINGLETON::pObjectMgr->Update();

	CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();
	if (!m_bSpawned && pPlayer->GetPos().x >= 160.f)
	{
		m_bSpawned = true;
		SpawnMonster();

		D3DXVECTOR3 vecSize(180.f / 66.f, 50.f / 20.f, 0.f);
		SpawnSealBlock(D3DXVECTOR3(100.f, 440.f, 0.f), vecSize, D3DXToRadian(90.f));
		SpawnSealBlock(D3DXVECTOR3(1050.f, 440.f, 0.f), vecSize, D3DXToRadian(270.f));

		CSINGLETON::pSoundMgr->PlaySound(L"SpawnMonster.wav", CSoundMgr::CHANNEL_ID::EFFECT);
	}
	if (pPlayer->GetPos().x >= 1160.f)
	{
		CSINGLETON::pObjectMgr->Release();
		CSINGLETON::pSceneMgr->SceneChange(SCENE_STAGE_2, SCENE_STAGE_3);
		m_iEvent = SCENE_CHANGE;
	}
	if (m_bSpawned && (!m_bAfterSpawn) && CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER)->size() == 0)
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

void CStage2::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CStage2::Render()
{
	CSINGLETON::pObjectMgr->Render();
}

HRESULT CStage2::Initialize()
{
	FAILED_CHECK_RETURN(SetSpawnPlayer
	(
		D3DXVECTOR3(80.f, 440.f, 0.f),
		D3DXVECTOR3 
		(
			static_cast<FLOAT>(30 * 40),
			static_cast<FLOAT>(22 * 40),
			0.f
		)
	), E_FAIL
	);

	SpawnLayer();

	for (int i = 0; i < 20; ++i)
	{
		SpawnSpikeObject(D3DXVECTOR3(220.f + i * 40.f, 760.f, 0.f));
	}
	return S_OK;
}

void CStage2::Release()
{
}
