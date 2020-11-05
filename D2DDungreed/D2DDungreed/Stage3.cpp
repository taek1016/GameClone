#include "stdafx.h"
#include "Stage\Stage3.h"


CStage3::CStage3()
	: m_bSpawn(false)
	, m_bAfterSpawn(false)
{	 
	CTerrain* pTerrain = CTerrain::Create(L"../Data/Stage3.dat");

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_TERRAIN,
		pTerrain
	);
}

void CStage3::SpawnMonster()
{
	SpawnBoss(D3DXVECTOR3(800.f, 400.f, 0.f));
}

void CStage3::SpawnResult()
{
}

CStage3::~CStage3()
{
}

CStage3* CStage3::Create()
{
	CStage3* pInstance = new CStage3;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}

int CStage3::Update()
{
	m_iEvent = CSINGLETON::pObjectMgr->Update();

	CGameObject* pPlayer = CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_PLAYER)->front();

	if (!m_bSpawn && pPlayer->GetPos().x >= 500)
	{
		D3DXVECTOR3 vecSize(180.f / 66.f, 50.f / 20.f, 0.f);
		SpawnSealBlock(D3DXVECTOR3(100.f, 520.f, 0.f), vecSize, D3DXToRadian(90.f));
		SpawnSealBlock(D3DXVECTOR3(1500.f, 160.f, 0.f), vecSize, D3DXToRadian(270.f));

		CSINGLETON::pSoundMgr->StopSound(CSoundMgr::CHANNEL_ID::BGM);
		CSINGLETON::pSoundMgr->PlayBGM(L"BGM_NifleHeim.wav");

		m_bSpawn = true;
		SpawnMonster();
	}

	if (CSINGLETON::pObjectMgr->GetObjList(OBJECT_TYPE::OBJECT_MONSTER)->size() == 0 && pPlayer->GetPos().x >= 1520)
	{
		CSINGLETON::pSoundMgr->StopAll();
		DestroyWindow(CSINGLETON::pWindow->GetHWND());
	}
	return m_iEvent;
}

void CStage3::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CStage3::Render()
{
	CSINGLETON::pObjectMgr->Render();
}

HRESULT CStage3::Initialize()
{
	FAILED_CHECK_RETURN(SetSpawnPlayer
	(
		D3DXVECTOR3(30.f, 580.f, 0.f),
		D3DXVECTOR3
		(
			static_cast<FLOAT>(1550),
			static_cast<FLOAT>(760),
			0.f
		)
	), E_FAIL
	);

	SpawnLayer();

	return S_OK;
}

void CStage3::Release()
{
}
