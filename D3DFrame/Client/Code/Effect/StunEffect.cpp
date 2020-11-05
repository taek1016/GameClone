#include "stdafx.h"
#include "StunEffect.h"

#include "Character/Player.h"

USING(Engine)

CStunEffect::CStunEffect(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMeshEffectBase(pGraphicDev)
	, m_fStunTime(0.f)
{
	set_Name(L"Stun");
}

CStunEffect::CStunEffect(const CStunEffect & rhs)
	: CMeshEffectBase(rhs)
	, m_fStunTime(0.f)
{
}

void CStunEffect::Ready_ToGo(void)
{
	m_fStunTime = 0.f;
}

void CStunEffect::act_Determine(const Engine::_float & fTimeDelta)
{
	m_fStunTime += fTimeDelta;

	if (m_fStunTime >= 3.f)
	{
		m_bDead = true;
	}

	auto pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	_matrix matNewPos = (pPlayer->Get_Component<CDynamicMesh>(L"Mesh", ID_STATIC)->Get_FrameByName("bloodelfmale_Bone130")->CombinedTransformationMatrix
		* *pPlayer->Get_Component<CTransform>(L"Transform", ID_DYNAMIC)->Get_World() * *m_pTransform->Get_World());

	matNewPos._42 += 5.f;

	m_pTransform->Set_WorldMatrix(&matNewPos);

	_vec3 vPos;
	memcpy(&vPos, matNewPos.m[3], sizeof(_vec3));

	m_pTransform->Set_Info(INFO_POS, &vPos);
}

CStunEffect * CStunEffect::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStunEffect* pInstance = new CStunEffect(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->read_Data();

	return pInstance;
}

Engine::CGameObject * CStunEffect::Clone(void)
{
	CStunEffect* pInstance = new CStunEffect(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
