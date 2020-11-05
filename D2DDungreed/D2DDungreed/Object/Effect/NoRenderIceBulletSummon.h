#ifndef __NO_RENDER_BULLET_SUMMON_H__

#include "../GameObject.h"

class CNoRenderIceBulletSummon : public CGameObject
{
private:
	int		m_iCurMakeBullet;
	float	m_fCurTime;

private:
	CNoRenderIceBulletSummon();

public:
	virtual ~CNoRenderIceBulletSummon		();

	static CNoRenderIceBulletSummon* Create	(const D3DXVECTOR3& vecPos);

	virtual int Update						() override;
	virtual void LateUpdate					() override;
	virtual void Render						() override;
	virtual void UpdateRect					() override;
};

#define __NO_RENDER_BULLET_SUMMON_H__
#endif