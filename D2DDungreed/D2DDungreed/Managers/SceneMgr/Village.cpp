#include "stdafx.h"
#include "Village.h"

#include "../../Object/Layer/MyLayer.h"
#include "../../Object/Layer/LargeLayer.h"
#include "../../Object/Player.h"
#include "../../Object/Item/ItemInWorldMap.h"
#include "../../Object/Item/Hecate.h"
#include "../../Object/Monster/Skel.h"
#include "../../Object/Monster/BigWhiteSkel.h"
#include "../../Object/Monster/SkelIceMagician.h"

CVillage::CVillage()
{
	CTerrain* pTerrain = CTerrain::Create(L"../Data/Town/TownTile.dat");

	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_TERRAIN,
		pTerrain
	);
}


CVillage::~CVillage()
{
	Release();
}

int CVillage::Update()
{
	m_iEvent = NO_EVENT;
	m_iEvent = CSINGLETON::pObjectMgr->Update();

	return m_iEvent;
}

void CVillage::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CVillage::Render()
{
	CSINGLETON::pObjectMgr->Render();
}	

CVillage * CVillage::Create()
{
	CVillage*	pInstance = new CVillage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}

HRESULT CVillage::Initialize()
{
	CSINGLETON::pDirectMgr->SetBackColor(D3DCOLOR_ARGB(255, 0, 0, 0));

	D3DXVECTOR3 vecPos(0.f, 0.f, 0.f);
	D3DXVECTOR3 vecSize(800.f / 320.f, 500.f / 180.f, 0.f);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_LAYER,
		CMyLayer::Create
		(
			L"Town",
			L"BackCloud",
			vecPos,
			vecSize
		)
	);
	
	vecPos = D3DXVECTOR3(0.f, 100.f, 0.f);
	vecSize = D3DXVECTOR3(800.f / 320.f, 400.f / 142.f, 0.f);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_LAYER,
		CLargeLayer::Create
		(
			L"Town",
			L"Mountain",
			vecPos,
			vecSize
		)
	);

	vecPos = D3DXVECTOR3(0.f, 200.f, 0.f);
	vecSize = D3DXVECTOR3(800.f / 320.f, 300.f / 95.f, 0.f);
	CSINGLETON::pObjectMgr->AddObject
	(
		OBJECT_TYPE::OBJECT_LAYER,
		CLargeLayer::Create
		(
			L"Town",
			L"Grass",
			vecPos,
			vecSize
		)
	);

	CSINGLETON::pCameraMgr->SetPivot(D3DXVECTOR3(0.5f, 0.5f, 0.f));

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(400.f, 1200.f, 0.f));
	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_PLAYER, pPlayer);

	D3DXVECTOR3 vecClientRs(
		static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowWidth()),
		static_cast<FLOAT>(CSINGLETON::pWindow->GetWindowHeight()),
		0.f);

	D3DXVECTOR3 vecWorldRs(
		static_cast<FLOAT>(MAX_MAPSIZE_X),
		static_cast<FLOAT>(MAX_MAPSIZE_Y),
		0.f
	);

	CSINGLETON::pCameraMgr->SetTarget(pPlayer);
	CSINGLETON::pCameraMgr->SetPos(pPlayer->GetPos());
	CSINGLETON::pCameraMgr->SetClientRS(vecClientRs);
	CSINGLETON::pCameraMgr->SetWorldRS(vecWorldRs);

	pPlayer = nullptr;

	return S_OK;
}

void CVillage::Release()
{
}
