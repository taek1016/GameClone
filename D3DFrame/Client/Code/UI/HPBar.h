#ifndef HPBar_h__
#define HPBar_h__

#include "UIBase.h"

class CHPBar : public CUIBase
{
private:
	explicit						CHPBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CHPBar(void);

public:
	virtual HRESULT					Set_Target(Engine::CGameObject* pObj);

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

	void							Calculate_HPBar(void);

private:
	virtual HRESULT					setUp_ConstantTable(LPD3DXEFFECT& pEffect) override;
	void							set_DefaultData(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_vec3					m_vStartPos;
	Engine::_vec3					m_vMaxScale;

	CStatCom*						m_pTargetStat;
	Engine::_tchar					m_szHP[32];

public:
	static CHPBar*					Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // HPBar_h__
