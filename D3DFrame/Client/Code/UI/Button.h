#ifndef Button_h__
#define Button_h__

#include "GameObject.h"

class CButton : public Engine::CGameObject
{
protected:
	explicit						CButton(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CButton(const CButton& rhs);
	virtual							~CButton(void);

public:
	virtual HRESULT					Initialize_GameObject(void) override;
	virtual HRESULT					Late_Initialize(void) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;
	
	void							Print_Content(const Engine::_tchar* pContent);

	const Engine::_bool				Get_Clicked(void) const;
	void							Cancel_Clicked(void);

protected:
	void							set_MinMax(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::CTexture*				m_pTexture;
	Engine::CRcTex*					m_pBuffer;
	Engine::_int					m_iIndex;

	MY_RECT							m_tRect;
	
	Engine::_bool					m_bClicked;
	Engine::_bool					m_bCollided;

	FONT_INFO						m_tInfo;

	LPD3DXLINE						m_pLine;

	Engine::_vec2					m_vColLine[5];
	D3DXCOLOR						m_tColor[2];

	Engine::_float					m_fDebugDelta;

public:
	static CButton*					Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_tchar* pName, const Engine::_vec3* vPos, const Engine::_vec3* vScale);
	virtual Engine::CGameObject*	Clone(void) override;

protected:
	inline virtual void				Free(void) override;
};

#endif // Button_h__
