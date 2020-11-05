#include "stdafx.h"
#include "PlayerController.h"

#include "Item/Rifle.h"
#include "SceneObject/Bullet.h"
#include "SceneObject/Turret.h"
#include "SceneObject/Barricade.h"
#include "SceneObject/Player.h"

USING(Engine)

CPlayerController::CPlayerController(void)
	: CController()
	, m_fSpeed(5.f)
{
}

CPlayerController::~CPlayerController(void)
{
}

HRESULT CPlayerController::Late_Initialize()
{
	m_pTransform = m_pGameObject->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC);
	m_pRigidBody = m_pGameObject->Get_Component<CRigidBody>(RIGIDBODY, ID_DYNAMIC);
	m_pBody = m_pGameObject->Get_Component<CBody>(BODY, ID_DYNAMIC);
	//m_pAnimation = m_pGameObject->Get_Component<CAnimation>(Animation, ID_DYNAMIC);
	return S_OK;
}

HRESULT CPlayerController::Initialize_Component()
{
	m_pBody = m_pGameObject->Get_Component<CBody>(BODY, ID_DYNAMIC);

	return S_OK;
}

_float airOffset = 0;

_int CPlayerController::Update_Component(const _float & fTimeDelta)
{
	Set_OnTerrain();
	Key_Input(fTimeDelta);

	if (m_bAirborne)
	{
		m_pTransform->Move_Pos(&(_vec3(0, m_fJumpPower - m_fAirbornePower, 0) * fTimeDelta));
		m_fAirbornePower += (5 + (airOffset += 0.3)) * fTimeDelta;
	}

	return 0;
}

void CPlayerController::AirBorne()
{
	m_bAirborne = true;
	m_fAirbornePower = 0;
	m_fJumpPower = 7.f;
	m_fAirTime = 0;
	airOffset = 0;
}

void CPlayerController::Jump()
{
	m_bAirborne = true;
	m_fAirbornePower = 0;
	m_fJumpPower = 4.f;
	m_fAirTime = 0;
	airOffset = 0;
}

void CPlayerController::Key_Input(const _float& fTimeDelta)
{
	_float	fMovePerFrame = m_fSpeed * fTimeDelta;
	_vec3	vDir;
	
	if (DLL::pCraftingMgr->Get_Activate())
	{
		return;
	}

	if (DLL::pDirectInput->KeyPressing(DIK_TAB))
	{
		// 라이플
		if (DLL::pDirectInput->KeyDown(DIK_1))
		{
			DLL::pInventory->Activate_Item(WEAPON::RIFLE);
		}
		// 샷건
		else if (DLL::pDirectInput->KeyDown(DIK_2))
		{
			DLL::pInventory->Activate_Item(WEAPON::SHOT_GUN);
		}
		// 전기톱
		else if (DLL::pDirectInput->KeyDown(DIK_3))
		{
			m_bSingleShot = false;
			DLL::pInventory->Activate_Item(WEAPON::CHAIN_SAW);
		}
		// 바리케이드 제작
		else if (DLL::pDirectInput->KeyDown(DIK_4))
		{
			DLL::pCraftingMgr->Set_Activate();
			DLL::pCraftingMgr->Make_Item(L"Barricade", INSTALL_TYPE::INSTALL_WALL);
		}
		// 터렛 제작
		else if (DLL::pDirectInput->KeyDown(DIK_5))
		{
			DLL::pCraftingMgr->Set_Activate();
			DLL::pCraftingMgr->Make_Item(L"Turret", INSTALL_TYPE::INSTALL_MACHINE_GUN);
		}
		// 바리케이드 설치
		else if (DLL::pDirectInput->KeyDown(DIK_6))
		{
			DLL::pSoundMgr->PlaySound(L"Install.mp3", CSoundMgr::CHANNEL_ID::EFFECT);
			dynamic_cast<CPlayer*>(m_pGameObject)->Set_PickableObj(DLL::pInventory->Get_InstallItem(INSTALL_TYPE::INSTALL_WALL));
		}
		// 터렛 설치
		else if (DLL::pDirectInput->KeyDown(DIK_7))
		{
			DLL::pSoundMgr->PlaySound(L"Install.mp3", CSoundMgr::CHANNEL_ID::EFFECT);
			dynamic_cast<CPlayer*>(m_pGameObject)->Set_PickableObj(DLL::pInventory->Get_InstallItem(INSTALL_TYPE::INSTALL_MACHINE_GUN));
		}
		else if (DLL::pDirectInput->KeyDown(DIK_Q))
		{
			DLL::pInventory->Add_InstallItem(INSTALL_MACHINE_GUN, DLL::pCraftingMgr->Clone(INSTALL_MACHINE_GUN));
		}
		else if (DLL::pDirectInput->KeyDown(DIK_W))
		{
			DLL::pInventory->Add_InstallItem(INSTALL_WALL, DLL::pCraftingMgr->Clone(INSTALL_WALL));
		}
	}
	else
	{
		// 이동
		if (DLL::pDirectInput->KeyDown(DIK_R))
		{
			m_bSingleShot = !m_bSingleShot;
		}

		if (DLL::pDirectInput->KeyPressing(DIK_W))
		{
			m_pBody->PlayArmAnimation(L"Move");
			m_pBody->PlayLegAnimation(L"Move");

			m_pTransform->Get_Info(Engine::INFO_LOOK, &vDir);
			D3DXVec3Normalize(&vDir, &vDir);
			m_pTransform->Move_Pos(&(vDir * fMovePerFrame));
		}
		if (DLL::pDirectInput->KeyPressing(DIK_S))
		{
			m_pBody->PlayArmAnimation(L"AttackGun");
			m_pBody->PlayLegAnimation(L"Move");

			m_pTransform->Get_Info(Engine::INFO_LOOK, &vDir);
			D3DXVec3Normalize(&vDir, &vDir);
			m_pTransform->Move_Pos(&(vDir * -fMovePerFrame));
		}
		if (DLL::pDirectInput->KeyPressing(DIK_A))
		{
			m_pTransform->Get_Info(Engine::INFO_RIGHT, &vDir);
			D3DXVec3Normalize(&vDir, &vDir);
			m_pTransform->Move_Pos(&(vDir * -fMovePerFrame));

		}
		if (DLL::pDirectInput->KeyPressing(DIK_D))
		{
			m_pTransform->Get_Info(Engine::INFO_RIGHT, &vDir);
			D3DXVec3Normalize(&vDir, &vDir);
			m_pTransform->Move_Pos(&(vDir * fMovePerFrame));
		}

		// 공격
		if (m_bSingleShot)
		{
			if (DLL::pDirectInput->MouseDown(DIM_LB))
			{
				m_pGameObject->Attack(fTimeDelta);
			}
		}
		else
		{
			if (DLL::pDirectInput->MousePress(DIM_LB))
			{
				m_pGameObject->Attack(fTimeDelta);
			}
		}

		// 점프
		if (DLL::pDirectInput->KeyDown(DIK_SPACE) && !m_bNowJumping)
		{
			Jump();
			m_bNowJumping = true;
		}
		else if (m_pRigidBody->Get_Jump())
		{
			m_pTransform->Move_Pos(&_vec3(0.f, -m_pRigidBody->Get_Height(fTimeDelta), 0.f));
		}

		if (DLL::pDirectInput->KeyDown(DIK_1))
		{
			_int iSetCamera = CAMERA_END;
			switch (DLL::pCameraMgr->Get_CurCamera())
			{
			case STATIC_CAMERA:
				iSetCamera = FIRST_PERSON_VIEW;
				break;

			case FIRST_PERSON_VIEW:
				iSetCamera = STATIC_CAMERA;
				break;
			}
			DLL::pCameraMgr->Set_CurCamera(iSetCamera);
		}
	}

	_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
	if (vPos.x >= 105.f && vPos.y >= 4.f && vPos.z >= 130.f)
	{
		DLL::pEventMgr->Activate_Mgr(L"ZombieRun");
	}
}

void CPlayerController::Set_OnTerrain(void)
{
	_vec3		vPos;
	m_pTransform->Get_Info(Engine::INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTex = DLL::pSearchMgr->Get_Object(L"Terrain")
		->Get_Component<CTerrainTex>(BODY, ID_STATIC);

	_float	fHeight = Compute_HeightOnTerrain(&vPos, pTerrainTex->Get_Vtx(), pTerrainTex->Get_TotalVtxCnt());
	
	

	if (m_bAirborne || m_bNowJumping)
	{
		if (vPos.y <= fHeight)
		{
			m_bAirborne = false;
			m_bNowJumping = false;
			m_pTransform->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
		}
	}
	else
	{
		if (fHeight + 0.5f >= vPos.y)
		{
			m_pRigidBody->CancleJump();
		}
		m_pTransform->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
	}
}

Engine::_float CPlayerController::Compute_HeightOnTerrain(const Engine::_vec3* pPos, const Engine::BasicVertex* pVtx, const _ulong& dwTotalCnt)
{
	_ulong	dwCntX = static_cast<_ulong>(sqrt(dwTotalCnt));
	// 타일 ITV = 1.f
	_ulong	dwIndex = _ulong(pPos->z / 1.f) * dwCntX + _ulong(pPos->x / 1.f);

	_float	fRatioX = (pPos->x - pVtx[dwIndex + dwCntX].vPos.x) / 1.f;
	_float	fRatioZ = (pVtx[dwIndex + dwCntX].vPos.z - pPos->z) / 1.f;

	_float	fHeight[4] = {
		pVtx[dwIndex + dwCntX].vPos.y,
		pVtx[dwIndex + dwCntX + 1].vPos.y,
		pVtx[dwIndex + 1].vPos.y,
		pVtx[dwIndex].vPos.y
	};

	// 오른쪽 위 평면
	if (fRatioX > fRatioZ)
	{
		return fHeight[0] + (fHeight[1] - fHeight[0]) * fRatioX + (fHeight[2] - fHeight[1]) * fRatioZ;
	}
	// 왼쪽 아래 평면
	else
	{
		return fHeight[0] + (fHeight[2] - fHeight[3]) * fRatioX + (fHeight[3] - fHeight[0]) * fRatioZ;
	}
}

CPlayerController * CPlayerController::Create(void)
{
	CPlayerController* pInstance = new CPlayerController();

	return pInstance;
}

inline void CPlayerController::freeMem()
{
	CController::freeMem();
	m_pTransform = nullptr;
}