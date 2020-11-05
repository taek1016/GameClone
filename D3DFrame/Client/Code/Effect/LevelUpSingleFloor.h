#ifndef LevelUpSingleFloor_h__
#define LevelUpSingleFloor_h__


#include "EffectBase.h"

class CLevelUpSingleFloor : public CEffectBase
{
private:
	explicit				CLevelUpSingleFloor(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CLevelUpSingleFloor(const CLevelUpSingleFloor& rhs);
	virtual					~CLevelUpSingleFloor(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

	void					Clone_YellowParticle(void);

	void					Move_Particle(Engine::CGameObject* pTarget, const Engine::_float& fTimeDelta);
	virtual void			Ready_ToGo(void) override;

protected:
	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect) override;

	class CLeftSide*		m_pLeft;
	class CRightSide*		m_pRight;

	Engine::_vec3			m_vUp;

	Engine::_float			m_fAngle;
	Engine::_float			m_fCurTime;
	Engine::_float			m_fDeleteTime;

public:
	static CLevelUpSingleFloor*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void) override;
	
private:
	inline virtual void		Free(void) override;
};

#endif // LevelUpSingleFloor_h__
