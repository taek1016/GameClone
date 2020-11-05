#include "stdafx.h"
#include "InfernalSummon.h"

USING(Engine)

CInfernalSummon::CInfernalSummon(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSummonSkillBase(pGraphicDev)
	, m_bInitialized(false)
{
	set_Name(L"InfernalGroundDown");
}

CInfernalSummon::CInfernalSummon(const CInfernalSummon & rhs)
	: CSummonSkillBase(rhs)
	, m_bInitialized(false)
{
}

Engine::_int CInfernalSummon::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (false == m_bInitialized)
	{
		set_InitialData();
	}

	if (m_pMesh->Is_AnimationSetEnd())
	{
		// 몬스터 소환
		DLL::pDataMgr->Clone_CharacterObj(L"Monster", L"Infernal", m_pTransform->Get_Info(INFO_POS));

		return DEAD_OBJ;
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_pMesh->Play_Animation(fTimeDelta);
	DLL::pRenderer->Add_RenderGroup(RENDER_ALPHA, this);

	return iExit;
}

void CInfernalSummon::set_InitialData(void)
{
	m_pMesh->Set_AnimationSet(0);
}

CInfernalSummon * CInfernalSummon::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CInfernalSummon* pInstance = new CInfernalSummon(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Set_Scale(&_vec3(1.5f, 1.5f, 1.5f));
	return pInstance;
}

Engine::CGameObject * CInfernalSummon::Clone(void)
{
	CInfernalSummon* pInstance = new CInfernalSummon(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
