#ifndef __MOUSE_MGR_H__

class CBaseItem;
class CMouseMgr
{
	DECLARE_SINGLETON(CMouseMgr)
private:
	CMouseMgr();
	~CMouseMgr();

public:
	void		Update		();
	void		LateUpdate	();
	void		Render		();

	D3DXVECTOR3	GetMousePos	();
	void		SetMouseType(MOUSE_TYPE	eType);

	void		Init		(HWND hWnd);

	void SetItem			(CBaseItem* pObj)
	{
		m_pItem = pObj;
#ifdef _DEBUG
		if (!m_pItem)
		{
			printf("false\n");
		}
#endif // _DEBUG

	}
	CBaseItem* GetItem		()
	{
		return m_pItem;
	}

private:
	POINT				m_ptMouse;

	std::wstring		m_wstrObjectKey;
	std::wstring		m_wstrMouseState;

	MOUSE_TYPE			m_eCurMouseType;
	D3DXMATRIX			m_matWorld;
	
	HWND				m_hWnd;

	CBaseItem*			m_pItem;
};

#define __MOUSE_MGR_H__
#endif // !__MOUSE_MGR_H__