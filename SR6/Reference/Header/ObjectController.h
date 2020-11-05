#ifndef SceneController_h__
#define SceneController_h__

#include "Engine_Defines.h"
#include "Base.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CObjectController : public CBase
{
private:
	explicit					CObjectController(const _int& iObjTypeNum);

public:
	virtual						~CObjectController(void);

public:
	_int						Update_Objects(const _float& fTimeDelta);
	HRESULT						Add_GameObject(const _int iObjType, CGameObject* pObj);

private:
	_int						m_iMaxObjTypeNum;
	vector<list<CGameObject*>>	m_vecObjList;
	class CSearchMgr*			m_pSearchMgr;
	class CCollisionMgr*		m_pColMgr;

public:
	static CObjectController*	Create(const _int& iObjTypeNum);

private:
	inline virtual void			freeMem(void);
};

END

#endif // SceneController_h__