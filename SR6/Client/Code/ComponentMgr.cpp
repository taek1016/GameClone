#include "stdafx.h"
#include "ComponentMgr.h"
#include "Component/Animator.h"
#include "Transform.h"
#include "CubeTex.h"
#include "TerrainTex.h"
#include "Component/Body.h"
#include "Controller.h"
#include "GraphicDev.h"
#include "Camera.h"

USING(Engine)

IMPLEMENT_SINGLETON(CComponentMgr);

CComponentMgr::CComponentMgr()
{
}

CComponentMgr::~CComponentMgr()
{
	freeMem();
}

CComponent * CComponentMgr::CreateComponent(CGameObject * obj, COMPONENT_TYPE type)
{
	CComponent* component = nullptr;

	switch (type)
	{
	case COMPONENT_TYPE::ANIMATOR:
		component = CAnimator::Create();
		component->Attach(obj, ID_DYNAMIC);
		break;

	case COMPONENT_TYPE::BODY:
		component = CBody::Create();
		component->Attach(obj, ID_DYNAMIC);
		break;

	case COMPONENT_TYPE::COLLIDER:
		
		break;

	case COMPONENT_TYPE::CONTROLLER:
		
		break;

	case COMPONENT_TYPE::PARTICLE:
		
		break;

	case COMPONENT_TYPE::RIGIDBODY:

		break;

	case COMPONENT_TYPE::TEXTURE:

		break;

	case COMPONENT_TYPE::TRANSFORM:
		component = CTransform::Create();
		component->Attach(obj, ID_DYNAMIC);
		break;

	case COMPONENT_TYPE::BUFFER:
		component = CCubeTex::Create();
		break;

	case COMPONENT_TYPE::TERRAIN:
		component = CTerrainTex::Create(20, 20);
		component->Attach(obj, ID_DYNAMIC);
		break;

	case COMPONENT_TYPE::CAMERA:
		break;
	}
	return component;
}

void CComponentMgr::freeMem(void)
{
}