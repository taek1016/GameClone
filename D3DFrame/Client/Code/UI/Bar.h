#ifndef Bar_h__
#define Bar_h__

#include "UIBase.h"

class CCoolTimeBar : public CUIBase
{
private:
	explicit				CCoolTimeBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CCoolTimeBar(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	void					Set_Percent(const Engine::_float& fPercent);

private:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect) override;
	void					set_Vector(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_float			m_fPercent;

public:
	static CCoolTimeBar*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // Bar_h__
