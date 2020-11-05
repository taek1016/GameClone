#ifndef __GAME_OBJECT_H__

class CGameObject
{
protected:
	CGameObject();

public:
	virtual ~CGameObject();

	virtual int Update		() PURE;
	virtual	void LateUpdate	() PURE;
	virtual	void Render		() PURE;

	void ForceUpdateRect	()
	{
		UpdateRect();
	}

	void SetPosition(const D3DXVECTOR3& vecPos)
	{
		m_tInfo.SetPos(vecPos);
	}

	const D3DXVECTOR3& GetPos			() const 
	{ 
		return m_tInfo.vPos; 
	}
	const D3DXVECTOR3 GetSize			() const 
	{ 
		return m_tInfo.vSize;
	}
	const RECT& GetRect					() const 
	{ 
		return m_tMainRect; 
	}
	const std::wstring& GetObjectKey	() const 
	{ 
		return m_wStrObjectKey; 
	}
	const std::wstring& GetObjectStatus	() const 
	{
		return m_wStrObjectStatus; 
	}
	const float GetCurFrame				() const
	{
		return m_tFrame.fCurFrame;
	}
	const OBJECT_TYPE GetType			() const 
	{ 
		return m_eObjType; 
	}

	void SetObjectKey					(const std::wstring& wStrkey) 
	{ 
		m_wStrObjectKey = wStrkey; 
	}
	void SetObjectStatus				(const std::wstring& wStrStatus) 
	{ 
		m_wStrObjectStatus = wStrStatus; 
	}
	void SetObjType						(const OBJECT_TYPE eType) 
	{ 
		m_eObjType = eType; 
	}

protected:
	virtual	void UpdateRect	() PURE;

	void Animate			();


private:
	void AssertMember		();

protected:
	OBJECT_INFO				m_tInfo;
	
	RECT					m_tMainRect;
	
	FRAME					m_tFrame;

	std::wstring			m_wStrObjectKey;
	std::wstring			m_wStrObjectStatus;

	OBJECT_TYPE				m_eObjType;
};
#define __GAME_OBJECT_H__
#endif // !__GAME_OBJECT_H__
