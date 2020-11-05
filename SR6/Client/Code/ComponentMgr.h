#ifndef ComponentMgr_h__
#define ComponentMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

class Engine::CComponent;
class Engine::CGameObject;
class CComponentMgr : public CBase
{
	DECLARE_SINGLETON(CComponentMgr);

	CComponentMgr();
	~CComponentMgr();

public:
	Engine::CComponent* CreateComponent(Engine::CGameObject* obj, Engine::COMPONENT_TYPE type);

	// CBase을(를) 통해 상속됨
	virtual void freeMem(void) override;
};

#endif