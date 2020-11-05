#ifndef CraftingFont_h__
#define CraftingFont_h__

#include "GameObject.h"

class CCraftFont : public Engine::CGameObject
{
private:
	explicit	CCraftFont(void);
	virtual		~CCraftFont(void);

public:
	HRESULT				Initialize_GameObject();
	Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override;
	void				Render_GameObject();

	void				Set_Failed();
	void				Set_Succeed();

private:
	Engine::_bool		m_bFailed = true;
	Engine::_bool		m_bActivate = false;
	wstring				m_wstrRenderKey;

	Engine::_float		m_fCurTime = 0.f;
	Engine::_float		m_fEndTime = 2.f;

	_vec3				m_vPos;
	_vec3				m_vScale;

	Engine::CTransform*	m_pTransform = nullptr;

public:
	static CCraftFont*	Create(void);
private:
	virtual void LoadData(HANDLE hFile) override;
	virtual CGameObject * Clone(const _vec3 * pPos = nullptr) override;
};

#endif // CraftingFont_h__
