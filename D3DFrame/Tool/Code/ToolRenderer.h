#ifndef ToolRenderer_h__
#define ToolRenderer_h__

#include "Engine_Defines.h"
#include "Base.h"

class Engine::CGameObject;
class CToolRenderer : public CBase
{
	DECLARE_SINGLETON(CToolRenderer)

private:
	explicit												CToolRenderer(void);
	virtual													~CToolRenderer(void);

public:
	void													Initialize_Renderer(LPDIRECT3DDEVICE9 pGraphicDev);
	void													Render(void);
	void													Set_RenderName(const Engine::_tchar* pKey);
	void													Set_SolidName(const Engine::_tchar* pKey);
	void													Add_RenderObj(const Engine::_tchar* pKey, Engine::CGameObject* pObj);

private:
	void													render_All(void);
	void													render_CertainName(void);
	void													render_AllCertainSolid(void);

	LPDIRECT3DDEVICE9										m_pGraphicDev;
	wstring													m_wCurRenderName;
	wstring													m_wCurSolidName;
	map<const Engine::_tchar*, list<Engine::CGameObject*>*>	m_mapRender;

private:
	inline virtual void										Free(void);
};

#endif // ToolRenderer_h__