#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex : public CVIBuffer
{
private:
	explicit			CTerrainTex(void);
	explicit			CTerrainTex(const CTerrainTex& rhs);
	virtual				~CTerrainTex(void);

public:
	const Engine::BasicVertex*	Get_Vtx(void) const { return m_pVertices; }
	const Engine::_ulong&		Get_TotalVtxCnt(void) const { return m_dwVtxCnt; }

	void						QuakeTerrain(_vec3 vPos, float fRange);
	void						StartQuake(_vec3 vPos, float fRange) { m_vQuakePoint = vPos; m_fQuakeTime = fRange; m_bQuake = true; }
public:
	HRESULT				Initialize_Buffer();

private:

	LPDIRECT3DTEXTURE9					m_pBaseAlphaTexture = nullptr;
	LPDIRECT3DTEXTURE9					m_pBaseTexture = nullptr;

	vector<Engine::AlphamapTexture>		m_vecTerrainTex;

	Engine::BasicVertex*				m_pVertices = nullptr;
	Engine::INDEX32*					m_pIndices = nullptr;

	int									m_iXWidth;
	int									m_iZWidth;

	_vec3								m_vQuakePoint;

	float								m_fQuakeTime = 0;

	bool								m_bQuake = false;
public:
	static CTerrainTex*	Create(const _ulong& dwCntX,
		const _ulong& dwCntZ,
		const _ulong& dwVtxItv = 1);

	virtual CResources* Clone() override;

	virtual void		Render_Buffer(LPDIRECT3DVERTEXBUFFER9 pVB = nullptr)override;

	void				SetVB(AlphamapTexture& alphaMap);

	void				LoadData(HANDLE hFile)override;

	virtual HRESULT		Attach(CGameObject* pObj, COMPONENTID com_ID);

private:
	inline virtual void freeMem(void);
};

END
#endif // TerrainTex_h__