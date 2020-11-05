#ifndef __ICE_SPEAR_EFFECT_H__

#include "../GameObject.h"

class CIceSpearEffect : public CGameObject
{
private:
	CIceSpearEffect();

public:
	virtual ~CIceSpearEffect();

	static CIceSpearEffect* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __ICE_SPEAR_EFFECT_H__
#endif