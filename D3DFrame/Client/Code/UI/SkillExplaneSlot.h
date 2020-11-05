#ifndef SkillExplaneSlot_h__
#define SkillExplaneSlot_h__

#include "UIBase.h"

class CSkillSlot;

class CSkillExplaneSlot : public CUIBase
{
private:
	explicit						CSkillExplaneSlot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CSkillExplaneSlot(void) = default;

public:
	virtual HRESULT					Initialize_UI(const Engine::_tchar* pName) override;
	virtual HRESULT					Late_InitializeUI(const Engine::_vec3* pPos, const Engine::_vec3* pScale) override;
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void							make_Slots(const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_tchar* pSkillName, const Engine::_int& iLevelLimit);

	CSkillSlot*						m_pSkillSlot;
	// Ό³ΈνΏλ
	Engine::_tchar					m_szSkillName[32];
	Engine::_tchar					m_szSkillLevelLimit[32];

public:
	static CSkillExplaneSlot*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale, const Engine::_tchar* pSkillName, const Engine::_int iLevelLimit, const Engine::_tchar* pSkillExplanation = nullptr);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // SkillExplaneSlot_h__
