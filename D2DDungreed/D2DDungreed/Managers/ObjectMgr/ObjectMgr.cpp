#include "stdafx.h"
#include "ObjectMgr.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
	: m_objList{}
{
	AssertMember();
}


CObjectMgr::~CObjectMgr()
{
	Release();
	AssertMember();
}

HRESULT CObjectMgr::AddObject(OBJECT_TYPE eType, CGameObject* pObj)
{
	NULL_CHECK_RETURN(pObj, E_FAIL);

	m_objList[eType].push_back(pObj);

	return S_OK;
}

int CObjectMgr::Update()
{
	int iEvent = NO_EVENT;
	for (int i = 0; i < OBJECT_TYPE::OBJECT_END; ++i)
	{
		for (auto iter = m_objList[i].begin(); iter != m_objList[i].end();)
		{
			if ((*iter) == nullptr)
			{
				iter = m_objList[i].erase(iter);
				continue;
			}

			iEvent = (*iter)->Update();

			if (DEAD_OBJ == iEvent)
			{
				if (i != OBJECT_TYPE::OBJECT_PLAYER)
				{
					SafeDelete(*iter);
				}
				iter = m_objList[i].erase(iter);
				continue;
			}
			++iter;
		}
	}

	CSINGLETON::pInventory->Update();
	CSINGLETON::pPlayerUI->Update();

	return iEvent;
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < OBJECT_TYPE::OBJECT_END; ++i)
	{
		for (auto& iter : m_objList[i])
		{
			iter->LateUpdate();
		}
	}

	// 타일, 물체 충돌
	//CSINGLETON::pPhysicMgr->IntersectObjToTile(m_objList[OBJECT_TYPE::OBJECT_PLAYER], m_objList[OBJECT_TYPE::OBJECT_TERRAIN]);
	//CSINGLETON::pPhysicMgr->IntersectObjToTile(m_objList[OBJECT_TYPE::OBJECT_MONSTER], m_objList[OBJECT_TYPE::OBJECT_TERRAIN]);

	CSINGLETON::pPlayerUI->LateUpdate();
}

void CObjectMgr::Render()
{
	for (int i = 0; i < OBJECT_TYPE::OBJECT_END; ++i)
	{
		for (auto& iter : m_objList[i])
		{
			iter->Render();
		}
	}
	CSINGLETON::pInventory->Render();
	CSINGLETON::pPlayerUI->Render();
}

void CObjectMgr::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		if (i == OBJECT_TYPE::OBJECT_PLAYER)
		{
			m_objList[i].clear();
			continue;
		}
		std::for_each(m_objList[i].begin(), m_objList[i].end(), SafeDelete<CGameObject*>);
		m_objList[i].clear();
	}
}

void CObjectMgr::AssertMember()
{
#ifdef _DEBUG
	for (int i = 0; i < OBJECT_TYPE::OBJECT_END; ++i)
	{
		assert(0 == m_objList[i].size());
	}
#endif // _DEBUG
}
