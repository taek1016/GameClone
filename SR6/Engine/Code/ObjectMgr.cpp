#include "ObjectMgr.h"

#include "Engine_Entry.h"

USING(Engine)
IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr(void)
	: m_iMapNum(0)
	, m_iCurMap(0)
{
	m_pSearchMgr = Ready_SearchMgr();
}

CObjectMgr::~CObjectMgr(void)
{
	freeMem();
}

HRESULT CObjectMgr::SetUp_CurScene(const _int & iSceneNum)
{
	if (iSceneNum >= m_iMapNum)
	{
		return E_FAIL;
	}

	m_iCurMap = iSceneNum;
	m_pSearchMgr->Set_CurMap(m_iCurMap);

	return S_OK;
}

HRESULT CObjectMgr::SetUp_ObjectMgr(const _int& iMapNum, const _int& iObjTypes)
{
	freeMem();

	m_iMapNum = iMapNum;
	m_vMapController.resize(m_iMapNum);
	m_pSearchMgr = Ready_SearchMgr();

	for (_int i = 0; i < m_iMapNum; ++i)
	{
		m_vMapController[i] = (CObjectController::Create(iObjTypes));
	}
	
	SetUp_CurScene(0);

	return S_OK;
}

_int CObjectMgr::Update_Objects(const _float& fTimeDelta)
{
	return m_vMapController[m_iCurMap]->Update_Objects(fTimeDelta);
}

HRESULT CObjectMgr::Add_GameObject(const _int& iMapNum, const _int& iObjTag, CGameObject * pObj)
{
	if (iMapNum >= m_iMapNum)
	{
		return E_FAIL;
	}

	return m_vMapController[iMapNum]->Add_GameObject(iObjTag, pObj);
}

inline void CObjectMgr::freeMem(void)
{
	for (_int i = 0; i < m_iMapNum; ++i)
	{
		Safe_Release(m_vMapController[i]);
	}
	m_vMapController.clear();
	m_pSearchMgr = nullptr;
}