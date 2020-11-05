#include "ObjectController.h"
#include "GameObject.h"

#include "Engine_Entry.h"
#include "SearchMgr.h"
#include "GameObject.h"

USING(Engine)

CObjectController::CObjectController(const _int & iObjTypeNum)
	: m_iMaxObjTypeNum(iObjTypeNum)
{
	m_vecObjList.resize(m_iMaxObjTypeNum);
	m_pSearchMgr = Ready_SearchMgr();
	m_pColMgr = Ready_Collision();
}

CObjectController::~CObjectController(void)
{
}

_int CObjectController::Update_Objects(const _float & fTimeDelta)
{
	_int iExit = 0;

	for (_int i = 0; i < m_iMaxObjTypeNum; ++i)
	{
		if (m_vecObjList[i].empty())
		{
			continue;
		}

		for (auto iter = m_vecObjList[i].begin(); iter != m_vecObjList[i].end();)
		{
			iExit = (*iter)->Update_GameObject(fTimeDelta);

			if (iExit & 0x80000000)
			{
				return -1;
			}

			if (DEAD_OBJ == iExit)
			{
				m_pSearchMgr->Delete_Object((*iter)->Get_Name());
				m_pColMgr->Delete_Obj((*iter)->Get_Name());
				Safe_Release(*iter);
				iter = m_vecObjList[i].erase(iter);
			}
			else if (BACK_POOL == iExit)
			{
				iter = m_vecObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	return iExit;
}

HRESULT CObjectController::Add_GameObject(const _int iObjType, CGameObject * pObj)
{
	if (iObjType >= m_iMaxObjTypeNum)
	{
		return E_FAIL;
	}

	m_vecObjList[iObjType].push_back(pObj);

	return S_OK;
}

CObjectController* CObjectController::Create(const _int& iObjTypeNum)
{
	return new CObjectController(iObjTypeNum);
}

inline void CObjectController::freeMem(void)
{
	for (auto iterList : m_vecObjList)
	{
		for (auto iter : iterList)
		{
			Safe_Release(iter);
		}
		iterList.clear();
	}
	m_vecObjList.clear();
}
