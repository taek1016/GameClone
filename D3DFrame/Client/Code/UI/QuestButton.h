#ifndef QuestButton_h__
#define QuestButton_h__

#include "Button.h"

class CQuestButton : public CButton
{
private:
	explicit				CQuestButton(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CQuestButton(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

	void					Print_AcceptContent(const FONT_INFO& tInfo);

private:
	FONT_INFO				m_tFontInfo;

public:
	static CQuestButton*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);

};

#endif // QuestButton_h__
