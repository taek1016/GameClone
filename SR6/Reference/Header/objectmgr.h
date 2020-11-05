#ifndef ObjectMgr_h__
#define ObjectMgr_h__

#include "Engine_Defines.h"
#include "Base.h"

#include "ObjectController.h"

BEGIN(Engine)

class CSearchMgr;

class ENGINE_DLL CObjectMgr : public CBase
{

	DECLARE_SINGLETON(CObjectMgr)

private:
	explicit					CObjectMgr(void);
	virtual						~CObjectMgr(void);

public:
	HRESULT						SetUp_CurScene(const _int& iMapNum);
	HRESULT						SetUp_ObjectMgr(const _int& iMapNum, const _int& pObjTypes);
	_int						Update_Objects(const _float& fTimeDelta);
	HRESULT						Add_GameObject(const _int& iSceneNum, const _int& iObjTag, CGameObject* pObj);

private:
	_int						m_iCurMap;
	_int						m_iMapNum;
	vector<CObjectController*>	m_vMapController;
	CSearchMgr*					m_pSearchMgr;

private:
	inline virtual void			freeMem(void);
};

END

#endif // ObjectMgr_h__