#include "stdafx.h"
#include "QuestMgr.h"

#include "Quest/QuestBase.h"
#include "Quest/HuntingQuest.h"

USING(Engine)
IMPLEMENT_SINGLETON(CQuestMgr)

CQuestMgr::CQuestMgr(void)
	: m_iQuestCount(0)
{
}

CQuestMgr::~CQuestMgr(void)
{
	Free();
}

void CQuestMgr::Update_Quest(void)
{
	for (auto iter : m_HuntingQuestMap)
	{
		iter.second->Update_Quest();
	}
}

void CQuestMgr::Add_HuntingQuest(const Engine::_tchar * pHuntingName, const Engine::_int& iCount, const Engine::_int& iExp)
{
	auto iter = find_if(m_HuntingQuestMap.begin(), m_HuntingQuestMap.end(), CTag_Finder(pHuntingName));

	if (iter != m_HuntingQuestMap.end())
	{
		return;
	}

	m_HuntingQuestMap.emplace(pHuntingName, CHuntingQuest::Create(pHuntingName, iCount, iExp));
}

void CQuestMgr::Kill_Monster(const Engine::_tchar * pMonsterName)
{
	auto iter = find_if(m_HuntingQuestMap.begin(), m_HuntingQuestMap.end(), CTag_Finder(pMonsterName));

	if (m_HuntingQuestMap.end() == iter)
	{
		return;
	}

	dynamic_cast<CHuntingQuest*>(iter->second)->Add_KillNum();
}

void CQuestMgr::Activate_HuntingQuest(const Engine::_tchar * pHuntingQuest)
{
	auto iter = find_if(m_HuntingQuestMap.begin(), m_HuntingQuestMap.end(), CTag_Finder(pHuntingQuest));

	if (m_HuntingQuestMap.end() == iter)
	{
		return;
	}

	iter->second->Activate_Quest();
	iter->second->Set_QuestCount(++m_iQuestCount);
}

const Engine::_tchar * CQuestMgr::Get_ActivatedQuestName(void)
{
	_int iCurCount = m_iQuestCount - 1;

	for (auto iter : m_HuntingQuestMap)
	{
		if (iCurCount == iter.second->Get_QuestNum())
		{
			return iter.second->Get_TargetName();
		}
	}

	return nullptr;
}

const Engine::_tchar * CQuestMgr::Get_NextQuestName(void)
{
	_int iCurCount = m_iQuestCount;

	_bool bPicked = false;
	for (auto iter : m_HuntingQuestMap)
	{
		if (iCurCount == iter.second->Get_QuestNum())
		{
			bPicked = true;
			continue;
		}

		if (false == bPicked)
		{
			continue;
		}

		if (0 == wcscmp(iter.second->Get_TargetName(), L"돼지"))
		{
			return L"Boar";
		}
		else if (0 == wcscmp(iter.second->Get_TargetName(), L"코도비스트"))
		{
			return L"KodoBeast";
		}
		else if (0 == wcscmp(iter.second->Get_TargetName(), L"네파리안"))
		{
			return L"Nefarian";
		}

	}

	return nullptr;
}

Engine::_bool CQuestMgr::Is_Cleared(const Engine::_tchar * pKey)
{
	auto iter = find_if(m_HuntingQuestMap.begin(), m_HuntingQuestMap.end(), CTag_Finder(pKey));

	if (m_HuntingQuestMap.end() == iter)
	{
		return false;
	}

	return iter->second->Get_Finished();
}

inline void CQuestMgr::Free(void)
{
	for (auto iter : m_HuntingQuestMap)
	{
		Safe_Release(iter.second);
	}
	m_iQuestCount = 0;
}
