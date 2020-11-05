#include "stdafx.h"
#include "FeetEquip.h"

#include "Character/Player.h"

USING(Engine)

CFeetEquip::CFeetEquip(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEquipBase(pGraphicDev)
{
	set_Name(L"FeetSlotUI");
}

void CFeetEquip::Click_Action(void)
{
	if (m_bClicked)
	{
		return;
	}

	wstring wStrName = DLL::pMouseMgr->Get_ItemName();
	DLL::pMouseMgr->Clear_Name();
	DLL::pMouseMgr->Set_ItemName(m_wstrItemName.c_str());
	m_wstrItemName = wStrName;

	Safe_Release(m_pItemTexture);
	if (!m_wstrItemName.empty())
	{
		m_pItemTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wstrItemName.c_str());
	}

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(DLL::pObjMgr->Get_ObjList(L"Player")->front());

	if (nullptr != pPlayer)
	{
		pPlayer->Change_Items(ITEM_FEET, m_wstrItemName.c_str());
	}
}

CFeetEquip * CFeetEquip::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CFeetEquip* pInstance = new CFeetEquip(pGraphicDev);

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	pInstance->Late_Initialize();

	pInstance->set_Data(pPos, pScale);
	pInstance->make_Slots();
	pInstance->first_Update();

	return pInstance;
}
