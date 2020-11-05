#ifndef Character_h__
#define Character_h__

#include "GameObject.h"
#include "ActionComponent.h"

class CCharacterBase : public Engine::CGameObject
{
protected:
	explicit												CCharacterBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit												CCharacterBase(const CCharacterBase& rhs);
	virtual													~CCharacterBase(void);

public:
	virtual HRESULT											Initialize_GameObject() override PURE;
	virtual HRESULT											Late_Initialize() override;

	virtual Engine::_int									Update_GameObject(const Engine::_float& fTimeDelta) override PURE;
	virtual void											Render_GameObject(void) override;

	void													Add_AnimationKey(const Engine::_tchar* pKey, const Engine::_int& iIdx);

	virtual void											Set_AnimationSet(const Engine::_tchar* pKey);
	void													Set_SphereColName(const Engine::_tchar* pName);
	void													Add_Action(const Engine::_tchar* pName, const Engine::_float& fCoolTime, const Engine::_float& fRadius);

	void													Set_Position(const Engine::_vec3* pPos);
	void													Add_MainCollider(const Engine::_float& fRadius);

	virtual void											Hit(const Engine::_int& iDamage);
	Engine::_bool											Is_Dead(void) const;

protected:
	void													make_PosToView(Engine::_vec4* pPos, const Engine::_float& fMoveX, const Engine::_float& fMoveY);

	virtual void											read_Data(void);
	virtual Engine::_float									get_ReadData(const Engine::_tchar* pKey);

	virtual void											play_Animation(void);
	virtual void											is_AnimationEnd(void) { ; }
	virtual HRESULT											setUp_ConstantTable(LPD3DXEFFECT& pEffect);
	virtual void											initialize_Bones(void) { };
	void													initialize_Animation(void);

	void													reset_ActCol(void);

	// 애니메이션 함수들
	virtual void											set_MoveAnimation(void);
	virtual void											set_DeadAnimation(void);
	virtual void											set_AttackAnimation(void);

	void													add_BoneNames(const Engine::_tchar* pName, const Engine::_tchar* pBoneName);
	void													set_PreAnimationKey(void);

	Engine::_int											m_iCurAnimationIdx;
	Engine::_int											m_iPreAnimationIdx;

	Engine::CSphereCollider*								m_pMainSphereCollider;
	Engine::CSphereCollider*								m_pActionCol;
	string													m_strColName;

	Engine::COLLTYPE										m_eSphereCol;

	Engine::CDynamicMesh*									m_pMesh;
	map<wstring, const Engine::_int>						m_mapAnimationIndexMap;

	CStatCom*												m_pStatCom;
	Engine::CShader*										m_pShaderCom;

	map<wstring, Engine::CActionCom*>						m_mapAction;
	map<wstring, Engine::COLLTYPE>							m_mapActColType;

	Engine::_ulong											m_dwNaviIdx;
	
	map<wstring, wstring>									m_mapBone;
	list<pair<Engine::CSphereCollider*, Engine::_bool>>		m_listAttackCol;

	Engine::_float											m_fMainColSize;
	Engine::_vec3											m_vStringPos;
	Engine::_float											m_fHeight;

	Engine::_tchar											m_szHitDamage[64];

protected:
	inline virtual void										Free(void);
};

#endif // Character_h__