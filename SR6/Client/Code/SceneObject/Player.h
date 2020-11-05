#ifndef Player_h__
#define Player_h__

#include "InGameObject.h"

class CPickableObject;
class CPlayer : public CInGameObject
{
private:
	explicit	CPlayer(void);
	explicit	CPlayer(const CPlayer& rhs);
	virtual		~CPlayer(void);

public:
	virtual HRESULT				Late_Initialize(void);
	virtual HRESULT				Initialize_GameObject(void);
	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void				Render_GameObject(void);

	virtual void				Attack(const Engine::_float& fTimeDelta);
	virtual void				Take_Damage(const _float& fDamage);

	void						Set_PickableObj(CPickableObject* pObj);

	void						AirBorne();

private:
	virtual void				LoadData(HANDLE hFile) override;
	HRESULT						Create_Component(void);

	Engine::_int				m_iHp;
	Engine::_int				m_iMaxHp;

	CPickableObject*			m_pPickedObj = nullptr;

public:
	static CPlayer*				Create(void);
	inline virtual CInGameObject* Clone(const Engine::_vec3* pPos = nullptr);

private:
	inline virtual void			freeMem();
};

#endif // Player_h__
