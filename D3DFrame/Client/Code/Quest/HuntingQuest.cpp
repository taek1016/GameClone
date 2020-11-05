#include "stdafx.h"
#include "HuntingQuest.h"

#include "Character/Player.h"

USING(Engine)

CHuntingQuest::CHuntingQuest(void)
	: CQuestBase()
	, m_iKillGoal(0)
	, m_iCurKillNum(0)
{
}

void CHuntingQuest::Update_Quest(void)
{
	if (false == m_bActivated)
	{
		return;
	}

	if (m_iCurKillNum >= m_iKillGoal)
	{
		if (false == m_bFinished)
		{
			DLL::pSoundMgr->PlaySound(L"QuestComplete.wav", CSoundMgr::EFFECT);
			DLL::pSoundMgr->SetVolume(CSoundMgr::EFFECT, 0.3f);
			dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front())->Get_Exp(m_iExp);
		}
		m_bFinished = true;
	}

	if (m_bActivated)
	{
		// 퀘스트 순번 받아오기
		wsprintf(m_szContentStr, L"%d. %s %s : %d / %d %s", m_iQuestCount, 
			m_szTargetName, L"사냥하기", m_iCurKillNum, m_iKillGoal, m_bFinished == true ? L"V" : L" ");
		DLL::pFontMgr->Print_Font(&m_vPos, &m_vScale, m_iLineCount, m_szContentStr, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
	}
}

void CHuntingQuest::Add_KillNum(void)
{
	if (m_bActivated && false == m_bFinished)
	{
		m_iCurKillNum++;
	}
}

void CHuntingQuest::set_TargetName(const Engine::_tchar * pTargetName)
{
	if (0 == wcscmp(pTargetName, L"Boar"))
	{
		lstrcpy(m_szTargetName, L"돼지");
	}
	else if (0 == wcscmp(pTargetName, L"KodoBeast"))
	{
		lstrcpy(m_szTargetName, L"코도비스트");
	}
	else if (0 == wcscmp(pTargetName, L"Nefarian"))
	{
		lstrcpy(m_szTargetName, L"네파리안");
	}
}

void CHuntingQuest::set_KillNum(const Engine::_int & iGoalNum)
{
	m_iKillGoal = iGoalNum;
}

void CHuntingQuest::set_Exp(const Engine::_int & iExp)
{
	m_iExp = iExp;
}

CHuntingQuest * CHuntingQuest::Create(const Engine::_tchar * pTargetName, const Engine::_int& iCount, const Engine::_int& iExp)
{
	CHuntingQuest* pInstance = new CHuntingQuest;

	pInstance->set_TargetName(pTargetName);
	pInstance->set_KillNum(iCount);
	pInstance->set_Exp(iExp);

	return pInstance;
}

inline void CHuntingQuest::Free(void)
{
	CQuestBase::Free();

	m_iCurKillNum = 0;
	m_iKillGoal = 0;

	ZeroMemory(m_szTargetName, sizeof(_tchar) * 32);
}
