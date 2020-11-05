#include "stdafx.h"
#include "SummonMeteor.h"

USING(Engine)

CSummonMeteor::CSummonMeteor(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTextureSkillBase(pGraphicDev)
	, m_fLifeTime(0.f)
{
	set_Name(L"SummonMeteor");
}

CSummonMeteor::CSummonMeteor(const CSummonMeteor & rhs)
	: CTextureSkillBase(rhs)
	, m_fLifeTime(0.f)
{
}

void CSummonMeteor::check_TextureIndex(const Engine::_float & fTimeDelta)
{
	m_fLifeTime += fTimeDelta;

	const _float fEndTime = 10.f;
	if (m_fLifeTime >= fEndTime)
	{
		m_bDead = true;
		return;
	}
}

void CSummonMeteor::dead_Action(const Engine::_float & fTimeDelta)
{
}

void CSummonMeteor::act_Determine(const Engine::_float & fTimeDelta)
{
	if (m_bDead)
	{
		return;
	}

	m_fCurIndex += fTimeDelta;

	if (m_fCurIndex >= 0.4f)
	{
		m_fCurIndex = 0.f;

		auto pOriPos = m_pTransform->Get_Info(INFO_POS);
		_vec3 vPos = *pOriPos;
		const _int iZoneLimit = 50;
		for (_int i = 0; i < 10; ++i)
		{
			vPos.x = pOriPos->x + rand() % iZoneLimit;
			vPos.z = pOriPos->z + rand() % iZoneLimit;

			summon_Meteor(&vPos);
		}
	}
}

void CSummonMeteor::summon_Meteor(const Engine::_vec3* pPos)
{
	auto pPlayerPos = DLL::pObjMgr->Get_ObjList(L"Player")->front()->Get_Pos();
	_vec3 vDir = *pPlayerPos - *m_pTransform->Get_Info(INFO_POS);
	D3DXVec3Normalize(&vDir, &vDir);

	auto pSkill = DLL::pSkillMgr->Get_MonsterSkill(L"Meteor", pPos, &vDir);
	pSkill->SetUp_Index();
	DLL::pObjMgr->Add_GameObject(L"Skill", pSkill);
}

CSummonMeteor * CSummonMeteor::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSummonMeteor* pInstance = new CSummonMeteor(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();
	pInstance->Set_Scale(&_vec3(100.f, 1.f, 100.f));

	return pInstance;
}

Engine::CGameObject * CSummonMeteor::Clone(void)
{
	CSummonMeteor* pInstance = new CSummonMeteor(*this);

	pInstance->Late_Initialize();

	return pInstance;
}
