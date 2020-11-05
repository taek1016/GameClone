#ifndef UICollector_h__
#define UICollector_h__

#include "UIBase.h"

class CButton;
class CSkillUI;
class CEquipUI;

class  CUICollector : public CUIBase
{
private:
	explicit						CUICollector(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CUICollector(void);

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Change_UI(const Engine::_tchar* pKey) override;

private:
	void							make_Buttons(const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	void							make_UI(const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	map<wstring, CButton*>			m_mapButtons;
	CSkillUI*						m_pSkillUI;
	CEquipUI*						m_pEquipUI;

public:
	static CUICollector*			Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // UICollector_h__
