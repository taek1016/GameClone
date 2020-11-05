#ifndef Engine_Entry_h__
#define Engine_Entry_h__

#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"
#include "Management.h"
#include "ObjectMgr.h"
#include "ObjPool.h"
#include "DirectKeyMgr.h"
#include "CameraMgr.h"
#include "ResourcesMgr.h"
#include "CalculateMgr.h"
#include "Renderer.h"
#include "CollisionMgr.h"
#include "Optimization.h"

#include "ShaderMgr.h"
#include "LightMgr.h"
#include "RenderTargetMgr.h"

BEGIN(Engine)

inline CGraphicDev*			Ready_GraphicDev(void);
inline CTimerMgr*			Ready_TimerMgr(void);
inline CFrameMgr*			Ready_FrameMgr(void);
inline CManagement*			Ready_Manager(void);
inline CObjectMgr*			Ready_ObjMgr(void);
inline CPoolMgr*			Ready_Pool(void);
inline CDirectInput*		Ready_Input(void);
inline CCameraMgr*			Ready_Camera(void);
inline CResourcesMgr*		Ready_ResourcesMgr(void);
inline CCalculateMgr*		Ready_Calculator(void);
inline CRenderer*			Ready_Renderer(void);
inline CCollisionMgr*		Ready_CollisionMgr(void);
inline COptimizationMgr*	Ready_Optimization(void);

inline CShaderMgr*			Ready_Shader(void);
inline CRenderTargetMgr*	Ready_RenderTarget(void);
inline CLightMgr*			Ready_Light(void);

inline void					Clear_Engine(void);

#include "Engine_Entry.inl"
END

#endif // Engine_Entry_h__
