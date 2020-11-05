#ifndef DealUI_h__
#define DealUI_h__

#include "UIBase.h"

class CCoinUI;
class CItemExplanationSlot;

class CDealUI : public CUIBase
{
private:
	explicit						CDealUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CDealUI(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	const Engine::_bool				Get_Activated(void) const;
	void							Activate(void);
	void							DeActivate(void);

private:
	void							make_Items(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_bool					m_bActivated;
	vector<CItemExplanationSlot*>	m_vecItemSlots;
	CCoinUI*						m_pCoinUI;

public:
	static CDealUI*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;

};

#endif // DealUI_h__
