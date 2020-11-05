#include "stdafx.h"
#include "EquipBase.h"

USING(Engine)

CEquipBase::CEquipBase(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSlotBase(pGraphicDev)
	, m_pItemTexture(nullptr)
	, m_pItemBuffer(nullptr)
{
}

void CEquipBase::Render_GameObject(void)
{
	CSlotBase::Render_GameObject();

	if (m_pItemTexture)
	{
		m_pItemTexture->Render_Texture();
		m_pBuffer->Render_Buffer();
	}
}

void CEquipBase::first_Update(void)
{
	m_pTransform->Update_Component(0.f);
}

void CEquipBase::make_Slots(void)
{
	if (m_pTexture)
	{
		Safe_Release(m_pTexture);
	}

	m_pTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrName.c_str());
}

inline void CEquipBase::Free(void)
{
	CSlotBase::Free();

	Safe_Release(m_pItemTexture);
	Safe_Release(m_pItemBuffer);
}
