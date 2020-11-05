#ifndef __ICICLE_H__
#include "BulletBase.h"
class CIcicle : public CBulletBase
{
private:
	float		m_fCurTime;
private:
	CIcicle();

public:
	virtual ~CIcicle();

	static CIcicle* Create(const D3DXVECTOR3& vecPos);

	virtual void LateUpdate() override;
	virtual void SetEffect() override;
};

#define __ICICLE_H__
#endif