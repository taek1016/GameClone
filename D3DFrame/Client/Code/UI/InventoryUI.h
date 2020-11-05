#ifndef InventoryUI_h__
#define InventoryUI_h__

#include "UIBase.h"

class CInventorySlot;

class CInventoryUI : public CUIBase
{
private:
	explicit				CInventoryUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CInventoryUI(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void					set_Buttons(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	vector<CInventorySlot*>	m_vecSlots;

public:
	static CInventoryUI*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

private:
	inline virtual void		Free(void) override;
};

#endif // InventoryUI_h__
