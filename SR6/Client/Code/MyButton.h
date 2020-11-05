#ifndef MyButton_h__
#define MyButton_h__

#include "GameObject.h"

class CMyButton : public Engine::CGameObject
{
private:
	explicit						CMyButton(void);
	explicit						CMyButton(const CMyButton& rhs);
	virtual							~CMyButton(void);

public:
	virtual HRESULT					Initialize_GameObject();
	Engine::_int					Update_GameObject(const Engine::_float& fTimeDelta);
	void							Render_GameObject();

	Engine::_bool					Get_Activate(void) const;

	void							Set_RenderKey(const wstring& strObjRenderKey);
	const wstring&					Get_RenderKey(void) const;

	const Engine::_bool				Get_Clicked() const { return m_bClicked; }
	void							Set_ButtonClicked() { m_bClicked = true; }
	void							Set_ButtonClickCancle() { m_bClicked = false; }

private:
	void							Setup_Btn(const Engine::_vec3* pPos, 
											const Engine::_vec3* vSize, 
											const Engine::_float& fWidth,
											const Engine::_float& fHeight);

	wstring							m_wStrObjRenderKey;
	Engine::_bool					m_bActivate = false;
	Engine::_bool					m_bClicked = false;

	Engine::_int					m_iIndex = 0;

	Engine::CTransform*				m_pTransform = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;
	RECT							m_tRc;

public:
	static CMyButton*				Create(const wstring& wStrRenderKey, 
											const Engine::_vec3* pPos, 
											const Engine::_vec3* pSize,
											const Engine::_float& fWidth,
											const Engine::_float& fHeight
	);
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos /* = nullptr */) override;

private:
	virtual void					freeMem() override;
	virtual void LoadData(HANDLE hFile) override;
};
#endif // MyButton_h__
