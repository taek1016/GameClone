#ifndef HPWarning_h__
#define HPWarning_h__

#include "UIBase.h"

class CHPWarning : public CUIBase
{
private:
	explicit				CHPWarning(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CHPWarning(const CHPWarning& rhs);
	virtual					~CHPWarning(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect);

	Engine::_float			m_fAlpha;
	Engine::_bool			m_bUp;

public:
	static CHPWarning*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

#endif // HPWarning_h__
