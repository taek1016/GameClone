#include "Search.h"

#include "GameObject.h"
#include "Transform.h"

USING(Engine)

CSearch::CSearch(void)
	: m_fNearLength(0.f)
{
}

CSearch::~CSearch(void)
{
}

CGameObject* CSearch::Get_Object(const _tchar* pObjTag)
{
	auto iter = find_if(m_mapSearch.begin(), m_mapSearch.end(), CTag_Finder(pObjTag));

	if (m_mapSearch.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

HRESULT CSearch::Add_Object(const _tchar* pObjTag, CGameObject* pObj)
{
	auto iter = find_if(m_mapSearch.begin(), m_mapSearch.end(), CTag_Finder(pObjTag));

	if (m_mapSearch.end() != iter)
	{
		return E_FAIL;
	}

	pObj->AddRef();
	m_mapSearch.emplace(make_pair(pObjTag, pObj));

	return S_OK;
}

HRESULT CSearch::Delete_Object(const _tchar* pObjTag)
{
	auto iter = find_if(m_mapSearch.begin(), m_mapSearch.end(), CTag_Finder(pObjTag));

	if (m_mapSearch.end() == iter)
	{
		return E_FAIL;
	}

	Safe_Release(iter->second);
	m_mapSearch.erase(iter);

	return S_OK;
}


CGameObject* CSearch::Get_NearList(CGameObject* pObj, list<CGameObject*>* pList, const _float fDistance)
{
	pList->clear();
	CGameObject* retVal = nullptr;
	_vec3 vMyPos = *pObj->Get_Component<CTransform>(TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);
	_vec3 vLength;
	_float fMin = 9999.f, fLength;
	for (auto iter : m_mapSearch)
	{
		if (iter.second->Get_Type() != Engine::IS_MONSTER::OBJ_MONSTER)
		{
			continue;
		}
		vLength = vMyPos - *iter.second->Get_Component<CTransform>(COMPONENT_TYPE::TRANSFORM, ID_DYNAMIC)->Get_Info(INFO_POS);

		fLength = D3DXVec3Length(&vLength);
		if (fDistance > fLength && fMin > fLength)
		{
			retVal = iter.second;
			fMin = fLength;
		}
	}
	return retVal;
}

CSearch * CSearch::Create(void)
{
	CSearch*	pInstance = new CSearch;

	return pInstance;
}

void CSearch::freeMem(void)
{
	for_each(m_mapSearch.begin(), m_mapSearch.end(), CDeleteMap());
	m_mapSearch.clear();
}