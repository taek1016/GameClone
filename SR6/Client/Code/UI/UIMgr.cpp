#include "stdafx.h"
#include "UIMgr.h"

#include "HitBox.h"

USING(Engine)
IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr(void)
	: m_fCurTime(0.f)
	, m_fHitTime(0.2f)
{
}

CUIMgr::~CUIMgr(void)
{
	freeMem();
}

void CUIMgr::Initialize_UI(void)
{
	m_pHitBox = CHitBox::Create();
	m_pHitBox->Late_Initialize();
}

void CUIMgr::Register_UI(const Engine::_tchar * pKey, CUIBase * pUi)
{
	auto iter = find_if(m_mapUI.begin(), m_mapUI.end(), CTag_Finder(pKey));

	if (m_mapUI.end() != iter)
	{
		return;
	}
	pUi->Late_Initialize();
	m_mapUI[pKey] = pUi;
}

void CUIMgr::Set_Data(const Engine::_tchar * pKey, const Engine::_float& fData)
{
	auto iter = find_if(m_mapUI.begin(), m_mapUI.end(), CTag_Finder(pKey));

	if (m_mapUI.end() == iter)
	{
		return;
	}

	m_mapUI[pKey]->Set_Data(fData);
}

void CUIMgr::Update_Ui(const Engine::_float & fTimeDelta)
{
	for (auto iter : m_mapUI)
	{
		iter.second->Update_GameObject(fTimeDelta);
	}

	if (m_bActivateHit)
	{
		m_pHitBox->Update_GameObject(fTimeDelta);
		m_fCurTime += fTimeDelta;

		if (m_fCurTime >= m_fHitTime)
		{
			m_bActivateHit = false;
			m_fCurTime = 0.f;
		}
	}
}

void CUIMgr::Activate_HitBox(void)
{
	m_bActivateHit = true;
}

inline void CUIMgr::freeMem()
{
	for_each(m_mapUI.begin(), m_mapUI.end(), CDeleteMap());
	m_mapUI.clear();
}