#include "CollisionMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr(void)
	:CBase()
{
}

CCollisionMgr::~CCollisionMgr(void)
{
	Free();
}

void CCollisionMgr::Add_ColFunc(const Engine::_tchar* pKey, _bool(ptr)(CGameObject *pFrom, CGameObject *pTo))
{
	auto iter = find_if(m_mapColFunc.begin(), m_mapColFunc.end(), CTag_Finder(pKey));

	if (m_mapColFunc.end() != iter)
	{
		return;
	}

	m_mapColFunc.emplace(pKey, ptr);
}

_bool CCollisionMgr::Collide_Each(const Engine::_tchar * pKey, CGameObject * pFrom, CGameObject * pTo)
{
	auto iter = find_if(m_mapColFunc.begin(), m_mapColFunc.end(), CTag_Finder(pKey));

	if (m_mapColFunc.end() == iter)
	{
		return false;
	}

	return iter->second(pFrom, pTo);
}

inline void CCollisionMgr::Free(void)
{
	m_mapColFunc.clear();
}
