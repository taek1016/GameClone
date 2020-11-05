#ifndef TargetUI_h__
#define TargetUI_h__

#include "UIBase.h"

class CHPBar;
class CMPBar;
class CSlotImage;

class CTargetUI : public CUIBase
{
private:
	explicit						CTargetUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CTargetUI(void);

public:
	virtual HRESULT					Set_Target(Engine::CGameObject* pObj) override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void							print_TargetName(const Engine::_tchar* pName);
	Engine::_bool					is_MonsterTarget(const Engine::_tchar* pName);
	void							make_Bar(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_tchar					m_szName[64];
	CHPBar*							m_pHPBar;
	CMPBar*							m_pMPBar;
	CSlotImage*						m_pSlotImage;

public:
	static CTargetUI*				Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};


#endif // TargetUI_h__
