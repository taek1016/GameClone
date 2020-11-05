#include "stdafx.h"
#include "Scene.h"

#include "../../Object/Effect/SummonEffect.h"
#include "../../Object/Player.h"
#include "../../Object/Layer/LargeLayer.h"
#include "../../Object/Layer/MyLayer.h"

#include "../../Object/Item/BasicBox.h"
#include "../../Object/Block/SealEffect.h"

#include "../../Object/Door/Door.h"
#include "../../Object/Fairy/Fairy.h"
#include "../../Object/Fairy/SmallFairy.h"
#include "../../Object/Fairy/MiddleFairy.h"
#include "../../Object/Fairy/LargeFairy.h"
#include "../../Object/Fairy/XLargeFairy.h"

#include "../../Object/Spike/SpikeObject.h"

#include "../../Object/Effect/NiffleHeimSummon.h"

CScene::CScene()
	: m_wstrName()
	, m_tWorld()
	, m_iEvent(NO_EVENT)
{
	D3DXMatrixIdentity(&m_tWorld);
}

CScene::~CScene()
{
	m_wstrName.clear();

	assert(0 == m_wstrName.length());
}

void CScene::SetSpawnEffect(const D3DXVECTOR3& vecPos, MONSTER_TYPE eType)
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_EFFECT,
		CSummonEffect::Create(vecPos, eType)
	);
}

HRESULT CScene::SetSpawnPlayer(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecWorldRS)
{
	CGameObject* pPlayer = CPlayer::Create(vecPos);

	FAILED_CHECK_RETURN(CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_PLAYER, pPlayer), E_FAIL);

	D3DXVECTOR3 vecClientRs(
		static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowWidth()),
		static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowHeight()),
		0.f);

	CSINGLETON::pCameraMgr->SetTarget(pPlayer);
	CSINGLETON::pCameraMgr->SetPos(pPlayer->GetPos());
	CSINGLETON::pCameraMgr->SetClientRS(vecClientRs);
	CSINGLETON::pCameraMgr->SetWorldRS(vecWorldRS);
	CSINGLETON::pCameraMgr->SetPivot(D3DXVECTOR3(0.5f, 0.5f, 0.f));

	pPlayer = nullptr;

	return S_OK;
}

void CScene::SpawnLayer()
{
	D3DXVECTOR3 vecPos(0.f, 0.f, 0.f);
	D3DXVECTOR3 vecSize(800.f / 320.f, 600.f / 260.f, 0.f);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_LAYER,
		CMyLayer::Create
		(
			L"Stage",
			L"BackStage",
			vecPos,
			vecSize
		)
	);

	vecSize = D3DXVECTOR3(800.f / 320.f, 600.f / 350.f, 0.f);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_LAYER,
		CLargeLayer::Create
		(
			L"Stage",
			L"FrontStage",
			vecPos,
			vecSize
		)
	);
}

void CScene::SpawnBasicBox(const D3DXVECTOR3 & vecPos, CBaseItem * pItem)
{
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_OBJECT,
		CBasicBox::Create(vecPos, pItem)
	);
}

void CScene::SpawnSealBlock(const D3DXVECTOR3 & vecPos, const D3DXVECTOR3 vecSize, float fRadian)
{
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_OBJECT, CSealEffect::Create(vecPos, vecSize, fRadian));
}

void CScene::SpawnDoor(const D3DXVECTOR3 & vecPos, const bool bAlreadyIn)
{
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_OBJECT, CDoor::Create(vecPos, bAlreadyIn));
}

void CScene::SpawnFairy(const D3DXVECTOR3 & vecPos, const FAIRY_SIZE eSize)
{
	CFairy* pFairy = nullptr;

	switch (eSize)
	{
	case FAIRY_SMALL:
		pFairy = CSmallFairy::Create(vecPos);
		break;

	case FAIRY_MIDDLE:
		pFairy = CMiddleFairy::Create(vecPos);
		break;

	case FAIRY_LARGE:
		pFairy = CLargeFairy::Create(vecPos);
		break;

	case FAIRY_XLARGE:
		pFairy = CXLargeFairy::Create(vecPos);
		break;
	}

	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_OBJECT, pFairy);
}

void CScene::SpawnSpikeObject(const D3DXVECTOR3 & vecPos)
{
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_OBJECT, CSpikeObject::Create(vecPos));
}

void CScene::SpawnBoss(const D3DXVECTOR3 & vecPos)
{
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_MONSTER, CNiffleHeimSummon::Create(vecPos));
}