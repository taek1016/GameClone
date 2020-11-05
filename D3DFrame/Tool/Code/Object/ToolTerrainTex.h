#ifndef ToolTerrainTex_h__
#define ToolTerrainTex_h__

#include "Engine_Defines.h"
#include "VIBuffer.h"

class CToolTerrainTex : public Engine::CVIBuffer
{
private:
	explicit		CToolTerrainTex(void);
	virtual			~CToolTerrainTex(void);

public:
	void			Set_UV(const Engine::_float& fDetail);

	Engine::_ulong	Get_VtxCntX(void) const { return m_dwCntX; }
	Engine::_ulong	Get_VtxCntZ(void) const { return m_dwCntZ; }
	Engine::_ulong	Get_VtxItv(void) const { return m_dwVtxItv; }

	Engine::VTXTEX*	Get_VtxData(void) const { return m_pLocalPos; }

	void			Change_Buffer(const Engine::VTXTEX* pVtxTex, const Engine::_ulong& dwVtxCnt);

	void			KeyInput();

	Engine::_bool	PickUp_TerrainTex(Engine::_vec3* pOut);
private:
	HRESULT			initialize_TerrainTex(const Engine::_ulong& dwCntX, const Engine::_ulong& dwCntZ, const Engine::_ulong& dwVtxItv, const Engine::_float& fDetail);
	void			set_Data(const Engine::_ulong& dwCntX, const Engine::_ulong& dwCntZ, const Engine::_ulong& dwVtxItv);

	Engine::_ulong	m_dwCntX;
	Engine::_ulong	m_dwCntZ;
	Engine::_ulong	m_dwVtxItv;
	Engine::_float	m_fDetail;

	Engine::VTXTEX*	m_pLocalPos;

public:
	static CToolTerrainTex*	Create(const Engine::_ulong& dwCntX, const Engine::_ulong& dwCntZ, const Engine::_ulong& dwVtxItv, const Engine::_float& fDetail);

private:
	virtual Engine::CComponent*	Clone(void) { return nullptr; }
	inline virtual void		Free(void);
};

#endif // ToolTerrainTex_h__
