#ifndef ToolStaticObjectCtrl_h__
#define ToolStaticObjectCtrl_h__

#include "Engine_Defines.h"
#include "Base.h"

class CToolStaticObject;

class CToolStaticObjectCtrl : public CBase
{
private:
	explicit						CToolStaticObjectCtrl(void);
	virtual							~CToolStaticObjectCtrl(void);

public:
	CToolStaticObject*				Get_Selected(void);
	void							Add_Objects(CToolStaticObject* pObj);
	void							KeyInput(void);

private:
	Engine::_vec3					worldToProj(const Engine::_vec3* pPos);
	Engine::_bool					is_Same(const Engine::_vec3* pV1, const Engine::_vec3* pV2);

	list<CToolStaticObject*>		m_ObjList;
	CToolStaticObject*				m_pSelected;

public:
	static CToolStaticObjectCtrl*	Create(void);

private:
	inline virtual void				Free(void);
};

#endif // ToolStaticObjectCtrl_h__
