#include "stdafx.h"
#include "InventorySlot.h"

USING(Engine)

CSlot::CSlot(void)
	: CGameObject()
{
	SetName(L"Slot");
}

CSlot::CSlot(const CSlot & rhs)
	: CGameObject(rhs)
{
}

CSlot::~CSlot(void)
{
}

HRESULT CSlot::Late_Initialize()
{
	return S_OK;
}

HRESULT CSlot::Initialize_GameObject()
{
	return S_OK;
}

Engine::_int CSlot::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CSlot::Render_GameObject(void)
{
	DLL::pResourceMgr->Render_Buffer(0, L"Buffer_RcTex");
	DLL::pResourceMgr->Render_Texture(0, m_pItem->Get_Name());
}

CSlot * CSlot::Create(void)
{
	CSlot*	pInstance = new CSlot;

	if (FAILED(pInstance->Initialize_GameObject()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject * CSlot::Clone(const Engine::_vec3 * pPos)
{
	return new CSlot(*this);
}

inline void CSlot::freeMem(void)
{
	CGameObject::freeMem();
}

void CSlot::LoadData(HANDLE hFile)
{
}
