#ifndef EngineEntry_h__
#define EngineEntry_h__

#include "Engine_Entry.h"

#include "ToolObjMgr.h"
#include "ToolContainerMgr.h"
#include "ToolRenderer.h"
#include "DataMgr.h"

class DLL
{
public:
	static Engine::CCameraMgr*			pCameraMgr;
	static Engine::CManagement*			pManagementMgr;
	static Engine::CGraphicDev*			pGraphicDev;
	static Engine::CDirectInput*		pInputMgr;
	static Engine::CResourcesMgr*		pResourcesMgr;
	static Engine::CTimerMgr*			pTimerMgr;
	static Engine::CFrameMgr*			pFrameMgr;
	static Engine::CCalculateMgr*		pCalculate;
	static Engine::CRenderTargetMgr*	pRenderTarget;
	static Engine::CShaderMgr*			pShaderMgr;
	static Engine::CLightMgr*			pLightMgr;

	static CToolObjMgr*				pObjMgr;
	static CToolContainer*			pToolContainer;
	static CToolRenderer*			pToolRenderer;
	static CDataMgr*				pDataMgr;

public:
	static HRESULT	Initialize_DLL(HWND hWnd, Engine::WINMODE eMode, const Engine::_uint& iSizeX, const Engine::_uint& iSizeY);
	static void		Destroy_DLL(void);
	static void		Intialize_Renderer(LPDIRECT3DDEVICE9& pGraphicDev);

private:
	static HRESULT	Get_Instances(void);
	static HRESULT	get_Shader(LPDIRECT3DDEVICE9 & pGraphicDev);
	static HRESULT	get_MultiRenderTarget(LPDIRECT3DDEVICE9 & pGraphicDev);
	static HRESULT	get_RenderTarget(LPDIRECT3DDEVICE9 & pGraphicDev);

};

#endif // EngineEntry_h__
