#ifndef Player_h__
#define Player_h__

#include "Character.h"

class CVehicleBase;

class CPlayer : public CCharacterBase
{
private:
	explicit						CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit						CPlayer(const CPlayer& rhs);
	virtual							~CPlayer(void);

public:
	virtual HRESULT					Initialize_GameObject() override;
	virtual HRESULT					Late_Initialize() override;

	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void					Render_GameObject(void);

	const Engine::_vec3				Get_SkillHandPosition(const Engine::_bool bBoneMatrixUse = false);

	Engine::_float					Get_HPPercent(void) const;
	void							Change_Items(const EQUIP_ENUM eEquip, const Engine::_tchar* pKey);
	void							Change_Body(const Engine::_tchar* pKey);
	void							TakeOff_Item(const EQUIP_ENUM eEquip);

	void							Stun(void);
	virtual void					Hit(const Engine::_int& iDamage) override;
	Engine::_bool					Is_AnimationEnd(void) const;
	void							Play_AnimationForce(const Engine::_tchar* pKey);

	void							Ride_Target(CVehicleBase* pVehicle);
	void							DisEmbark(void);

	void							Get_Exp(const Engine::_int& iExp);
	Engine::_bool					Has_EnoughMana(const Engine::_float& fMana);

	const Engine::_int&				Get_Damage(void) const;

private:
	virtual void					read_Data(void) override;

	void							print_Unbeatable(const Engine::_float& fTimeDelta);
	void							print_LevelUp(const Engine::_float& fTimeDelta);
	void							print_Name(void);
	void							get_CameraRight(Engine::_vec3* pRight);
	void							make_VectorReady(void);

	void							key_Input(const Engine::_float& fTimeDelta);
	virtual Engine::_bool			attack_Act(void) override;

	UNIT_INFO						m_tItemInfo;
	
	wstring							m_wStrBodyName;

	vector<ITEM_INFO*>				m_vecItemEquip;
	Engine::_bool					m_bHit;
	Engine::_bool					m_bSkillUsing;
	Engine::_bool					m_bRide;
	Engine::_bool					m_bStun;

	Engine::_bool					m_bUnBeatable;
	Engine::_float					m_fUnBeatableActivateTime;

	Engine::_float					m_fCurDeadTime;
	Engine::_float					m_fDeadLifeTime;

	Engine::_float					m_fStunTime;
	Engine::_float					m_fLevelUpTime;
	Engine::_float					m_fLevelUpDeadTime = 3.f;
	Engine::_bool					m_bLevelUp;

	CVehicleBase*					m_pVehicle;

	Engine::_bool					m_bFirstUpdate;
	Engine::_vec3					m_vFirstPlacePos;

public:
	static CPlayer*					Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual Engine::CGameObject*	Clone(void);

private:
	inline virtual void				Free(void) override;
};

#endif // Player_h__
