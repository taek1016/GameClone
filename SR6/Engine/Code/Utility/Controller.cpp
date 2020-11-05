#include "Controller.h"

USING(Engine)

CController::CController(void)
	: CComponent()
{
}

CController::~CController(void)
{
}

HRESULT CController::Attach(CGameObject * pObj, COMPONENTID com_ID)
{
	m_pGameObject = pObj;
	m_pGameObject->Add_Component(COMPONENT_TYPE::CONTROLLER, this, com_ID);

	return S_OK;
}

inline void CController::freeMem()
{
	CComponent::freeMem();
}
