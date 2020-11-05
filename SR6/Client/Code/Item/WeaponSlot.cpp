#include "stdafx.h"
#include "WeaponSlot.h"

USING(Engine)

CWeaponSlot::CWeaponSlot(void)
	: CGameObject()
{
	SetName(L"WeaponSlot");
}

CWeaponSlot::CWeaponSlot(const CWeaponSlot & rhs)
	: CGameObject(rhs)
{
}

CWeaponSlot::~CWeaponSlot(void)
{
}

HRESULT CWeaponSlot::Late_Initialize()
{
	m_pTexture = dynamic_cast<CTexture*>(DLL::pResourceMgr->Clone(RESOURCE_STAGE, L"Slot"));
	m_pTexture->Attach(this, ID_STATIC);

	if (nullptr != m_pItem)
	{
		m_wStrRenderKey = m_pItem->Get_Name();
		m_pItem->Late_Initialize();
	}

	return S_OK;
}

HRESULT CWeaponSlot::Initialize_GameObject()
{
	CComponent*	pComponent = nullptr;

	m_pTransform = CTransform::Create();
	m_pTransform->Attach(this, ID_DYNAMIC);
	m_pTransform->Set_Scale(60.f, 60.f, 1.f);


	return S_OK;
}

Engine::_int CWeaponSlot::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	m_bSelected == true ? m_iRenderIdx = 1 : m_iRenderIdx = 0;

	DLL::pRenderer->Add_RenderGroup(RENDER_UI, this);

	return iExit;
}

void CWeaponSlot::Render_GameObject(void)
{
	auto pGraphicDev = DLL::pGraphicDev->GetDevice();

	pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_World());

	m_pTexture->Render_Texture(m_iRenderIdx);
	DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");

	if (m_pItem)
	{
		DLL::pResourceMgr->Render_Texture(RESOURCE_STAGE, m_wStrRenderKey.c_str());
		DLL::pResourceMgr->Render_Buffer(RESOURCE_STATIC, L"Buffer_RcTex");
	}
}

void CWeaponSlot::Set_Item(Engine::CItemBase * pItem)
{
	if (m_pItem)
	{
		Safe_Release(m_pItem);
	}
	m_pItem = pItem;

	if (m_pItem)
	{
		_tchar szName[256]{};
		wsprintf(szName, L"%s%s", m_pItem->Get_Name(), L"Icon");

		m_wStrRenderKey = szName;
	}
}

void CWeaponSlot::Activate_Slot(void)
{
	m_bSelected = true;

}

void CWeaponSlot::Set_Pos(const Engine::_vec3 * pPos)
{
	m_pTransform->Set_Pos(pPos);
}

CWeaponSlot* CWeaponSlot::Create(const Engine::_vec3* pPos, Engine::CItemBase* pItem)
{
	CWeaponSlot*	pInstance = new CWeaponSlot;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}
	pInstance->Set_Pos(pPos);
	pInstance->Set_Item(pItem);

	return pInstance;
}

Engine::CGameObject * CWeaponSlot::Clone(const Engine::_vec3 * pPos)
{
	return new CWeaponSlot(*this);
}

inline void CWeaponSlot::freeMem(void)
{
	CGameObject::freeMem();
}