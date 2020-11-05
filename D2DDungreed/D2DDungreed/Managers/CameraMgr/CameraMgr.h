#ifndef __CAMERA_MGR_H__

class CGameObject;
class CCamera
{
private:
	float			m_fCurTime;
	bool			m_bHit;
	D3DXVECTOR3		m_vecPos;
	D3DXVECTOR3		m_vecClientRS;
	D3DXVECTOR3		m_vecWorldRS;
	D3DXVECTOR3		m_vecPivot;
	CGameObject*	m_pTarget;

public:
	void SetHit()
	{
		m_fCurTime = 0.f;
		m_bHit = true;
	}
	void SetTarget(CGameObject* pObj) 
	{ 
		m_pTarget = pObj; 
	}
	void SetPos(const D3DXVECTOR3 vecPos)
	{
		m_vecPos = vecPos;
	}
	void SetClientRS(const D3DXVECTOR3 vecClientRS)
	{
		m_vecClientRS = vecClientRS;
	}
	void SetWorldRS(const D3DXVECTOR3 vecWorldRS)
	{
		m_vecWorldRS = vecWorldRS;
	}
	void SetPivot(const D3DXVECTOR3	vecPivot)
	{
		m_vecPivot = vecPivot;
	}
	void SetTargetNullptr()
	{
		m_pTarget = nullptr;
	}

	const D3DXVECTOR3 GetPos() const
	{
		return m_vecPos;
	}

public:
	void LateUpdate();
	DECLARE_SINGLETON(CCamera)

private:
	CCamera();
	~CCamera();

	void AssertMember();
};

#define __CAMERA_MGR_H__
#endif