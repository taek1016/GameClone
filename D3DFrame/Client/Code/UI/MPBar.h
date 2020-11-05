#ifndef MPBar_h__
#define MPBar_h__

#include "UIBase.h"

class CMPBar : public CUIBase
{
private:
	explicit						CMPBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual							~CMPBar(void);

public:
	virtual HRESULT					Set_Target(Engine::CGameObject* pObj);

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

	void							Calculate_MPBar(void);

private:
	virtual HRESULT					setUp_ConstantTable(LPD3DXEFFECT& pEffect) override;
	void							set_DefaultData(const Engine::_vec3* pPos, const Engine::_vec3* pScale);

	Engine::_vec3					m_vStartPos;
	Engine::_vec3					m_vMaxScale;

	CStatCom*						m_pTargetStat;
	Engine::_tchar					m_szMP[32];

public:
	static CMPBar*					Create(LPDIRECT3DDEVICE9 pGraphicDev, const Engine::_vec3* pPos, const Engine::_vec3* pScale);
	virtual Engine::CGameObject*	Clone(void) override;

private:
	inline virtual void				Free(void) override;
};

#endif // MPBar_h__
