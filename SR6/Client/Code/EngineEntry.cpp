#include "stdafx.h"
#include "EngineEntry.h"

USING(Engine)

CGraphicDev*		CEngineEntry::pGraphicDev = nullptr;
CTimerMgr*			CEngineEntry::pTimerMgr = nullptr;
CFrameMgr*			CEngineEntry::pFrameMgr = nullptr;
CManagement*		CEngineEntry::pManagement = nullptr;
CObjectMgr*			CEngineEntry::pObjMgr = nullptr;
CResourcesMgr*		CEngineEntry::pResourceMgr = nullptr;
CDirectInput*		CEngineEntry::pDirectInput = nullptr;
CSearchMgr*			CEngineEntry::pSearchMgr = nullptr;
CKeyMgr*			CEngineEntry::pKeyMgr = nullptr;
CCameraMgr*			CEngineEntry::pCameraMgr = nullptr;
CRenderer*			CEngineEntry::pRenderer = nullptr;
CObjContainerMgr*	CEngineEntry::pObjContainer = nullptr;
CMouseManager*		CEngineEntry::pMouseMgr = nullptr;
CCollisionMgr*		CEngineEntry::pColMgr = nullptr;
Engine::CPoolMgr*	CEngineEntry::pPoolMgr = nullptr;
CComponentMgr*		CEngineEntry::pComMgr = nullptr;
CUIMgr*				CEngineEntry::pUiMgr = nullptr;
CInventory*			CEngineEntry::pInventory = nullptr;
CCraftingMgr*		CEngineEntry::pCraftingMgr = nullptr;
CPickingMgr*		CEngineEntry::pPickMgr = nullptr;
CSoundMgr*			CEngineEntry::pSoundMgr = nullptr;
CEventMgr*			CEngineEntry::pEventMgr = nullptr;

void CEngineEntry::InitializeMgr()
{
	// DLL 싱글턴
	pGraphicDev = Ready_GraphicDev();
	pTimerMgr = Ready_TimerMgr();
	pFrameMgr = Ready_FrameMgr();
	pManagement = Ready_Manager();
	pSearchMgr = Ready_SearchMgr();
	pObjMgr = Ready_ObjMgr();
	pResourceMgr = Ready_ResourcesMgr();
	pDirectInput = Ready_InputMgr();
	pKeyMgr = Ready_KeyMgr();
	pCameraMgr = Ready_CameraMgr();
	pRenderer = Ready_Renderer();
	pObjContainer = Ready_Container();
	pMouseMgr = Ready_Mouse();
	pColMgr = Ready_Collision();
	pPoolMgr = Ready_Pool();

	pComMgr = CComponentMgr::GetInstance();
	pUiMgr = CUIMgr::GetInstance();
	pInventory = CInventory::GetInstance();
	pCraftingMgr = CCraftingMgr::GetInstance();
	pPickMgr = CPickingMgr::GetInstance();
	pSoundMgr = CSoundMgr::GetInstance();
	pEventMgr = CEventMgr::GetInstance();
	// 초기화
	//Initialize_Key();
	pPoolMgr->Initialize_Pool(POOL_END, 500);
}

void CEngineEntry::DestroyMgr()
{
	CALL_DESTROY_L(pCameraMgr);
	CALL_DESTROY_L(pKeyMgr);
	CALL_DESTROY_L(pDirectInput);
	CALL_DESTROY_L(pTimerMgr);
	CALL_DESTROY_L(pFrameMgr);
	CALL_DESTROY_L(pManagement);
	CALL_DESTROY_L(pSearchMgr);
	CALL_DESTROY_L(pMouseMgr);
	CALL_DESTROY_L(pColMgr);
	CALL_DESTROY_L(pPoolMgr);
	CALL_DESTROY_L(pColMgr);
	CALL_DESTROY_L(pUiMgr);
	CALL_DESTROY_L(pInventory);
	CALL_DESTROY_L(pComMgr);
	CALL_DESTROY_L(pCraftingMgr);
	CALL_DESTROY_L(pPickMgr);
	CALL_DESTROY_L(pSoundMgr);
	CALL_DESTROY_L(pEventMgr);

	// 장치 관리자는 항상 마지막에!
	CALL_DESTROY_L(pRenderer);
	CALL_DESTROY_L(pObjMgr);
	CALL_DESTROY_L(pResourceMgr);
	CALL_DESTROY_L(pObjContainer);
	CALL_DESTROY_L(pGraphicDev);
}

void CEngineEntry::Initialize_Key()
{

}