#ifndef __EFFECT_H__

#include "../GameObject.h"

class CEffect : public CGameObject
{
private:
	float	m_fAngle;
	float	m_fTime;
	float	m_fHalfX;
	float	m_fHalfY;

private:
	CEffect();

public:
	virtual ~CEffect();

	static CEffect* Create
	(
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const EFFECT_TYPE&	eType,
		const float			fAngle = 0.f,
		const float			fTime = 1.f
	);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __EFFECT_H__
#endif