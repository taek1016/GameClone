#ifndef Barricade_h__
#define Barricade_h__

#include "PickableObject.h"

class CBarricade : public CPickableObject
{
	explicit CBarricade();
	explicit CBarricade(const CBarricade& rhs);

	Engine::_float			m_fGatherTime = 0.f;
	Engine::_float			m_fDieTime = 2.f;

	Engine::CCollider*		m_pPlayerCol = nullptr;
	Engine::CCollider*		m_pMyCol = nullptr;

public:
	

public:
	Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta)override;

	void	Render_GameObject()override;

	HRESULT Initialize_GameObject()override;

	HRESULT Late_Initialize()override;

	bool	IsPicked();

	virtual CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;

	static CBarricade* Create();

	void freeMem()override;
};

#endif