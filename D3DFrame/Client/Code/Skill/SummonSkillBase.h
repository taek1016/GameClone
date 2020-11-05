#ifndef SummonSkillBase_h__
#define SummonSkillBase_h__

#include "SkillBase.h"

class CSummonSkillBase : public CSkillBase
{
protected:
	explicit					CSummonSkillBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CSummonSkillBase(const CSummonSkillBase& rhs);
	virtual						~CSummonSkillBase(void) = default;

public:
	virtual HRESULT				Initialize_GameObject(void) override;
	virtual HRESULT				Late_Initialize(void) override;
	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override PURE;
	virtual void				Render_GameObject(void) override;

protected:
	Engine::CDynamicMesh*		m_pMesh;

	list<Engine::CGameObject*>	m_listSummonObj;

protected:
	inline virtual void			Free(void) override;
};

#endif // SummonSkillBase_h__
