#include "stdafx.h"
#include "DealUI.h"

#include "ItemExplanationSlot.h"
#include "CoinUI.h"

USING(Engine)

CDealUI::CDealUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
	, m_bActivated(false)
	, m_pCoinUI(nullptr)
{
	set_Name(L"MerchantUI");
}

Engine::_int CDealUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_vecItemSlots)
	{
		iter->Update_GameObject(fTimeDelta);
	}

	_int iMoney = DLL::pInventory->Get_Money();
	m_pCoinUI->Set_Coins(iMoney);
	m_pCoinUI->Update_GameObject(fTimeDelta);

	return 0;
}

const Engine::_bool CDealUI::Get_Activated(void) const
{
	return m_bActivated;
}

void CDealUI::Activate(void)
{
	m_bActivated = true;
}

void CDealUI::DeActivate(void)
{
	m_bActivated = false;
}

void CDealUI::make_Items(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	const _float fHalf = 0.5f;
	// ÀüÃ¼ ³Êºñ 350, ³ôÀÌ 454
	const _float fTotalWidth = 350.f;
	const _float fTotalHeight = 454.f;

	// ½½·Ô ½ÃÀÛ ³Êºñ´Â 20ÇÈ¼¿, ³Êºñ 5ÇÈ¼¿
	const _float fStartPosX = pPos->x - (pScale->x * fHalf) + (20.f / fTotalWidth) * pScale->x;
	// ½½·Ô ½ÃÀÛ ³ôÀÌ´Â 74ÇÈ¼¿
	const _float fStartPosY = pPos->y + (pScale->y * fHalf) - (74.f / fTotalHeight) * pScale->y;

	// ½Ç ³Êºñ´Â 320 ÇÈ¼¿, ½Ç ³ôÀÌ´Â 320 ÇÈ¼¿
	// µû¶ó¼­ ÇÑ Ä­Àº 150, 50ÇÈ¼¿.
	//pScale->x * (20.f / fTotalWidth)
	const _float fXGap = 5.f / fTotalWidth * pScale->x;
	const _float fYGap = 10.f / fTotalHeight * pScale->y;

	_vec3 vScale(150.f / fTotalWidth * pScale->x, 50.f / fTotalHeight * pScale->y, 1.f);
	_vec3 vPos(fStartPosX + fXGap, fStartPosY - fYGap, 0.f);
	
	_vec3 vOneSlot = vPos;
	_vec3 vTwoSlot = vPos;
	vTwoSlot.x += vScale.x;

	const _tchar* pItemNames[] = { L"DefaultStaff", L"FinalStaff", L"BlueCloth", L"MetalPlate" };
	const _int iSize = sizeof(pItemNames) / sizeof(pItemNames[0]);

	for (_int i = 0; i < iSize; ++i)
	{
		if (i % 2 == 0)
		{
			vPos.x = vOneSlot.x;
			vPos.y = vPos.y - vScale.y * i;
		}
		else
		{
			vPos.x = vTwoSlot.x;
		}

		m_vecItemSlots.push_back(CItemExplanationSlot::Create(m_pGraphicDev, &vPos, &vScale, pItemNames[i]));
	}

	vPos.x = pPos->x + (pScale->x * fHalf);
	vPos.y = pPos->y - pScale->y * fHalf + 15.f / fTotalHeight * pScale->y;
	vScale.x = 150.f / fTotalWidth * pScale->x;
	vScale.y = 10.f / fTotalHeight * pScale->y;
	m_pCoinUI = CCoinUI::Create(m_pGraphicDev, &vPos, &vScale);
}

CDealUI * CDealUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDealUI* pInstance = new CDealUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	const _float fHalf = 0.5f;
	const _float fQuarter = 0.25f;
	_vec3 vPos(-WINCX * fHalf * fQuarter, 0.f, 0.f);
	_vec3 vScale(WINCX * fQuarter, WINCY * fHalf, 1.f);

	if (FAILED(pInstance->Late_InitializeUI(&vPos, &vScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->make_Items(&vPos, &vScale);

	return pInstance;
}

Engine::CGameObject * CDealUI::Clone(void)
{
	return nullptr;
}

inline void CDealUI::Free(void)
{
	CUIBase::Free();

	for (auto iter : m_vecItemSlots)
	{
		Safe_Release(iter);
	}
}
