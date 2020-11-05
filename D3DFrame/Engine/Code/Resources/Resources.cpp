#include "Resources.h"

#include "Engine_Entry.h"
USING(Engine)

CResources::CResources(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_bClone(false)
{
	m_pGraphicDev->AddRef();
}

CResources::CResources(const CResources& rhs)
	: m_bClone(true)
	, m_pGraphicDev(rhs.m_pGraphicDev)
{
	m_pGraphicDev->AddRef();
}

CResources::~CResources(void)
{
}

HRESULT CResources::Attach(const _tchar * pKey, CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(pKey, this, com_ID);

	return S_OK;
}

void CResources::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
