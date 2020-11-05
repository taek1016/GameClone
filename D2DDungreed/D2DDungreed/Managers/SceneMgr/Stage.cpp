#include "stdafx.h"
#include "Stage.h"

#include "..\..\Object\Player.h"
#include "..\..\Object\Terrain\Terrain.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	CSINGLETON::pObjectMgr->Update();

	return NO_EVENT;
}

void CStage::LateUpdate()
{
	CSINGLETON::pObjectMgr->LateUpdate();
}

void CStage::Render()
{
	CSINGLETON::pObjectMgr->Render();
}

HRESULT CStage::Initialize()
{
	CGameObject* pPlayer = CPlayer::Create(D3DXVECTOR3(400.f, 300.f, 0.f));

	HRESULT hr = CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_PLAYER, pPlayer);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	hr = CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_TERRAIN, CTerrain::Create());
	FAILED_CHECK_RETURN(hr, E_FAIL);

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
	CSINGLETON::pCameraMgr->SetPivot(D3DXVECTOR3(0.5f, 0.5f, 0.f));

	pPlayer = nullptr;

	return S_OK;
}

void CStage::Release()
{
}

CStage* CStage::Create()
{
	CStage*	pInstance = new CStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	CSINGLETON::pMouseMgr->SetMouseType(MOUSE_TYPE::MOUSE_ATTACK);

	return pInstance;
}