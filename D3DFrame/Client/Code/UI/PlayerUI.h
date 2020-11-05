#ifndef PlayerUI_h__
#define PlayerUI_h__

#include "UIBase.h"

class CHPBar;
class CMPBar;

class CPlayerUI : public CUIBase
{
private:
	explicit						CPlayerUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CPlayerUI(void);

public:
	virtual HRESULT					Set_Target(Engine::CGameObject* pObj) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void) override;

	virtual void					Change_UI(const Engine::_tchar* pKey);

private:
	void							make_Bar(const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	CHPBar*							m_pHPBar;
	CMPBar*							m_pMPBar;

	CStatCom*						m_pTargetStat;

	Engine::_vec3					m_vLevelPos;
	Engine::_vec3					m_vLevelScale;
	Engine::_tchar					m_szLevel[32];

public:
	static CPlayerUI*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};


#endif // PlayerUI_h__
