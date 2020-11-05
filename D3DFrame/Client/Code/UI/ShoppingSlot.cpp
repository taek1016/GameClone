#include "stdafx.h"
#include "ShoppingSlot.h"

#include "CoinUI.h"

USING(Engine)

CShoppingSlot::CShoppingSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CItemSlot(pGraphicDev)
	, m_pCoin(nullptr)
	, m_tColor(1.f, 1.f, 0.f, 1.f)
	, m_vFontScale(15.f, 20.f, 1.f)
{
}

Engine::_int CShoppingSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CItemSlot::Update_GameObject(fTimeDelta);

	_int iMoney = DLL::pItemMgr->Get_ItemPrice(m_wStrItemName.c_str());
	m_pCoin->Set_Coins(iMoney);
	m_pCoin->Update_GameObject(fTimeDelta);
	

	DLL::pFontMgr->Print_Font(&m_vStartPos, &m_vFontScale, 10, m_szItemName, m_tColor);

	return iExit;
}

void CShoppingSlot::Click_Action(void)
{
	if (DLL::pInventory->Can_BuyItem(DLL::pItemMgr->Get_ItemPrice(m_wStrItemName.c_str())))
	{
		wstring strTemp = m_wStrItemName;
		m_wStrItemName = DLL::pMouseMgr->Get_ItemName();

		DLL::pMouseMgr->Set_ItemName(strTemp.c_str());
	}
}

void CShoppingSlot::Initialize_Name(void)
{
	::ZeroMemory(m_szItemName, sizeof(_tchar) * 32);
	if (L"DefaultStaff" == m_wStrItemName)
	{
		wsprintf(m_szItemName, L"¼ö½À ÁöÆÎÀÌ");
	}
	else if (L"FinalStaff" == m_wStrItemName)
	{
		wsprintf(m_szItemName, L"Á¹¾÷ ÁöÆÎÀÌ");
	}
	else if (L"BlueCloth" == m_wStrItemName)
	{
		wsprintf(m_szItemName, L"ÆÄ¶õ °¡Á×¿Ê");
	}
	else if (L"MetalPlate" == m_wStrItemName)
	{
		wsprintf(m_szItemName, L"°­Ã¶ÆÇ±Ý");
	}

}

void CShoppingSlot::make_CoinUI(const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	m_vStartPos = *pPos;
	m_vStartPos.x += 30.f;
	m_vStartPos.y += 10.f;

	_vec3 vPos = *pPos;
	vPos.x += 110.f;
	vPos.y -= 10.f;

	_vec3 vScale(*pScale);
	vScale.x *= 2.f;
	vScale.y *= 0.5f;

	m_pCoin = CCoinUI::Create(m_pGraphicDev, &vPos, &vScale);
}

CShoppingSlot * CShoppingSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CShoppingSlot* pInstance = new CShoppingSlot(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	if (FAILED(pInstance->Late_Initialize()))
	{
		Safe_Release(pInstance);
	}

	pInstance->initialize_TextureBuffer();

	pInstance->set_Data(pPos, pScale);
	pInstance->Set_Pos(pPos);
	pInstance->Set_Scale(pScale);
	pInstance->make_CoinUI(pPos, pScale);

	return pInstance;
}
