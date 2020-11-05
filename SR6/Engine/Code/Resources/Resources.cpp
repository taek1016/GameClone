#include "Resources.h"

#include "Engine_Entry.h"
#include "GameObject.h"

USING(Engine)

CResources::CResources(void)
	: m_pGraphicDev(Ready_GraphicDev()->GetDevice())
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

HRESULT CResources::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::BUFFER, this, com_ID);

	return S_OK;
}

void CResources::freeMem(void)
{
	Safe_Release(m_pGraphicDev);
}