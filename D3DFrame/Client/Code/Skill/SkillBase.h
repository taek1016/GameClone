#ifndef SkillBase_h__
#define SkillBase_h__

#include "GameObject.h"

class CSkillBase : public Engine::CGameObject
{
protected:
	explicit				CSkillBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CSkillBase(const CSkillBase& rhs);
	virtual					~CSkillBase(void);

public:
	virtual HRESULT				Initialize_GameObject(void) override PURE;
	virtual HRESULT				Late_Initialize(void) override PURE;
	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta) override PURE;
	virtual void				Render_GameObject(void) override PURE;

	virtual HRESULT				SetUp_ConstantTable(LPD3DXEFFECT& pEffect);
	void						Set_Dir(const Engine::_vec3* pDir);
	void						Set_Damage(const Engine::_int& iDamage);

	void						SetUp_Index(void);

protected:
	virtual void				set_Collider(void);
	virtual void				read_Data(void);
	Engine::_float				get_ReadData(const Engine::_tchar* pKey);

	Engine::_float				m_fColRadius;
	Engine::CShader*			m_pShaderCom;
	Engine::_vec3				m_vDir;
	Engine::_int				m_iDamage;
	Engine::_ulong				m_dwNaviIndex;
	Engine::CSphereCollider*	m_pCollider;
	Engine::COLLTYPE			m_eCollType;
};

#endif // SkillBase_h__
