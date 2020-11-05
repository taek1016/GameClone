#include "stdafx.h"
#include "ToolGameObject.h"

USING(Engine)

CToolGameObject::CToolGameObject(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pCollider(nullptr)
{
}

CToolGameObject::CToolGameObject(const CToolGameObject & rhs)
	: CGameObject(rhs)
	, m_pCollider(nullptr)
{
}

CToolGameObject::~CToolGameObject(void)
{
}

inline void CToolGameObject::Free(void)
{
	Engine::CGameObject::Free();

	Engine::Safe_Release(m_pCollider);
}
