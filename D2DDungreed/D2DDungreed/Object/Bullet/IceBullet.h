#ifndef __ICE_BULLET_H__

#include "BulletBase.h"

class CIceBullet : public CBulletBase
{
private:
	float		m_fRotationAngle;

private:
	CIceBullet();

	void SetRotationAngle	(float fAngle)
	{
		m_fRotationAngle = fAngle;
	}

public:
	virtual ~CIceBullet		();

	static CIceBullet* Create
	(
		const D3DXVECTOR3&	vecPos,
		const float			fAngle, 
		const float			fRotationAngle
	);


	// CBulletBase을(를) 통해 상속됨
	virtual void SetEffect	() override;
	virtual void LateUpdate	() override;
};

#define __ICE_BULLET_H__
#endif