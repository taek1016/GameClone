#ifndef __SEAL_EFFECT_H__

#include "../GameObject.h"

class CSealEffect : public CGameObject
{
private:
	float						m_fAngle;

private:
	CSealEffect					();

public:
	virtual ~CSealEffect		();

	static CSealEffect* Create	(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, const float fAngle);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __SEAL_EFFECT_H__
#endif