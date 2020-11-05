#ifndef InfernalSummon_h__
#define InfernalSummon_h__

#include "../SummonSkillBase.h"

class CInfernalSummon : public CSummonSkillBase
{
private:
	explicit						CInfernalSummon(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CInfernalSummon(const CInfernalSummon& rhs);
	virtual							~CInfernalSummon(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void							set_InitialData(void);

	Engine::_bool					m_bInitialized;
	Engine::_float					m_fCurTime;

public:
	static CInfernalSummon*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};
#endif // InfernalSummon_h__
