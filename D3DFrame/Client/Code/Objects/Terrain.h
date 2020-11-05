#ifndef Terrain_h__
#define Terrain_h__

#include "GameObject.h"
#include "NaviMesh.h"

class CTerrain : public Engine::CGameObject
{
private:
	explicit						CTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CTerrain(const CTerrain& rhs);
	virtual							~CTerrain(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	void							Initialize_Terrain(const Engine::_vec3* pPos, const Engine::_vec3 * pScale, const Engine::_vec3 * pAngle, const Engine::_tchar* pKey);
	void							Add_Cell(const Engine::_vec3* pPos1, const Engine::_vec3* pPos2, const Engine::_vec3* pPos3);
	void							Link_NaviMesh(void);

	Engine::_ulong					Find_CellIndex(const Engine::_vec3* pPos);

private:
	HRESULT							setUp_ConstantTable(LPD3DXEFFECT & pEffect);

	Engine::CStaticMesh*			m_pMesh;
	Engine::CNaviMesh*				m_pNaviMesh;
	Engine::CShader*				m_pShaderCom;

public:
	static CTerrain*				Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // Terrain_h__
