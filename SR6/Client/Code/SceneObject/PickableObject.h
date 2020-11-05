#ifndef PickableObject_h__
#define PickableObject_h__

#include "InGameObject.h"

class CPickableObject : public CInGameObject
{
protected:
	explicit					CPickableObject();
	explicit					CPickableObject(const CPickableObject& rhs);
	
protected:
	vector<Engine::_vec3>		m_vecVertices;
	vector<Engine::_vec3>		m_vecWorldvtx;

	Engine::_matrix				m_matBill;

	Engine::_bool				m_bIsPicked = false;
public:
	void						PickUp(CGameObject* picker);
	void						Drop();

	Engine::_int				Update_GameObject(const Engine::_float& fTimeDelta)override;
	
	HRESULT						Initialize_GameObject()override;

	Engine::_bool				IsPicked(Engine::_vec3 vOrigin, Engine::_vec3 vDir, Engine::_float fMaxDistance, Engine::_float *distance);

	void						freeMem()override;
};

#endif