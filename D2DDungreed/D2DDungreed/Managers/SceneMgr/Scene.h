#ifndef __SCENE_H__
#define __SCENE_H__

class CScene
{
protected:
	CScene						();

public:
	virtual ~CScene				();

public:
	virtual int		Update		() PURE;
	virtual void	LateUpdate	() PURE;
	virtual void	Render		() PURE;

protected:
	virtual HRESULT	Initialize	() PURE;
	virtual void	Release		() PURE;

	void SetSceneName			(const std::wstring& wstr) { m_wstrName = wstr; }
	void SetStatus				(const std::wstring& wStr) { m_wStrStatus = wStr; }
	void SetSpawnEffect			(const D3DXVECTOR3& vecPos, MONSTER_TYPE eType);
	HRESULT SetSpawnPlayer		(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecWorldRS);
	void SpawnLayer				();
	void SpawnBasicBox			(const D3DXVECTOR3& vecPos, CBaseItem* pItem);
	void SpawnSealBlock			(const D3DXVECTOR3& vecPos, const D3DXVECTOR3 vecSize, float fRadian);
	void SpawnDoor				(const D3DXVECTOR3& vecPos, const bool bAlreadyIn);
	void SpawnFairy				(const D3DXVECTOR3& vecPos, const FAIRY_SIZE eSize);
	void SpawnSpikeObject		(const D3DXVECTOR3& vecPos);
	void SpawnBoss				(const D3DXVECTOR3& vecPos);

protected:
	std::wstring	m_wstrName;
	std::wstring	m_wStrStatus;

	D3DXMATRIX		m_tWorld;

	int				m_iEvent;
};

#endif // !__SCENE_H__