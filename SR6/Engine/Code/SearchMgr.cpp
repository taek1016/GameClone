#include "SearchMgr.h"

#include "System/Search.h"
#include "Engine_Entry.h"
#include "GameObject.h"
#include "Transform.h"
#include "ObjectMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSearchMgr)

CSearchMgr::CSearchMgr(void)
	: m_iVecMaxIdx(0)
{
}

CSearchMgr::~CSearchMgr(void)
{
	freeMem();
}

HRESULT CSearchMgr::Set_CurMap(const _int & iCurMap)
{
	if (iCurMap >= m_iVecMaxIdx)
	{
		return E_FAIL;
	}

	m_iCurMap = iCurMap;
	m_pObjMgr = Ready_ObjMgr();

	return S_OK;
}

const _vec3 * CSearchMgr::Get_Pos(const _tchar * pTag)
{
	return m_vecSearch[m_iCurMap]->Get_Object(pTag)->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
}

HRESULT CSearchMgr::Initialize_SearchMgr(const _int& iSearchMgrSize)
{
	freeMem();

	m_iVecMaxIdx = iSearchMgrSize;
	m_vecSearch.resize(m_iVecMaxIdx);

	m_iCurMap = 0;
	m_pObjMgr = Ready_ObjMgr();

	for (_int i = 0; i < m_iVecMaxIdx; ++i)
	{
		m_vecSearch[i] = CSearch::Create();
	}

	return S_OK;
}

CGameObject* CSearchMgr::Get_Object(const _tchar* pObjTag)
{
	return m_vecSearch[m_iCurMap]->Get_Object(pObjTag);
}

HRESULT CSearchMgr::Add_Object(const _tchar* pObjTag, CGameObject* pObj)
{
	return m_vecSearch[m_iCurMap]->Add_Object(pObjTag, pObj);
}

HRESULT CSearchMgr::Delete_Object(const _tchar* pObjTag)
{
	return m_vecSearch[m_iCurMap]->Delete_Object(pObjTag);
}

CGameObject* CSearchMgr::Find_NearObj(CGameObject* pObj, list<CGameObject*>* pList, const _float fDistance)
{
	return m_vecSearch[m_iCurMap]->Get_NearList(pObj, pList, fDistance);
}

void CSearchMgr::freeMem(void)
{
	for_each(m_vecSearch.begin(), m_vecSearch.end(), CDeleteObj());
	
	m_vecSearch.clear();

	m_pObjMgr = nullptr;
}