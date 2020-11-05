#ifndef CoolTimeUI_h__
#define CoolTimeUI_h__

#include "UIBase.h"

class CCoolTimeBar;
class CSlotImage;

class CCoolTimeUI : public CUIBase
{
private:
	explicit				CCoolTimeUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CCoolTimeUI(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void					make_Bar(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_float			m_fCurTime;
	Engine::_float			m_fCurSkillCoolTime;

	Engine::_float			m_fSoundTime;
	Engine::_float			m_fSoundLifeTime;
	const Engine::_tchar*	m_pSoundName;

	Engine::_bool			m_bSound;
	Engine::_bool			m_bActivated;
	CCoolTimeBar*			m_pBar;
	CSlotImage*				m_pSlotImage;

public:
	static CCoolTimeUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
};

#endif // CoolTimeUI_h__
