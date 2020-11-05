#ifndef PickingMgr_h__
#define PickingMgr_h__

class CPickableObject;
class CPickingMgr : public CBase
{
	DECLARE_SINGLETON(CPickingMgr)
	CPickingMgr();

	list<CPickableObject*> m_ltObjects;
public:
	void freeMem()override;
	CPickableObject* GetPickedObject(const Engine::_float& fTimeDelta, _float dist, _float* fOutDist);
	void Add_Object(CPickableObject* obj) { m_ltObjects.push_back(obj); }
	void Delete_Object(const _tchar* name);
};

#endif