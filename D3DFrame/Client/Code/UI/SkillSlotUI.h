#ifndef SkillUI_h__
#define SkillUI_h__

#include "UIBase.h"

class CSkillSlot;

class CSkillSlotUI : public CUIBase
{
private:
	explicit						CSkillSlotUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CSkillSlotUI(void);

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Change_UI(const Engine::_tchar* pKey) override;

private:
	void							make_Buttons(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	map<wstring, CSkillSlot*>		m_mapSkillSlot;

public:
	static CSkillSlotUI*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;

};

#endif // SkillUI_h__
