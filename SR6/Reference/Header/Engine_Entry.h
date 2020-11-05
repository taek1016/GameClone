#ifndef Engine_Entry_h__
#define Engine_Entry_h__

#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"
#include "Management.h"
#include "SearchMgr.h"
#include "ObjectMgr.h"
#include "ResourcesMgr.h"
#include "DirectInput.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "Renderer.h"
#include "CObjContainerMgr.h"
#include "CollisionMgr.h"
#include "MouseMgr.h"
#include "PoolMgr.h"
//#include "ObserverMgr.h"

BEGIN(Engine)

inline CGraphicDev*			Ready_GraphicDev(void);
inline CFrameMgr*			Ready_FrameMgr(void);
inline CTimerMgr*			Ready_TimerMgr(void);
inline CManagement*			Ready_Manager(void);
inline CSearchMgr*			Ready_SearchMgr(void);
inline CObjectMgr*			Ready_ObjMgr(void);
inline CResourcesMgr*		Ready_ResourcesMgr(void);
inline CDirectInput*		Ready_InputMgr(void);
inline CKeyMgr*				Ready_KeyMgr(void);
inline CCameraMgr*			Ready_CameraMgr(void);
inline CRenderer*			Ready_Renderer(void);
inline CObjContainerMgr*	Ready_Container(void);
inline CCollisionMgr*		Ready_Collision(void);
inline CMouseManager*		Ready_Mouse(void);
inline CPoolMgr*			Ready_Pool(void);
//inline CObserverMgr*		Ready_ObserverMgr(void);

#include "Engine_Entry.inl"

END

#endif // Engine_Entry_h__