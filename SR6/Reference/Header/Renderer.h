#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Defines.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer : public CComponent
{
	DECLARE_SINGLETON(CRenderer)

private:
	explicit				CRenderer(void) = default;
	virtual					~CRenderer(void);

public:
	void					Set_GraphicDev(LPDIRECT3DDEVICE9 pGraphicDev) { m_pGraphicDev = pGraphicDev; }
	void					Set_Window(const _float& fWidth, const _float& fHeight) { m_fWidth = fWidth; m_fHeight = fHeight; }

	virtual HRESULT			Late_Initialize();
	void					Add_RenderGroup(RENDERID eGroup, CGameObject* pGameObject);
	void					Render_GameObject(void);
	void					Clear_RenderGroup(void);

private:
	void					Ready_Priority(void);
	void					End_Priority(void);

	void					Ready_UI(void);
	void					End_UI(void);

	void					Ready_Alpha(void);
	void					End_Alpha(void);

	_float					m_fWidth = 0.f;
	_float					m_fHeight = 0.f;

	list<CGameObject*>		m_RenderGroup[RENDER_END];

	LPDIRECT3DDEVICE9		m_pGraphicDev = nullptr;

private:
	virtual void			freeMem(void);

};

END

#endif // Renderer_h__
