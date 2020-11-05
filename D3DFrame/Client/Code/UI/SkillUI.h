#ifndef SkillUI_h__
#define SkillUI_h__

#include "UIBase.h"

class CSkillExplaneSlot;

class CSkillUI : public CUIBase
{
private:
	explicit						CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CSkillUI(void);

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

	void							Activate(void);
	void							DeActivate(void);
	const Engine::_bool&			Get_Activated(void) const;

private:
	void							make_Slots(const map<const Engine::_tchar*, const Engine::_int>* pMapSKillName, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_bool					m_bActivated;
	vector<CSkillExplaneSlot*>		m_vecSkillSlots;

public:
	static CSkillUI*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const map<const Engine::_tchar*, const Engine::_int>* pMapSKillName, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // SkillUI_h__
