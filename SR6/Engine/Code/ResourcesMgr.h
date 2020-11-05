#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "CubeTex.h"
#include "RcCol.h"
#include "RcTex.h"
#include "TriCol.h"
#include "TerrainTex.h"
#include "Texture.h"

BEGIN(Engine)
class ENGINE_DLL CResourcesMgr : public CBase
{
	
	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit	CResourcesMgr(void);
	virtual		~CResourcesMgr(void);

public:
	HRESULT		Reserve_ContainerSize(const _ushort& wSize);

	HRESULT		Initialize_Buffer(const _ushort& wContainerIdx,
									const _tchar* pBufferTag,
									BUFFERID eID,
									const _ulong& dwCntX = 0,
									const _ulong& dwCntZ = 0,
									const _ulong& dwVtxItv = 0,
									const _tchar* pHeightFilePath = nullptr);

	HRESULT		Initialize_Texture(const _ushort& wContainerIdx,
								const _tchar* pTextureTag,
								TEXTURETYPE eType,
								const _tchar* pPath,
								const _uint& iCnt = 1);


	void		Render_Buffer	(const _ushort& wContainerIdx,
								const _tchar* pBufferTag);

	void		Render_Texture	(const _ushort& wContainerIdx,
								const _tchar* pTextureTag);

	void		SendToClient(const _ushort& wContainerIdx, const _tchar* pBufferTag, void* pVertex);
	void		ReceiveToEngine(const _ushort& wContainerIdx, const _tchar* pBufferTag, void* pVertex);

public:
	CComponent*	Clone(const _ushort& wContainerIdx,
						const _tchar* pResourceTag);

private:
	map<const _tchar*, CResources*>*			m_pMapResources = nullptr;
	_ushort										m_wSize = 0;

private:
	CResources*	find_Resources(const _ushort& wContainerIdx,
								const _tchar* pResourceTag);

	virtual void freeMem() override;
};

END

#endif // ResourcesMgr_h__
