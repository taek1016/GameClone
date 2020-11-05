#ifndef __BANSHEE_BULLET_H__

#include "BulletBase.h"

class CBansheeBullet : public CBulletBase
{
private:
	float			m_fCurTime;
private:
	CBansheeBullet();

	void SetAngle			(float fAngle)
	{
		m_fAngle = fAngle;
	}
	void SetSpeed			(float fSpeed)
	{
		m_fSpeed = fSpeed;
	}
	void SetDamage			(float fDamage)
	{
		m_fDamage = fDamage;
	}

public:
	virtual ~CBansheeBullet();

	static CBansheeBullet* Create(const D3DXVECTOR3& vecPos, const float fAngle);

	virtual void LateUpdate		() override;
	virtual void SetEffect		() override;
};

#define __BANSHEE_BULLET_H__
#endif