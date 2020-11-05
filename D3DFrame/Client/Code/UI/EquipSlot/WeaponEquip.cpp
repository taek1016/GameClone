#include "stdafx.h"
#include "WeaponEquip.h"

#include "Character/Player.h"

USING(Engine)

CWeaponEquip::CWeaponEquip(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEquipBase(pGraphicDev)
{
	set_Name(L"WeaponSlotUI");
}

void CWeaponEquip::Click_Action(void)
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
		pPlayer->Change_Items(ITEM_WEAPON, m_wstrItemName.c_str());
	}
}

CWeaponEquip * CWeaponEquip::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CWeaponEquip* pInstance = new CWeaponEquip(pGraphicDev);

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
