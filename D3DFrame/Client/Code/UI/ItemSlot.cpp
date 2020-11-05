#include "stdafx.h"
#include "ItemSlot.h"

USING(Engine)

CItemSlot::CItemSlot(LPDIRECT3DDEVICE9 pGraphicDev)
	: CSlotBase(pGraphicDev)
	, m_pItemTexture(nullptr)
	, m_pItemBuffer(nullptr)
	, m_bIsInShop(false)
{
}

CItemSlot::~CItemSlot(void)
{
}

Engine::_int CItemSlot::Update_GameObject(const Engine::_float & fTimeDelta)
{
	_int iExit = CSlotBase::Update_GameObject(fTimeDelta);

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CItemSlot::Render_GameObject(void)
{
	CSlotBase::Render_GameObject();

	if (m_pItemTexture)
	{
		m_pItemTexture->Render_Texture();
		m_pItemBuffer->Render_Buffer();
	}
}

void CItemSlot::Set_Texture(const Engine::_tchar * pName)
{
	if (nullptr != m_pTexture)
	{
		Safe_Release(m_pItemTexture);
	}

	m_pItemTexture = DLL::pResourcesMgr->Clone<CTexture>(RESOURCE_TEXTURE, m_wStrItemName.c_str());
}

void CItemSlot::Click_Action(void)
{

	wstring strTemp = m_wStrItemName;
	m_wStrItemName = DLL::pMouseMgr->Get_ItemName();

	if (false == m_wStrItemName.empty())
	{
		Set_Texture(m_wStrItemName.c_str());
	}
	else
	{
		Clear_Item();
	}
	DLL::pMouseMgr->Set_ItemName(strTemp.c_str());
}

Engine::_bool CItemSlot::Is_Empty(void) const
{
	if (m_wStrItemName.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CItemSlot::Set_Item(const Engine::_tchar * pName)
{
	m_wStrItemName = pName;
	Set_Texture(pName);
}

void CItemSlot::Clear_Item(void)
{
	m_wStrItemName.clear();
	Safe_Release(m_pItemTexture);
}

const Engine::_tchar * CItemSlot::Get_Item(void) const
{
	return m_wStrItemName.c_str();
}

void CItemSlot::initialize_TextureBuffer(void)
{
	m_pItemBuffer = CRcTex::Create(m_pGraphicDev);
}

CItemSlot * CItemSlot::Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3 * pPos, const Engine::_vec3 * pScale, const Engine::_bool& bIsInShop)
{
	CItemSlot* pInstance = new CItemSlot(pGraphicDev);

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
	pInstance->m_bIsInShop = bIsInShop;

	return pInstance;
}

inline void CItemSlot::Free(void)
{
	CSlotBase::Free();

	Safe_Release(m_pItemBuffer);
	Safe_Release(m_pItemTexture);
}
