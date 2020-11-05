#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)

class CRenderTargetMgr;
class CLightMgr;
class CGameObject;
class CShaderMgr;

class ENGINE_DLL CRenderer : public CBase 
{
	DECLARE_SINGLETON(CRenderer)

private: 
	explicit				CRenderer(void);
	virtual					~CRenderer(void);

public:
	HRESULT					Initialize_Renderer(CRenderTargetMgr* pRenderTargetMgr, CLightMgr* pLightMgr, CShaderMgr* pShaderMgr, LPDIRECT3DDEVICE9 & pGraphicDev);

	void					Set_Window(const _float& fWidth, const _float& fHeight) { m_fWidth = fWidth; m_fHeight = fHeight; }

	void					Add_RenderGroup(RENDERID eGroup, CGameObject* pGameObject);
	void					Render_GameObject(const _bool& bRenderDebug, LPDIRECT3DDEVICE9& pGraphicDev);
	void					Clear_RenderGroup(void);

private:
	//void					ready_Priority(void);
	//void					end_Priority(void);

	//void					ready_UI(void);
	//void					end_UI(void);

	//void					ready_Alpha(void);
	//void					end_Alpha(void);

	void					render_Priority(LPDIRECT3DDEVICE9& pGraphicDev);
	void					render_PreUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void					render_NonAlpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void					render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void					render_UI(LPDIRECT3DDEVICE9& pGraphicDev);

	void					render_Defferd(LPDIRECT3DDEVICE9& pGraphicDev);
	void					render_LightAcc(LPDIRECT3DDEVICE9& pGraphicDev);

	void					render_Blend(LPDIRECT3DDEVICE9& pGraphicDev);

	_float					m_fWidth = 0.f;
	_float					m_fHeight = 0.f;

	list<CGameObject*>		m_RenderGroup[RENDER_END];

	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;

	CRenderTargetMgr*		m_pRenderTargetMgr;
	CLightMgr*				m_pLightMgr;
	CShaderMgr*				m_pShaderMgr;

private:
	virtual void			Free(void);
};
END

#endif // Renderer_h__
