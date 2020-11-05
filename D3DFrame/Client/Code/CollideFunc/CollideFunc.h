#ifndef CollideFunc_h__
#define CollideFunc_h__

#include "Engine_Defines.h"

BEGIN(Engine)
class CGameObject;
END

class CButton;

class CollideFunc
{
public:
	static Engine::_bool MainSphereCol(Engine::CGameObject* pFrom, Engine::CGameObject* pTo);
	static Engine::_bool ActionColToPlayer(Engine::CSphereCollider* pSphere, Engine::CGameObject* pPlayer);
	static Engine::_bool SphereToSphere(Engine::CSphereCollider* pFrom, Engine::CSphereCollider* pTo);
	static Engine::_bool SphereToMouse(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pMouseViewspace, const Engine::_vec3* pTargetPos, const Engine::_float* pRadius);
	static Engine::_bool MouseToRect(MY_RECT* pButton, const Engine::_vec2* pPos);
};

#endif // CollideFunc_h__
