#include "stdafx.h"
#include "SingleEvent.h"

#include "SceneObject/BossZombie.h"

USING(Engine)

CSingleEvent::CSingleEvent(void)
	: m_bActivate(false)

	, m_iCurEvent(0)
	, m_iMaxEvent(4)

	, m_fCurTime(0.f)
	, m_fEventTime(15.f)
{
}

CSingleEvent::~CSingleEvent(void)
{
}

void CSingleEvent::Update_Event(const Engine::_float & fTimeDelta)
{
	if (!m_bActivate || m_iCurEvent == m_iMaxEvent)
	{
		return;
	}

	// 위치에 맞게 몬스터 쭉 생성하기
	// 이벤트 횟수는 3회. 1, 2회는 좀비, 3회는 보스.

	m_fCurTime += fTimeDelta;

	if (m_fCurTime < m_fEventTime)
	{
		return;
	}
	else
	{
		m_fCurTime = 0.f;
	}

	if (m_iCurEvent != m_iMaxEvent - 1)
	{
		// 좀비 생성
		_float fX, fY, fZ;
		for (_int i = 0; i < 20; ++i)
		{
			fX = rand() % 10 + 105.f;
			fY = 4.f;
			fZ = rand() % 20 + 150.f;

			DLL::pPickMgr->Add_Object(dynamic_cast<CPickableObject*>(DLL::pObjContainer->Clone(STAGE_DEFAULT, STAGE_OBJ::STAGE_MONSTER, L"Zombie", &_vec3(fX, fY, fZ))));
		}
		m_iCurEvent++;
	}
	else
	{
		DLL::pSoundMgr->PlaySound(L"BossSpawn.wav", CSoundMgr::CHANNEL_ID::EFFECT);
		DLL::pSoundMgr->SetVolume(CSoundMgr::CHANNEL_ID::EFFECT, 0.5f);
		CGameObject* boss = DLL::pObjContainer->Clone(STAGE_MAP::STAGE_DEFAULT, STAGE_OBJ::STAGE_TERRAIN, L"BossZombie", &_vec3(105.f, 4.f, 150.f));
		DLL::pPickMgr->Add_Object(dynamic_cast<CPickableObject*>(boss));
		m_iCurEvent++;
	}

	
}

void CSingleEvent::Activate_Event()
{
	m_bActivate = true;
}

CSingleEvent * CSingleEvent::Create(void)
{
	return new CSingleEvent;
}

inline void CSingleEvent::freeMem()
{
}
