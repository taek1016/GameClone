#include "stdafx.h"
#include "WalkVehicle.h"

USING(Engine)

CWalkVehicle::CWalkVehicle(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVehicleBase(pGraphicDev)
{
}

CWalkVehicle::CWalkVehicle(const CWalkVehicle & rhs)
	: CVehicleBase(rhs)
{
}

void CWalkVehicle::key_Input(const Engine::_float & fTimeDelta)
{
	Set_AnimationSet(L"Stand");

	if (false == m_bRiding)
	{
		return;
	}

	if (DLL::pInputMgr->KeyDown(DIK_G))
	{

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

		vDir = vDir * m_fWalkSpeed * fTimeDelta;

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
