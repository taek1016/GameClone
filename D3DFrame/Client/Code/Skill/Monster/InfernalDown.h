#ifndef InfernalDown_h__
#define InfernalDown_h__

#include "../SummonSkillBase.h"

class CInfernalDown : public CSummonSkillBase
{
private:
	explicit						CInfernalDown(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CInfernalDown(const CInfernalDown& rhs);
	virtual							~CInfernalDown(void) = default;

public:
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;

private:
	void							set_Length(void);

	Engine::_bool					m_bLengthSet;

	Engine::_float					m_fCurTime;
	Engine::_float					m_fLength;

public:
	static CInfernalDown*			Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
};

#endif // InfernalDown_h__
