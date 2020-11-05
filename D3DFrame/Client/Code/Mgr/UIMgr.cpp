#include "stdafx.h"
#include "UIMgr.h"

#include "UI/UIBase.h"

USING(Engine)
IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr(void)
	: CBase()
	, m_bUIAct(false)
{
}

CUIMgr::~CUIMgr(void)
{
	Free();
}

void CUIMgr::Update_UI(const Engine::_float & fTimeDelta)
{
	if (false == m_bUIAct)
	{
		return;
	}

	for (auto iter : m_mapUI)
	{
		iter.second->Update_GameObject(fTimeDelta);
	}
}

void CUIMgr::Add_UI(const Engine::_tchar * pName, CUIBase * pUI)
{
	auto iter = m_mapUI.find(pName);

	if (m_mapUI.end() != iter)
	{
		return;
	}

	m_mapUI.emplace(pName, pUI);
}

void CUIMgr::Set_Target(const Engine::_tchar * pName, Engine::CGameObject * pObj)
{
	auto iter = m_mapUI.find(pName);

	if (m_mapUI.end() == iter)
	{
		return;
	}

	iter->second->Set_Target(pObj);
}

void CUIMgr::Set_Act(void)
{
	m_bUIAct = !m_bUIAct;
}

inline void CUIMgr::Free(void)
{
	for (auto iter : m_mapUI)
	{
		Safe_Release(iter.second);
	}
}
