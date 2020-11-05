#ifndef MeshEffectBase_h__
#define MeshEffectBase_h__

#include "EffectBase.h"

class CMeshEffectBase : public CEffectBase
{
protected:
	explicit				CMeshEffectBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CMeshEffectBase(const CMeshEffectBase& rhs);
	virtual					~CMeshEffectBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

	void					Set_Target(Engine::CGameObject* pTarget);

protected:
	void					read_Data(void);
	Engine::_float			get_ReadData(const Engine::_tchar* pKey);

	virtual HRESULT			setUp_ConstantTable(LPD3DXEFFECT& pEffect);
	virtual void			act_Determine(const Engine::_float& fTimeDelta) PURE;

	Engine::CDynamicMesh*	m_pMesh;
	Engine::CShader*		m_pShader;

	Engine::CGameObject*	m_pTarget;
	Engine::CTransform*		m_pTargetTransform;

	Engine::_bool			m_bDead;
};

#endif // MeshEffectBase_h__