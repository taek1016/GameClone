#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit			CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit			CTerrainTex(const CTerrainTex& rhs);
	virtual				~CTerrainTex(void);

public:
	const _vec3*		Get_VtxPos(void) const	{ return m_pPos; }
	_ulong				Get_VtxCntX(void) const { return m_dwCntX; }
	_ulong				Get_VtxCntZ(void) const { return m_dwCntZ; }

	HRESULT				Initialize_Buffer(void);

private:
	void				set_Data(const _ulong& dwCntX, const _ulong& dwCntZ, const _ulong& dwVtxItv);

	BITMAPFILEHEADER	m_fH;
	BITMAPINFOHEADER	m_iH;

	_vec3*				m_pPos;
	_bool				m_bClone;

	_ulong				m_dwCntX;
	_ulong				m_dwCntZ;
	_ulong				m_dwVtxItv;

public:
	static CTerrainTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* pFilePath);


	virtual CResources*		Clone(void) override;

private:
	void					LoadFile(const _tchar* pFilePath, _ulong** ppPixel);
	virtual void			Free(void);
};

END
#endif // TerrainTex_h__
