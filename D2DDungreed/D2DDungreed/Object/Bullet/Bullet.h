#ifndef __BULLET_H__

#include "BulletBase.h"

class CBullet : public CBulletBase
{
private:
	CBullet();

public:
	virtual ~CBullet	();

	static CBullet*	Create
	(
		const ATTACK_FROM	eFrom,
		const D3DXVECTOR3&	vecPos,
		const float			fAngle,
		const float			fDamage
	);


	// CBulletBase��(��) ���� ��ӵ�
	virtual void SetEffect() override;

};

#define __BULLET_H__
#endif