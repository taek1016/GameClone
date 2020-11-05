#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "Resources.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "RcTex.h"
#include "PtTex.h"
#include "Cube.h"
#include "TerrainTex.h"
#include "Texture.h"

#include "StaticMesh.h"
#include "DynamicMesh.h"

BEGIN(Engine)
class ENGINE_DLL CResourcesMgr : public CBase
{

	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit	CResourcesMgr(void);
	virtual		~CResourcesMgr(void);

public:
	HRESULT		Reserve_ContainerSize(const _ushort& wSize);

	HRESULT		Initialize_Buffer(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _ushort& wContainerIdx,
									const _tchar* pBufferTag,
									BUFFERID eID,
									const _tchar * pFilePath = nullptr);

	HRESULT		Initialize_Texture(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _ushort& wContainerIdx,
									const _tchar* pTextureTag,
									TEXTURETYPE eType,
									const _tchar* pPath,
									const _uint& iCnt = 1);

	HRESULT		Initialize_Meshes(LPDIRECT3DDEVICE9 pGraphicDev, 
									const _ushort& wContainerIdx,
									const _tchar* pMeshTag,
									MESHTYPE eType,
									const _tchar* pFilePath,
									const _tchar* pFileName);

	//void		SendToClient(const _ushort& wContainerIdx, const _tchar* pBufferTag, void* pVertex);
	//void		ReceiveToEngine(const _ushort& wContainerIdx, const _tchar* pBufferTag, void* pVertex);

public:
	//CComponent*	Clone(const _ushort& wContainerIdx,
	//					const _tchar* pResourceTag);

	template <typename T>
	T*	Clone(const _ushort& wContainerIdx,
		const _tchar* pResourceTag)
	{
		auto	iter = find_if(m_pMapResources[wContainerIdx].begin(),
			m_pMapResources[wContainerIdx].end(), CTag_Finder(pResourceTag));

		if (iter == m_pMapResources[wContainerIdx].end())
			return nullptr;

		return dynamic_cast<T*>(iter->second->Clone());
	}

private:
	map<const _tchar*, CResources*>*			m_pMapResources = nullptr;
	_ushort										m_wSize = 0;

private:
	CResources*	find_Resources(const _ushort& wContainerIdx,
		const _tchar* pResourceTag);

	virtual void				Free() override;
};

END

#endif // ResourcesMgr_h__