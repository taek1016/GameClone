#ifndef MouseMgr_h__
#define MouseMgr_h__

#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CRcTex;
END

class CMouseManager : public Engine::CGameObject
{
	DECLARE_SINGLETON(CMouseManager)

private:
	explicit				CMouseManager(void);
	virtual					~CMouseManager(void);

public:
	virtual HRESULT			Late_Initialize(void) override;
	virtual HRESULT			Initialize_GameObject(void) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	void					Late_Update(void);
	virtual void			Render_GameObject(void) override;

	void					Set_MouseMode(MOUSE_STATE eMode);
	void					Set_PickTarget(Engine::CGameObject* pPick);
	void					Set_Activate(void);
	void					Set_ItemName(const Engine::_tchar* pName);

	const Engine::_vec3*	Get_ViewportMouse(void) const;
	const Engine::_vec3*	Get_ViewspaceMouse(void) const;

	Engine::CGameObject*	Get_PickTarget(void);
	const Engine::_tchar*	Get_ItemName(void);

	void					Clear_PickTarget(void);
	void					Clear_Name(void);

private:
	void					get_MousePos(void);

	Engine::_bool			m_bActivated;

	wstring					m_wStrClickItemName;

	Engine::_vec3			m_vMouseScale;
	Engine::_vec3			m_vMouseInViewport;
	Engine::_vec3			m_vMouseInViewSpace;
	Engine::_vec3			m_vTargetScale;

	Engine::_matrix			m_matMouseWorld;
	Engine::_matrix			m_matTargetWorld;

	Engine::CTexture*		m_pMouseTexture;
	Engine::CRcTex*			m_pMouseBuffer;

	Engine::CTexture*		m_pTargetTexture;
	Engine::CRcTex*			m_pTargetBuffer;

	Engine::CGameObject*	m_pPickTarget;
	
	MOUSE_STATE				m_eCurMouseState;

	Engine::_bool			m_bClicked;
	Engine::_float			m_fClickCool;

private:
	inline virtual void		Free(void) override;
};

#endif // MouseMgr_h__
