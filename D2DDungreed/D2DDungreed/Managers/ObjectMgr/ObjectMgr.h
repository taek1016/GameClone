#ifndef __OBJECT_MGR_H__
#define __OBJECT_MGR_H__

class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	HRESULT	AddObject(OBJECT_TYPE eType, CGameObject* pObj);
	int		Update();
	void	LateUpdate();
	void	Render();

	const OBJECT_LIST* GetObjList(OBJECT_TYPE eType)
	{
		return &m_objList[eType];
	}
	void	Release();

private:
	void	AssertMember();

private:
	OBJECT_LIST			m_objList[OBJECT_TYPE::OBJECT_END];
};

#endif	//__OBJECT_MGR_H__