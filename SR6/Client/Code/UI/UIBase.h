#ifndef UIBase_h__
#define UIBase_h__

#include "GameObject.h"
#include "Base.h"

class CUIBase : public CGameObject
{
protected:
	explicit				CUIBase(void);
	virtual					~CUIBase(void);

public:
	virtual void			Set_Data(const Engine::_float& fData) { m_fData = fData; }
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) PURE;
	virtual HRESULT			Late_Initialize() PURE;
	virtual void			Render_GameObject() PURE;

protected:
	Engine::CGameObject*	m_pTarget = nullptr;

	Engine::_float			m_fData = 0.f;

private:
	virtual void			freeMem(void) override;
};
#endif // UIBase_h__
