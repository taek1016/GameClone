#include "stdafx.h"
#include "HeadEquip.h"

#include "Character/Player.h"

USING(Engine)

CHeadEquip::CHeadEquip(LPDIRECT3DDEVICE9 pGraphicDev)
	: CEquipBase(pGraphicDev)
{
	set_Name(L"HeadSlotUI");
}

void CHeadEquip::Click_Action(void)
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
		pPlayer->Change_Items(ITEM_HEAD, m_wstrItemName.c_str());
	}
}

CHeadEquip * CHeadEquip::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CHeadEquip* pInstance = new CHeadEquip(pGraphicDev);

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
