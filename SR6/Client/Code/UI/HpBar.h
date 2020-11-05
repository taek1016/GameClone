#ifndef HpBar_h__
#define HpBar_h__

#include "GameObject.h"
#include "UIBase.h"

class CHpBar : public CUIBase
{
private:
	explicit						CHpBar();
	virtual							~CHpBar();

public:
	virtual HRESULT					Late_Initialize();
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void					Render_GameObject();

private:
	_matrix							m_matBaseWorld;

	_matrix							m_matBarTranslate;
	_matrix							m_matBarScale;

	_vec3							m_vScale;
	_vec3							m_vPos;

public:
	static	CHpBar*					Create(void);
	virtual void					LoadData(HANDLE hFile) override;
	virtual Engine::CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;
};

#endif // HpBar_h__
