#ifndef UIBase_h__
#define UIBase_h__

#include "GameObject.h"

class CUIBase : public Engine::CGameObject
{
protected:
	explicit				CUIBase(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CUIBase(void);

public:
	virtual HRESULT			Initialize_UI(const Engine::_tchar* pName);
	virtual HRESULT			Late_InitializeUI(const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual HRESULT			Set_Target(Engine::CGameObject* pObj);

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override PURE;
	virtual void			Render_GameObject(void) override;

	virtual void			Change_UI(const Engine::_tchar* pKey);

protected:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect);

	virtual void			set_Data(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_int			m_iIndex;
	Engine::_int			m_iPass;

	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pTransform;
	Engine::CRcTex*			m_pBuffer;

	Engine::CGameObject*	m_pTarget;

	MY_RECT							m_tRect;

	Engine::_bool					m_bClicked;
	Engine::_bool					m_bCollided;

	LPD3DXLINE						m_pLine;

	Engine::_vec2					m_vColLine[5];
	D3DXCOLOR						m_tColor[2];

	Engine::CShader*				m_pShader;

protected:
	inline virtual void		Free(void) override;
};
#endif // UIBase_h__
