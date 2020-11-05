#include "stdafx.h"
#include "EquipSlot.h"

USING(Engine)

CEquipSlot::CEquipSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSlotBase(pGraphicDev)
	, m_pItemBuffer(nullptr)
	, m_pItemTexture(nullptr)
	, m_eEquipData(EQUIP_ENUM::ITEM_END)
{
}

void CEquipSlot::Render_GameObject(void)
{
	CSlotBase::Render_GameObject();

	if (nullptr != m_pItemTexture)
	{
		m_pItemTexture->Render_Texture();
		m_pItemBuffer->Render_Buffer();
	}
}

void CEquipSlot::Set_Texture(const Engine::_tchar * pName)
{
	if (nullptr != m_pTexture)
	{
		Safe_Release(m_pItemTexture);
	}

	m_pItemTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrItemName.c_str());
}

void CEquipSlot::Click_Action(void)
{
	if (m_bClicked)
	{
		return;
	}

	wstring strTemp = m_wStrItemName;

	m_wStrItemName = DLL::pMouseMgr->Get_ItemName();
	if (false == m_wStrItemName.empty())
	{
		Set_Texture(m_wStrItemName.c_str());
	}
	DLL::pMouseMgr->Set_ItemName(strTemp.c_str());

	// 바로 캐릭터에 아이템 매니저에서 클론 때려서 넘겨주기.

}

void CEquipSlot::initialize_TextureBuffer(void)
{
	m_pItemBuffer = CRcTex::Create(m_pGraphicDev);
}

CEquipSlot * CEquipSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale)
{
	CEquipSlot* pInstance = new CEquipSlot(pGraphicDev);

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

	return pInstance;
}

inline void CEquipSlot::Free(void)
{
	CSlotBase::Free();

	Safe_Release(m_pItemBuffer);
	Safe_Release(m_pItemTexture);
}
