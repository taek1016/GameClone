#include "stdafx.h"
#include "InventoryUI.h"

#include "InventoryUISlot.h"

USING(Engine)

CInventoryUI::CInventoryUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUIBase(pGraphicDev)
{
	set_Name(L"SlotBase");
}

Engine::_int CInventoryUI::Update_GameObject(const Engine::_float & fTimeDelta)
{
	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	for (auto iter : m_vecSlots)
	{
		iter->Update_GameObject(fTimeDelta);

		if (iter->Get_Clicked())
		{
			iter->Click_Action();
		}
	}

	return 0;
}

void CInventoryUI::set_Buttons(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	const _int iSlotNum = 4;

	m_vecSlots.resize(iSlotNum);

	const _float fHalf = 0.5f;

	// 전체 315, 42픽셀
	const _float fGapX = 20.f / 305.f * pScale->x;
	const _float fGapY = 5.f / 42.f * pScale->y;

	_vec3 vPos = *pPos;

	// 시작점
	vPos.x -= pScale->x * fHalf * 0.4f + 2 * fGapX;

	const _float fEachXWidth = (305.f * 0.75f) / (iSlotNum) - fGapX;
	const _float fEachYHeight = pScale->y - 2 * fGapY;

	_vec3 vScale(fEachXWidth, fEachYHeight, 1.f);

	for (_int i = 0; i < iSlotNum; ++i)
	{
		m_vecSlots[i] = CInventorySlot::Create(m_pGraphicDev, &vPos, &vScale, i);
		vPos.x += fGapX + fEachXWidth;
	}

	m_vecSlots[0]->Set_BagName(L"BagOneFourIcon");
}

CInventoryUI * CInventoryUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CInventoryUI* pInstance = new CInventoryUI(pGraphicDev);

	if (FAILED(pInstance->Initialize_UI(pInstance->Get_Name())))
	{
		Safe_Release(pInstance);
	}

	if (FAILED(pInstance->Late_InitializeUI(pPos, pScale)))
	{
		Safe_Release(pInstance);
	}

	pInstance->set_Buttons(pPos, pScale);

	return pInstance;
}

inline void CInventoryUI::Free(void)
{
	CUIBase::Free();

	for (auto iter : m_vecSlots)
	{
		Safe_Release(iter);
	}
}
