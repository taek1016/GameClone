#include "stdafx.h"
#include "SummonEffect.h"

#include "../Monster/Monster.h"
#include "../Monster/BigWhiteSkel.h"
#include "../Monster/SkelIceMagician.h"
#include "../Monster/Banshee.h"
#include "../Monster/BigGraySkel.h"

CSummonEffect::CSummonEffect()
	: m_eMonsterType(MONSTER_TYPE::SUMMON_END)
{
	SetObjectKey(L"FX");
	SetObjectStatus(L"MonsterSpawn");

	m_tInfo.SetSize(D3DXVECTOR3(100.f / 31.f, 100.f / 31.f, 0.f));

	m_tFrame.SetMaxFrame(15.f);
}

void CSummonEffect::SpawnMonster()
{
	CMonster* pInstance = nullptr;

	switch (m_eMonsterType)
	{
	case BIG_SKEL:
		pInstance = CBigWhiteSkel::Create(m_tInfo.vPos);
		break;

	case ICE_MAGICIAN:
		pInstance = CSkelIceMagician::Create(m_tInfo.vPos);
		break;

	case BANSHEE:
		pInstance = CBanshee::Create(m_tInfo.vPos);
		break;

	case BIG_SKILL_SKEL:
		pInstance = CBigGraySkel::Create(m_tInfo.vPos);
		break;
	}

	CSINGLETON::pObjectMgr->AddObject(OBJECT_TYPE::OBJECT_MONSTER, pInstance);
}

CSummonEffect::~CSummonEffect()
{
	m_eMonsterType = MONSTER_TYPE::SUMMON_END;
}

CSummonEffect * CSummonEffect::Create(const D3DXVECTOR3 & vecPos, MONSTER_TYPE eMonsterType)
{
	CSummonEffect* pInstance = new CSummonEffect;

	pInstance->m_tInfo.SetPos(vecPos);
	pInstance->SetMonster(eMonsterType);

	return pInstance;
}

int CSummonEffect::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * CSINGLETON::pTimeMgr->GetDelta();

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
	{
		SpawnMonster();
		return DEAD_OBJ;
	}

	return NO_EVENT;
}

void CSummonEffect::LateUpdate()
{
	CSINGLETON::pMathMgr->CalculateMove(m_tInfo.matWorld, m_tInfo.vPos, m_tInfo.vSize, 0.f);
}

void CSummonEffect::Render()
{
	const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
	(
		m_wStrObjectKey, 
		m_wStrObjectStatus, 
		static_cast<WORD>(m_tFrame.fCurFrame)
	);

	CSINGLETON::pDirectMgr->RenderImage(pTexInfo, m_tInfo.matWorld, m_tInfo.iColorValue);
}

void CSummonEffect::UpdateRect()
{
}
