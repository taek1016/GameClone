#include "Engine_Entry.h"


inline CGraphicDev* Ready_GraphicDev(void)
{
	return CGraphicDev::GetInstance();
}

inline CFrameMgr* Ready_FrameMgr(void)
{
	return CFrameMgr::GetInstance();
}

inline CTimerMgr* Ready_TimerMgr(void)
{
	return CTimerMgr::GetInstance();
}

inline CManagement* Ready_Manager(void)
{
	return CManagement::GetInstance();
}

inline CObjectMgr* Ready_ObjMgr(void)
{
	return CObjectMgr::GetInstance();
}

inline CCollisionMgr * Ready_CollisionMgr(void)
{
	return CCollisionMgr::GetInstance();
}

inline COptimizationMgr * Ready_Optimization(void)
{
	return COptimizationMgr::GetInstance();
}

inline CShaderMgr * Ready_Shader(void)
{
	return CShaderMgr::GetInstance();
}

inline CRenderTargetMgr * Ready_RenderTarget(void)
{
	return CRenderTargetMgr::GetInstance();
}

inline CLightMgr * Ready_Light(void)
{
	return CLightMgr::GetInstance();
}

inline CResourcesMgr* Ready_ResourcesMgr(void)
{
	return CResourcesMgr::GetInstance();
}

inline CCalculateMgr * Ready_Calculator(void)
{
	return CCalculateMgr::GetInstance();
}

inline CRenderer * Ready_Renderer(void)
{
	return CRenderer::GetInstance();
}

inline CPoolMgr*			Ready_Pool(void)
{
	return CPoolMgr::GetInstance();
}

inline CDirectInput*		Ready_Input(void)
{
	return CDirectInput::GetInstance();
}

inline CCameraMgr * Ready_Camera(void)
{
	return CCameraMgr::GetInstance();
}

inline void Clear_Engine(void)
{
	CGraphicDev::GetInstance()->DestroyInstance();
	CTimerMgr::GetInstance()->DestroyInstance();
	CFrameMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();
	CObjectMgr::GetInstance()->DestroyInstance();
	CPoolMgr::GetInstance()->DestroyInstance();
	CDirectInput::GetInstance()->DestroyInstance();
	CCameraMgr::GetInstance()->DestroyInstance();
	CResourcesMgr::GetInstance()->DestroyInstance();
	CCalculateMgr::GetInstance()->DestroyInstance();
	CRenderer::GetInstance()->DestroyInstance();
	CObjectMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	COptimizationMgr::GetInstance()->DestroyInstance();
}
