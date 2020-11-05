#include "stdafx.h"
#include "FlyVehicle.h"

USING(Engine)

CFlyVehicle::CFlyVehicle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVehicleBase(pGraphicDev)
	, m_bFly(false)
	, m_bFlyFast(true)
	, m_bFlyDown(false)
	, m_bFlyStart(false)
	, m_fFlyFastSpeed(0.f)
	, m_fFlyNormalSpeed(0.f)
{
}

CFlyVehicle::CFlyVehicle(const CFlyVehicle & rhs)
	: CVehicleBase(rhs)
	, m_bFlyFast(true)
	, m_bFlyDown(false)
	, m_bFly(false)
	, m_bFlyStart(false)
	, m_fFlyFastSpeed(rhs.m_fFlyFastSpeed)
	, m_fFlyNormalSpeed(rhs.m_fFlyNormalSpeed)
{
}

Engine::_bool CFlyVehicle::check_GroundUpperPos(Engine::_float& fYPos)
{
	_vec3 vPos, vGroundPos;
	vPos = vGroundPos = *m_pTransform->Get_Info(INFO_POS);
	vGroundPos.y = DLL::pPickMgr->Get_TerrainHeight(&vPos);

	if (vPos.y > vGroundPos.y)
	{
		return true;
	}
	fYPos = vGroundPos.y;
	return false;
}

void CFlyVehicle::read_Data(void)
{
	CVehicleBase::read_Data();

	m_fFlyFastSpeed = get_ReadData(L"FlyFastSpeed");
	m_fFlyNormalSpeed = get_ReadData(L"FlyNormalSpeed");
}

void CFlyVehicle::key_Input(const Engine::_float & fTimeDelta)
{
	if (m_bFlyDown)
	{
		_vec3 vPos, vDownPos;
		vPos = vDownPos = *m_pTransform->Get_Info(INFO_POS);
		vDownPos.y = DLL::pPickMgr->Get_TerrainHeight(&vPos);

		_float fDistance = fabsf(D3DXVec3Length(&(vDownPos - vPos)));
		if (0.5f > fDistance)
		{
			m_dwNaviIdx = DLL::pPickMgr->Get_Index(m_pTransform->Get_Info(INFO_POS));
			m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &_vec3(0.f, 0.f, 0.f)));
			m_bFlyDown = false;
		}
		else
		{
			_vec3 vDir(0.f, -1.f, 0.f);
			vDir *= m_fFlyNormalSpeed * fTimeDelta;
			m_pTransform->Move_Pos(&vDir);
			return;
		}
	}

	if (m_bFlyStart)
	{
		if (m_pMesh->Is_AnimationSetEnd())
		{
			m_bFlyStart = false;
		}
		else
		{
			return;
		}
	}

	if (false == m_bFly)
	{
		Set_AnimationSet(L"Stand");
	}
	else
	{
		Set_AnimationSet(L"FlightIdle");
	}

	if (false == m_bRiding)
	{
		return;
	}

	if (DLL::pInputMgr->KeyDown(DIK_F))
	{
		if (false == m_bFly)
		{
			Set_AnimationSet(L"FlightStart");
		}

		m_bFlyStart = !m_bFlyStart;
		m_bFly = !m_bFly;

		if (false == m_bFly)
		{
			m_bFlyDown = true;
		}
	}

	if (m_bFly)
	{
		sky_KeyInput(fTimeDelta);
	}
	else
	{
		ground_KeyInput(fTimeDelta);
	}
}

void CFlyVehicle::sky_KeyInput(const Engine::_float & fTimeDelta)
{
	if (DLL::pInputMgr->KeyPressing(DIK_T))
	{
		_vec3 vDir(0.f, 1.f, 0.f);
		vDir *= fTimeDelta * 5.f;

		m_pTransform->Move_Pos(&vDir);
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_G))
	{
		_vec3 vDir(0.f, -1.f, 0.f);
		vDir *= fTimeDelta * 5.f;

		m_pTransform->Move_Pos(&vDir);
	}

	if (DLL::pInputMgr->KeyPressing(DIK_A))
	{
		const _float fDeltaRot = -D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		m_pRidingTargetTransform->Rotation(ROT_Y, fDeltaRot);

		Set_AnimationSet(L"FlightShuffleLeft");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_D))
	{
		const _float fDeltaRot = D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		m_pRidingTargetTransform->Rotation(ROT_Y, fDeltaRot);

		Set_AnimationSet(L"FlightShuffleRight");
	}

	if (DLL::pInputMgr->KeyPressing(DIK_W))
	{
		_vec3 vDir = *m_pTransform->Get_Info(INFO_LOOK);
		D3DXVec3Normalize(&vDir, &vDir);

		m_bFlyFast == true ? (vDir *= m_fFlyFastSpeed * fTimeDelta) : (vDir *= m_fFlyNormalSpeed * fTimeDelta);

		m_pTransform->Move_Pos(&vDir);

		_float fGroundYPos;
		if (false == check_GroundUpperPos(fGroundYPos))
		{
			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y = fGroundYPos;

			m_pTransform->Set_Info(INFO_POS, &vPos);
		}

		Set_AnimationSet(L"FlightRun");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_S))
	{
		_vec3 vDir = *m_pTransform->Get_Info(INFO_LOOK) * -1.f;
		D3DXVec3Normalize(&vDir, &vDir);

		vDir = vDir * m_fWalkSpeed * fTimeDelta;

		m_pTransform->Move_Pos(&vDir);
		_float fGroundYPos;
		if (false == check_GroundUpperPos(fGroundYPos))
		{
			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y = fGroundYPos;

			m_pTransform->Set_Info(INFO_POS, &vPos);
		}

		Set_AnimationSet(L"FlightBack");
	}

	if (DLL::pInputMgr->KeyPressing(DIK_Q))
	{
		const _float fReverse = -1.f;
		_vec3 vLeft;
		get_CameraRight(&vLeft);
		m_bFlyFast == true ? (vLeft = vLeft * m_fFlyFastSpeed * fTimeDelta) : (vLeft = vLeft * m_fFlyNormalSpeed * fTimeDelta);

		_vec3 vLook = (*m_pTransform->Get_Info(INFO_POS) + vLeft);
		m_pTransform->Compute_LookAtTarget(&vLook);
		m_pRidingTargetTransform->Compute_LookAtTarget(&vLook);

		m_pTransform->Move_Pos(&vLeft);
		_float fGroundYPos;
		if (false == check_GroundUpperPos(fGroundYPos))
		{
			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y = fGroundYPos;

			m_pTransform->Set_Info(INFO_POS, &vPos);
		}

		if (DLL::pInputMgr->KeyPressing(DIK_W))
		{
			Set_AnimationSet(L"FlightRight");
			return;
		}
		Set_AnimationSet(L"FlightRun");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_E))
	{
		_vec3 vRight;
		get_CameraRight(&vRight);

		m_bFlyFast == true ? (vRight = vRight * m_fFlyFastSpeed * fTimeDelta) : (vRight = vRight * m_fFlyNormalSpeed * fTimeDelta);

		_vec3 vLook = (*m_pTransform->Get_Info(INFO_POS) + vRight);
		m_pTransform->Compute_LookAtTarget(&vLook);
		m_pRidingTargetTransform->Compute_LookAtTarget(&vLook);

		m_pTransform->Move_Pos(&vRight);
		_float fGroundYPos;
		if (false == check_GroundUpperPos(fGroundYPos))
		{
			_vec3 vPos = *m_pTransform->Get_Info(INFO_POS);
			vPos.y = fGroundYPos;

			m_pTransform->Set_Info(INFO_POS, &vPos);
		}

		if (DLL::pInputMgr->KeyPressing(DIK_W))
		{
			Set_AnimationSet(L"FlightLeft");
			return;
		}

		Set_AnimationSet(L"FlightRun");
	}
}

void CFlyVehicle::ground_KeyInput(const Engine::_float & fTimeDelta)
{
	if (false == m_bRiding)
	{
		return;
	}

	if (DLL::pInputMgr->KeyDown(DIK_R))
	{
		m_bRun = !m_bRun;
	}

	if (DLL::pInputMgr->KeyPressing(DIK_A))
	{
		const _float fDeltaRot = -D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		m_pRidingTargetTransform->Rotation(ROT_Y, fDeltaRot);
		Set_AnimationSet(L"ShuffleLeft");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_D))
	{
		const _float fDeltaRot = D3DXToRadian(180.f) * fTimeDelta;
		m_pTransform->Rotation(ROT_Y, fDeltaRot);
		m_pRidingTargetTransform->Rotation(ROT_Y, fDeltaRot);
		Set_AnimationSet(L"ShuffleRight");
	}

	if (DLL::pInputMgr->KeyPressing(DIK_W))
	{
		_vec3 vDir = *m_pRidingTargetTransform->Get_Info(INFO_LOOK);
		D3DXVec3Normalize(&vDir, &vDir);

		m_bRun == true ? (vDir = vDir * m_fRunSpeed * fTimeDelta) : (vDir = vDir * m_fWalkSpeed * fTimeDelta);

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));

		m_bRun == true ? Set_AnimationSet(L"Run") : Set_AnimationSet(L"Walk");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_S))
	{
		_vec3 vDir = *m_pRidingTargetTransform->Get_Info(INFO_LOOK);
		D3DXVec3Normalize(&vDir, &vDir);

		vDir = vDir * m_fWalkSpeed * fTimeDelta * -1.f;

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vDir));

		Set_AnimationSet(L"WalkBack");
	}
	if (DLL::pInputMgr->KeyPressing(DIK_Q))
	{
		const _float fReverse = -1.f;
		_vec3 vLeft;
		get_CameraRight(&vLeft);
		m_bRun == true ? vLeft *= fReverse * m_fRunSpeed * fTimeDelta : vLeft *= fReverse * m_fWalkSpeed * fTimeDelta;

		_vec3 vLookPos = *m_pTransform->Get_Info(INFO_POS) + vLeft;
		m_pTransform->Compute_LookAtTarget(&vLookPos);
		m_pRidingTargetTransform->Compute_LookAtTarget(&vLookPos);

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vLeft));
		m_bRun == true ? Set_AnimationSet(L"Run") : Set_AnimationSet(L"Walk");
	}
	else if (DLL::pInputMgr->KeyPressing(DIK_E))
	{
		_vec3 vRight;
		get_CameraRight(&vRight);
		m_bRun == true ? vRight *= m_fRunSpeed * fTimeDelta : vRight *= m_fWalkSpeed * fTimeDelta;

		_vec3 vLookPos = *m_pTransform->Get_Info(INFO_POS) + vRight;
		m_pTransform->Compute_LookAtTarget(&vLookPos);
		m_pRidingTargetTransform->Compute_LookAtTarget(&vLookPos);

		m_pTransform->Set_Info(INFO_POS, &DLL::pPickMgr->SetUp_OnTerrain(m_dwNaviIdx, m_pTransform->Get_Info(INFO_POS), &vRight));
		m_bRun == true ? Set_AnimationSet(L"Run") : Set_AnimationSet(L"Walk");
	}
}
