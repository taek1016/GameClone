#ifndef __ICE_PILLAR_CREATE_H__

#include "../GameObject.h"

class CBoss;
class CIcePillarCreate : public CGameObject
{
private:
	int			m_iIndex;
	float		m_fRevolve;
	float		m_fAngle;
	CBoss*		m_pTarget;

private:
	CIcePillarCreate();

	void SetTarget					(CBoss* pObj)
	{
		m_pTarget = pObj;
	}
	void SetSelfRot					(float fAngle) 
	{
		m_fAngle = fAngle;
	}
	void SetRevolve					(float fAngle)
	{
		m_fRevolve = fAngle;
	}
	void SetIndex					(int iIndex)
	{
		m_iIndex = iIndex;
	}

public:
	virtual ~CIcePillarCreate		();

	static CIcePillarCreate* Create	(int iIndex, float fSelfRotAngle, float fRevolveAngle, CBoss* pObj);

	virtual int Update				() override;
	virtual void LateUpdate			() override;
	virtual void Render				() override;
	virtual void UpdateRect			() override;
};

#define __ICE_PILLAR_CREATE_H__
#endif