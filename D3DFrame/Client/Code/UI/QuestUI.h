#ifndef QuestUI_h__
#define QuestUI_h__

#include "UIBase.h"

class CButton;

class CQuestUI : public CUIBase
{
private:
	explicit	CQuestUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual		~CQuestUI(void) = default;

public:
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

	Engine::_bool			Get_Accept(void);
	void					Cancel_Accepted(void);

	void					Clear_Contents(void);
	void					Print_Contents(FONT_INFO& tFontInfo);

	void					Quest_AcceptContent(const Engine::_tchar* pContent);
	void					Quest_DenyContent(const Engine::_tchar* pContent);

private:
	void					make_Buttons(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	vector<FONT_INFO>		m_vecFontInfo;

	CButton*				m_pAcceptButton;
	CButton*				m_pDenyButton;

public:
	static CQuestUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	inline virtual void		Free(void) override;
};
#endif // QuestUI_h__
