#ifndef ToolObjContainer_h__
#define ToolObjContainer_h__

#include "GameObject.h"

class CToolObjContainer : public CBase
{
public:
	explicit											CToolObjContainer(void);
	virtual												~CToolObjContainer(void);

public:
	void												Update(const float fTimeDelta);
	void												Render(void);

	Engine::CGameObject*								Get_Obj(const Engine::_tchar* pKey);
	void												Add_Obj(const Engine::_tchar* pKey, Engine::CGameObject* pObj);
	void												Delete_Obj(const Engine::_tchar* pKey);
	const map<const Engine::_tchar*, Engine::CGameObject*>*	Get_Map(void);
private:
	map<const Engine::_tchar*, Engine::CGameObject*>	m_mapObjContainer;

private:
	inline virtual void									Free(void);
};

#endif // ToolObjContainer_h__
