#ifndef ToolTerrain_h__
#define ToolTerrain_h__

#include "Engine_Defines.h"

class CToolNavi;
class CToolNaviCtrl;
class CToolTerrainTex;
class CToolGuideAxis;
class CTerrainTool;

class CToolTerrain : public Engine::CGameObject
{
public:
	explicit				CToolTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CToolTerrain(void);

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void			Render_GameObject(void);
	
	virtual HRESULT			Initialize_GameObject(void);
	virtual HRESULT			Late_Initialize(void) { return S_OK; }

	void					Set_TerrainTool(CTerrainTool* pTerrainTool);
	void					Make_Tex(const Engine::_ulong& dwCntX, const Engine::_ulong& dwCntZ);
	void					Make_TerrainMesh(const Engine::_tchar* pKey);
	void					Make_NaviMesh(void);
	void					Make_GuideLine(void);

	void					KeyInput(void);
	void					Change_CtrlTarget(const Engine::_tchar* pKey);
	void					Delete_Navi(const Engine::_ulong& dwIdx);

	Engine::CStaticMesh*	Get_Buffer(void) const;
	CToolGuideAxis*			Get_ActivatedAxis(void);
	CToolNavi*				Get_Navi(void);
	CToolNaviCtrl*			Get_NaviCtrl(void);
	const wstring&			Get_RenderKey(void) const;
	
private:
	HRESULT					SetUp_ConstantTable(LPD3DXEFFECT & pEffect);

	Engine::_bool			m_bTerrainCtrl;
	Engine::_bool			m_bNaviCtrlInitialized;

	Engine::CStaticMesh*	m_pMesh;
	Engine::CShader*		m_pShaderCom;

	CToolTerrainTex*		m_pTexBuffer;
	CToolNavi*				m_pNavi;
	CToolNaviCtrl*			m_pNaviCtrl;
	CTerrainTool*			m_pTerrainTool;

	wstring					m_wStrRenderKey;

public:
	static CToolTerrain*	Create(void);
	HRESULT					SaveTerrain(HANDLE hFile);
	virtual void			LoadData(HANDLE hFile);

private:
	inline virtual void		Free();
};

#endif // ToolTerrain_h__
