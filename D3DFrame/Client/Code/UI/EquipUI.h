#ifndef EquipUI_h__
#define EquipUI_h__

#include "UIBase.h"

class CEquipBase;

class CEquipUI : public CUIBase
{
private:
	explicit				CEquipUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CEquipUI(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

	void							Activate(void);
	void							DeActivate(void);
	const Engine::_bool&			Get_Activated(void) const;

private:
	void					make_Slots(const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	vector<CEquipBase*>		m_vecEquip;
	Engine::_bool			m_bActivated;
public:
	static CEquipUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

private:
	inline virtual void		Free(void) override;
};
#endif // EquipUI_h__
