#ifndef HitBox_h__
#define HitBox_h__

#include "UIBase.h"

class CHitBox : public CUIBase
{
private:
	explicit						CHitBox(void);
	virtual							~CHitBox(void);

public:
	virtual HRESULT					Late_Initialize();
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void					Render_GameObject();

private:
	_matrix							m_matWorld;

public:
	static	CHitBox*				Create(void);

private:
	virtual void					LoadData(HANDLE hFile) override;
	virtual Engine::CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;

};

#endif // HitBox_h__
