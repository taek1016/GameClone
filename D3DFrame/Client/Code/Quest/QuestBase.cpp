#include "stdafx.h"
#include "QuestBase.h"

USING(Engine)

CQuestBase::CQuestBase(void)
	: m_bActivated(false)
	, m_bFinished(false)
	, m_szContentStr{}
	, m_iQuestCount(0)
	, m_iLineCount(25)
	, m_vPos(0.f, 0.f, 0.f)
	, m_vScale(0.f, 0.f, 0.f)
{
}

void CQuestBase::Set_QuestCount(const Engine::_int & iCount)
{
	m_iQuestCount = iCount;

	m_vScale = _vec3(20.f, 20.f, 1.f);

	m_vPos.x = WINCX * 0.5f - m_vScale.x * m_iLineCount;
	m_vPos.y = WINCY * 0.3f - m_iQuestCount * (m_vScale.y * 2.f);
	m_vPos.z = 0.f;
}

void CQuestBase::Activate_Quest(void)
{
	DLL::pSoundMgr->PlaySound(L"QuestActivate.wav", CSoundMgr::EFFECT);
	DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);
	m_bActivated = true;
}

Engine::_bool CQuestBase::Get_Activated(void) const
{
	return m_bActivated;
}

Engine::_bool CQuestBase::Get_Finished(void) const
{
	return m_bFinished;
}

Engine::_int CQuestBase::Get_QuestNum(void) const
{
	return m_iQuestCount;
}

const Engine::_tchar * CQuestBase::Get_TargetName(void) const
{
	return m_szTargetName;
}

inline void CQuestBase::Free(void)
{
	m_bActivated = false;
	m_bFinished = false;

	m_iQuestCount = 0;
	m_iLineCount = 0;

	ZeroMemory(m_szContentStr, sizeof(_tchar) * 128);
	ZeroMemory(m_szQuestCount, sizeof(_tchar) * 32);

	ZeroMemory(&m_vPos, sizeof(_vec3));
	ZeroMemory(&m_vScale, sizeof(_vec3));

}
