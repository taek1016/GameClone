#ifndef EngineEntry_h__
#define EngineEntry_h__

// 엔진에서 갖고오는 것
#include "Engine_Defines.h"
#include "Engine_Entry.h"
#include "ComponentMgr.h"
#include "UI/UIMgr.h"
#include "Item/Inventory.h"
#include "Item/CraftingMgr.h"
#include "SceneObject/PickingMgr.h"
#include "SoundMgr.h"
#include "Event/EventMgr.h"

class CEngineEntry
{
public:
	static void InitializeMgr();
	static void Initialize_Key();
	static void DestroyMgr();

	static Engine::CGraphicDev*			pGraphicDev;
	static Engine::CTimerMgr*			pTimerMgr;
	static Engine::CFrameMgr*			pFrameMgr;
	static Engine::CManagement*			pManagement;
	static Engine::CSearchMgr*			pSearchMgr;
	static Engine::CObjectMgr*			pObjMgr;
	static Engine::CResourcesMgr*		pResourceMgr;
	static Engine::CDirectInput*		pDirectInput;
	static Engine::CKeyMgr*				pKeyMgr;
	static Engine::CCameraMgr*			pCameraMgr;
	static Engine::CRenderer*			pRenderer;
	static Engine::CObjContainerMgr*	pObjContainer;
	static Engine::CMouseManager*		pMouseMgr;
	static Engine::CCollisionMgr*		pColMgr;
	static Engine::CPoolMgr*			pPoolMgr;

	static CComponentMgr*				pComMgr;
	static CUIMgr*						pUiMgr;
	static CInventory*					pInventory;
	static CCraftingMgr*				pCraftingMgr;
	static CPickingMgr*					pPickMgr;
	static CSoundMgr*					pSoundMgr;
	static CEventMgr*					pEventMgr;
};

#endif // EngineEntry_h__
