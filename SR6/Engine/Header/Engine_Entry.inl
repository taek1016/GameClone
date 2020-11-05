#include "Engine_Entry.h"

USING(Engine)
CGraphicDev*			Ready_GraphicDev(void)
{
	return CGraphicDev::GetInstance();
}

CFrameMgr*				Ready_FrameMgr(void)
{
	return CFrameMgr::GetInstance();
}

CTimerMgr*				Ready_TimerMgr(void)
{
	return CTimerMgr::GetInstance();
}

CManagement*			Ready_Manager(void)
{
	return CManagement::GetInstance();
}

CSearchMgr*				Ready_SearchMgr(void)
{
	return CSearchMgr::GetInstance();
}

CObjectMgr*				Ready_ObjMgr(void)
{
	return CObjectMgr::GetInstance();
}

CResourcesMgr*			Ready_ResourcesMgr(void)
{
	return CResourcesMgr::GetInstance();
}

CDirectInput*			Ready_InputMgr(void)
{
	return CDirectInput::GetInstance();
}

CKeyMgr*				Ready_KeyMgr(void)
{
	return CKeyMgr::GetInstance();
}

CCameraMgr*			Ready_CameraMgr(void)
{
	return CCameraMgr::GetInstance();
}

CRenderer*			Ready_Renderer(void)
{
	return CRenderer::GetInstance();
}

CObjContainerMgr*	Ready_Container(void)
{
	return CObjContainerMgr::GetInstance();
}

CCollisionMgr*		Ready_Collision(void)
{
	return CCollisionMgr::GetInstance();
}

CMouseManager*		Ready_Mouse(void)
{
	return CMouseManager::GetInstance();
}

CPoolMgr*			Ready_Pool(void)
{
	return CPoolMgr::GetInstance();
}

//CObserverMgr*			Ready_ObserverMgr(void)
//{
//	return CObserverMgr::GetInstance();
//}