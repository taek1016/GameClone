#ifndef __ICE_SPEAR_H__
#include "../GameObject.h"
class CIceSpear : public CGameObject
{
private:
	bool			m_bDead;
	bool			m_bTargeting;

	float			m_fCurTime;
	float			m_fAngle;

private:
	CIceSpear();

public:
	virtual ~CIceSpear();

	static CIceSpear* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __ICE_SPEAR_H__
#endif