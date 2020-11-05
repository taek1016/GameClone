#include "stdafx.h"
#include "SkillSlotUI.h"

#include "SkillSlot.h"

USING(Engine)

CSkillSlotUI::CSkillSlotUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
	set_Name(L"SkillUI");
}

CSkillSlotUI::~CSkillSlotUI(void)
{
}

Engine::_int CSkillSlotUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	CGameObject::Update_GameObject(fTimeDelta);

	for (auto iter : m_mapSkillSlot)
	{
		iter.second->Update_GameObject(fTimeDelta);
	}

	for (auto iter : m_mapSkillSlot)
	{
		if (iter.second->Get_Clicked())
		{
			iter.second->Click_Action();
		}
	}

	DLL::pRenderer->Add_RenderGroup(RENDERID::RENDER_UI, this);

	return 0;
}

void CSkillSlotUI::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture();
	m_pBuffer->Render_Buffer();

	for (auto iter : m_mapSkillSlot)
	{
		iter.second->Render_GameObject();
	}
}

void CSkillSlotUI::Change_UI(const Engine::_tchar * pKey)
{
}

void CSkillSlotUI::make_Buttons(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{

	// ÀüÃ¼ ³Êºñ 665, ³ôÀÌ 85
	const _float fTotalWidth = 665.f;
	const _float fTotalHeight = 85.f;

	// ÇÑ Ä­ ´ç 35ÇÈ¼¿, 35ÇÈ¼¿
	const _float fPixelWidth = 35.f;
	const _float fPixelHeight = 35.f;

	_vec3 vScale(pScale->x * (fPixelWidth / fTotalWidth), pScale->y * (fPixelHeight / fTotalHeight), 1.f);

	// °£°ÝÀº 7ÇÈ¼¿ ´ÜÀ§
	const _float fGapX = 7.f;

	const _float fHalf = 0.5f;

	_vec3 vPos(0.f, 0.f, 0.f);
	// ½ÃÀÛ xÁöÁ¡Àº 107ÇÈ¼¿ + 17.5 ÇÈ¼¿ ÁöÁ¡
	const _float fStartXPos = pPos->x - pScale->x * fHalf;
	const _float fStartYPos = pPos->y - pScale->y * fHalf;

	vPos.x = fStartXPos + pScale->x * (107.f + fPixelWidth * fHalf) / fTotalWidth;
	// ³ôÀÌ´Â ¹Ø 2ÇÈ¼¿ + 17.5ÇÈ¼¿ ÁöÁ¡
	vPos.y = fStartYPos + pScale->y * (2.f + fPixelHeight * fHalf) / fTotalHeight;

	TCHAR* szDefault = L"Slot";
	vector<TCHAR*> vecNames;

	const _int iMaxSlot = 11;
	const _int iMaxStr = 256;
	TCHAR szNames[iMaxStr];

	const _float fRealGapX = pScale->x * (fPixelWidth + fGapX) / fTotalWidth;

	for (_int i = 0; i < iMaxSlot; ++i)
	{
		::ZeroMemory(szNames, sizeof(TCHAR) * iMaxStr);
		wsprintf(szNames, L"%s%d", szDefault, i + 1);

		m_mapSkillSlot.emplace(szNames, CSkillSlot::Create(m_pGraphicDev, &vPos, &vScale, i + 1));

		vPos.x += fRealGapX;
	}
}

CSkillSlotUI * CSkillSlotUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CSkillSlotUI* pInstance = new CSkillSlotUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Buttons(pPos, pScale);

	return pInstance;
}

Engine::CGameObject * CSkillSlotUI::Clone(void)
{
	return nullptr;
}

inline void CSkillSlotUI::Free(void)
{
	CGameObject::Free();

	for (auto iter : m_mapSkillSlot)
	{
		Safe_Release(iter.second);
	}
}
