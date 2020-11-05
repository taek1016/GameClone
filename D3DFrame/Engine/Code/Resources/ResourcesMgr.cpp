#include "ResourcesMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CResourcesMgr)

CResourcesMgr::CResourcesMgr(void)
{
}

CResourcesMgr::~CResourcesMgr(void)
{
	Free();
}

HRESULT CResourcesMgr::Reserve_ContainerSize(const _ushort & wSize)
{
	if (nullptr != m_pMapResources)
	{
		MSG_BOX("ResourcesMgr Reserve_Container Failed");
		return E_FAIL;
	}

	m_pMapResources = new map<const _tchar*, CResources*>[wSize];

	m_wSize = wSize;

	return S_OK;
}

HRESULT CResourcesMgr::Initialize_Buffer(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort & wContainerIdx, const _tchar * pBufferTag, BUFFERID eID, const _tchar * pFilePath)
{
	NULL_CHECK_RETURN(m_pMapResources, E_FAIL);

	CResources*	pResources = find_Resources(wContainerIdx, pBufferTag);

	if (nullptr != pResources)
		return E_FAIL;

	switch (eID)
	{
	case BUFFER_TRICOL:
		pResources = CTriCol::Create(pGraphicDev);
		break;

	case BUFFER_RCCOL:
		pResources = CRcCol::Create(pGraphicDev);
		break;

	case BUFFER_RCTEX:
		pResources = CRcTex::Create(pGraphicDev);
		break;

	case BUFFER_TERRAINTEX:
		pResources = CTerrainTex::Create(pGraphicDev, pFilePath);
		break;

	case BUFFER_CUBETEX:
		pResources = CCubeTex::Create(pGraphicDev);
		break;
	}
	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_pMapResources[wContainerIdx].emplace(pBufferTag, pResources);

	return S_OK;
}

HRESULT CResourcesMgr::Initialize_Texture(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort & wContainerIdx, const _tchar * pTextureTag, TEXTURETYPE eType, const _tchar * pPath, const _uint & iCnt)
{
	NULL_CHECK_RETURN(m_pMapResources, E_FAIL);

	CResources*	pResources = find_Resources(wContainerIdx, pTextureTag);

	if (nullptr != pResources)
		return E_FAIL;

	pResources = CTexture::Create(pGraphicDev, pPath, eType, iCnt);

	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_pMapResources[wContainerIdx].emplace(pTextureTag, pResources);

	return S_OK;
}

HRESULT CResourcesMgr::Initialize_Meshes(LPDIRECT3DDEVICE9 pGraphicDev, const _ushort & wContainerIdx, const _tchar * pMeshTag, MESHTYPE eType, const _tchar * pFilePath, const _tchar * pFileName)
{
	NULL_CHECK_RETURN(m_pMapResources, E_FAIL);

	CResources*	pResources = find_Resources(wContainerIdx, pMeshTag);

	if (nullptr != pResources)
		return E_FAIL;

	switch (eType)
	{
	case TYPE_STATIC:
		pResources = CStaticMesh::Create(pGraphicDev, pFilePath, pFileName);
		break;

	case TYPE_DYNAMIC:
		pResources = CDynamicMesh::Create(pGraphicDev, pFilePath, pFileName);
		break;
	}

	NULL_CHECK_RETURN(pResources, E_FAIL);

	m_pMapResources[wContainerIdx].emplace(pMeshTag, pResources);

	return S_OK;
}

//CComponent * CResourcesMgr::Clone(const _ushort & wContainerIdx, const _tchar * pResourceTag)
//{
//	auto	iter = find_if(m_pMapResources[wContainerIdx].begin(),
//		m_pMapResources[wContainerIdx].end(), CTag_Finder(pResourceTag));
//
//	if (iter == m_pMapResources[wContainerIdx].end())
//		return nullptr;
//
//	return iter->second->Clone();
//}

//void CResourcesMgr::SendToClient(const _ushort & wContainerIdx, const _tchar * pBufferTag, void * pVertex)
//{
//	auto	iter = find_if(m_pMapResources[wContainerIdx].begin(),
//		m_pMapResources[wContainerIdx].end(), CTag_Finder(pBufferTag));
//
//	if (iter == m_pMapResources[wContainerIdx].end())
//		return;
//
//	dynamic_cast<CVIBuffer*>(iter->second)->SendToClient(pVertex);
//}
//
//void CResourcesMgr::ReceiveToEngine(const _ushort & wContainerIdx, const _tchar * pBufferTag, void * pVertex)
//{
//	auto	iter = find_if(m_pMapResources[wContainerIdx].begin(),
//		m_pMapResources[wContainerIdx].end(), CTag_Finder(pBufferTag));
//
//	if (iter == m_pMapResources[wContainerIdx].end())
//		return;
//
//	//dynamic_cast<CVIBuffer*>(iter->second)->ReceiveToEngine(pVertex);
//}

CResources* CResourcesMgr::find_Resources(const _ushort & wContainerIdx, const _tchar * pResourceTag)
{
	auto	iter = find_if(m_pMapResources[wContainerIdx].begin(),
		m_pMapResources[wContainerIdx].end(), CTag_Finder(pResourceTag));

	if (iter == m_pMapResources[wContainerIdx].end())
		return nullptr;

	return iter->second;
}

void CResourcesMgr::Free()
{
	for (_ushort i = 0; i < m_wSize; ++i)
	{
		for_each(m_pMapResources[i].begin(), m_pMapResources[i].end(), CDeleteMap());
		m_pMapResources[i].clear();
	}

	Safe_Delete_Array(m_pMapResources);
}