#include "stdafx.h"
#include "SkillUI.h"

#include "UI/SkillExplaneSlot.h"

USING(Engine)

CSkillUI::CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_bActivated(false)
{
	set_Name(L"AbilityPanelUI");
}

CSkillUI::~CSkillUI(void)
{
}

Engine::_int CSkillUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	if (false == m_bActivated)
	{
		return 0;
	}

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_vecSkillSlots)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	return iExit;
}

void CSkillUI::Activate(void)
{
	m_bActivated = true;
}

void CSkillUI::DeActivate(void)
{
	m_bActivated = false;
}

const Engine::_bool & CSkillUI::Get_Activated(void) const
{
	return m_bActivated;
}

void CSkillUI::make_Slots(const map<const Engine::_tchar*, const Engine::_int>* pMapSKillName, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	const _float fHalf = 0.5f;
	const _float fTotalWidth = 276.f;
	const _float fTotalHeight = 416.f;

	const _float fCenterX = 62.f;

	const _float fXLeftPos = (15.f + fCenterX) / fTotalWidth * pScale->x;
	const _float fXRightPos = (138.f + fCenterX) / fTotalWidth * pScale->x;

	const _float fYGap = 40.f / fTotalHeight * pScale->y;
	const _float fYStartPos = pPos->y + pScale->y * fHalf - 85.f / fTotalHeight * pScale->y - fYGap * fHalf + 5.f;

	const _float fXMapPos = pPos->x - pScale->x * fHalf;
	_vec3 vPos(0.f, fYStartPos, 0.f);
	_vec3 vScale(124.f / fTotalWidth * pScale->x, 40.f / fTotalHeight * pScale->y, 1.f);

	_int iCount = 0;
	for (auto iter : *pMapSKillName)
	{
		if (iCount % 2 == 0)
		{
			vPos.x = fXMapPos + fXLeftPos;
		}
		else
		{
			vPos.x = fXMapPos + fXRightPos;
			iCount++;
		}

		m_vecSkillSlots.push_back(CSkillExplaneSlot::Create(m_pGraphicDev, &vPos, &vScale, iter.first, iter.second));

		if (iCount % 2 == 0)
		{
			iCount = 0;
			vPos.y -= fYGap;
		}
	}
}

CSkillUI * CSkillUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const map<const Engine::_tchar*, const Engine::_int>* pMapSKillName, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CSkillUI* pInstance = new CSkillUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_InitializeUI(pPos, pScale);
	pInstance->make_Slots(pMapSKillName, pPos, pScale);

	return pInstance;
}

Engine::CGameObject * CSkillUI::Clone(void)
{
	return nullptr;
}

inline void CSkillUI::Free(void)
{
	CUIBase::Free();

	for (auto iter : m_vecSkillSlots)
	{
		Safe_Release(iter);
	}
	m_vecSkillSlots.clear();
}
