#ifndef EngineEntry_h__
#define EngineEntry_h__

#include "Engine_Entry.h"

#include "Mgr/DataMgr.h"
#include "Mgr/ComponentMgr.h"
#include "Mgr/PickMgr.h"
#include "Mgr/MouseMgr.h"
#include "Mgr/UIMgr.h"

#include "Mgr/SkillMgr.h"
#include "Mgr/InventoryMgr.h"
#include "Mgr/ItemMgr.h"
#include "Mgr/FontMgr.h"
#include "Mgr/QuestMgr.h"

#include "Mgr/EffectMgr.h"
#include "Mgr/SoundMgr.h"

class DLL
{
public:
	static Engine::CCameraMgr*			pCameraMgr;
	static Engine::CManagement*			pManagement;
	static Engine::CGraphicDev*			pGraphicDev;
	static Engine::CDirectInput*		pInputMgr;
	static Engine::CResourcesMgr*		pResourcesMgr;

	static Engine::CTimerMgr*			pTimerMgr;
	static Engine::CFrameMgr*			pFrameMgr;
	static Engine::CCalculateMgr*		pCalculate;
	static Engine::CRenderer*			pRenderer;
	static Engine::CObjectMgr*			pObjMgr;

	static Engine::COptimizationMgr*	pOptimizationMgr;
	static Engine::CRenderTargetMgr*	pRenderTarget;
	static Engine::CShaderMgr*			pShaderMgr;
	static Engine::CLightMgr*			pLightMgr;
	static CClientDataMgr*				pDataMgr;

	static CComponentMgr*				pComMgr;
	static CPickMgr*					pPickMgr;
	static CMouseManager*				pMouseMgr;
	static CUIMgr*						pUIMgr;
	static CSkillMgr*					pSkillMgr;
	
	static CInventoryMgr*				pInventory;
	static CItemMgr*					pItemMgr;
	static CFontMgr*					pFontMgr;
	static CQuestMgr*					pQuestMgr;
	static CEffectMgr*					pEffectMgr;

	static CSoundMgr*					pSoundMgr;

public:
	static HRESULT	Initialize_DLL(HWND hWnd, Engine::WINMODE eMode, const Engine::_uint& iSizeX, const Engine::_uint& iSizeY);
	static void		Destroy_DLL(void);

	static void		Initialize_Mouse(void);
	static void		Initialize_Renderer(LPDIRECT3DDEVICE9& pGraphicDev);
	static void		Initialize_Quests(void);

private:
	static HRESULT	get_EngineInstances(void);
	static HRESULT	get_ClientInstances(void);
	static HRESULT	get_RenderTarget(LPDIRECT3DDEVICE9& pGraphicDev);
	static HRESULT	get_MultiRenderTarget(LPDIRECT3DDEVICE9& pGraphicDev);
	static HRESULT	get_Shader(LPDIRECT3DDEVICE9& pGraphicDev);

	static void		destroy_ClientInstances(void);
};

#endif // EngineEntry_h__
