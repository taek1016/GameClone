#include "stdafx.h"
#include "QuestUI.h"

#include "QuestButton.h"

USING(Engine)

CQuestUI::CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_pAcceptButton(nullptr)
	, m_pDenyButton(nullptr)
{
	set_Name(L"TextUI");
}

Engine::_int CQuestUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	for (auto iter : m_vecFontInfo)
	{
		DLL::pFontMgr->Print_Font(&iter.vPos, &iter.vScale, iter.iLinePerText, iter.pTextData, iter.tColor);
	}

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	if (m_pAcceptButton)
	{
		m_pAcceptButton->Update_GameObject(fTimeDelta);
	}
	if (m_pDenyButton)
	{
		m_pDenyButton->Update_GameObject(fTimeDelta);
	}
	return CGameObject::Update_GameObject(fTimeDelta);
}

Engine::_bool CQuestUI::Get_Accept(void)
{
	return m_pAcceptButton->Get_Clicked();
}

void CQuestUI::Cancel_Accepted(void)
{
	m_pAcceptButton->Cancel_Clicked();
}

void CQuestUI::Clear_Contents(void)
{
	m_vecFontInfo.clear();
}

void CQuestUI::Print_Contents(FONT_INFO & tFontInfo)
{
	m_vecFontInfo.push_back(tFontInfo);
}

void CQuestUI::Quest_AcceptContent(const _tchar* pContent)
{
	m_pAcceptButton->Print_Content(pContent);
}

void CQuestUI::Quest_DenyContent(const _tchar* pContent)
{
	m_pDenyButton->Print_Content(pContent);
}

void CQuestUI::make_Buttons(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	// 전체 348, 높이 435 픽셀
	// 높이 50픽셀 단위로 올리기.
	const _float fHalf = 0.5f;

	const _float fTotalWidth = 348.f;
	const _float fTotalHeight = 435.f;

	_vec3 vScale(200.f / fTotalWidth * pScale->x, 30.f / fTotalHeight * pScale->y, 1.f);
	_vec3 vPos(*pPos);
	vPos.y = pPos->y - pScale->y * fHalf;	// 맨 밑으로 내림
	vPos.y += 70.f / fTotalHeight * pScale->y;

	m_pAcceptButton = CButton::Create(m_pGraphicDev, nullptr, &vPos, &vScale);

	vPos.y -= 40.f / fTotalHeight * pScale->y;
	m_pDenyButton = CButton::Create(m_pGraphicDev, nullptr, &vPos, &vScale);
}

CQuestUI * CQuestUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CQuestUI* pInstance = new CQuestUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->m_wStrName.c_str())))
	{
		Safe_Release(pInstance);
	}

	const _float fHalf = 0.5f;
	const _float fQuarter = 0.25f;
	_vec3 vPos(WINCX * fHalf * fQuarter, 0.f, 0.f);
	_vec3 vScale(WINCX * fQuarter, WINCY * fHalf, 1.f);

	pInstance->Late_InitializeUI(&vPos, &vScale);
	pInstance->make_Buttons(&vPos, &vScale);

	return pInstance;
}

inline void CQuestUI::Free(void)
{
	CUIBase::Free();

	m_vecFontInfo.clear();

	Safe_Release(m_pDenyButton);
	Safe_Release(m_pAcceptButton);
}
