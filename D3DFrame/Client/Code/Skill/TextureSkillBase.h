#ifndef TextureSkillBase_h__
#define TextureSkillBase_h__

#include "SkillBase.h"

class CTextureSkillBase : public CSkillBase
{
protected:
	explicit					CTextureSkillBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit					CTextureSkillBase(const CTextureSkillBase& rhs);
	virtual						~CTextureSkillBase(void) = default;

public:
	virtual HRESULT				Initialize_GameObject(void) override;
	virtual HRESULT				Late_Initialize(void) override;
	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void				Render_GameObject(void) override;

protected:
	virtual void				check_TextureIndex(const Engine::_float& fTimeDelta) PURE;
	virtual void				dead_Action(const Engine::_float& fTimeDelta) PURE;
	virtual void				act_Determine(const Engine::_float& fTimeDelta) PURE;
	void						set_Index(const Engine::_float& fMaxIndex);
	virtual HRESULT				setUp_ConstantTable(LPD3DXEFFECT& pEffect);

	Engine::_bool				m_bDead;
	
	Engine::_float				m_fCurDeltaTime;
	Engine::_float				m_fCurIndex;
	Engine::_float				m_fMaxSize;

	Engine::_vec3				m_vScale;

	Engine::CTexture*			m_pTexture;
	Engine::CVIBuffer*			m_pBuffer;

	Engine::CSphereCollider*	m_pCollider;
	Engine::COLLTYPE			m_eCollType;
};

#endif // TextureSkillBase_h__
