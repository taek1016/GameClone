#ifndef __MISSILE_WARNING_H__
#include "../GameObject.h"
class CMissileWarningEffect : public CGameObject
{
private:
	float		m_fAngle;

private:
	CMissileWarningEffect();

	void SetAngle(float fAngle)
	{
		m_fAngle = fAngle;
	}

public:
	virtual ~CMissileWarningEffect();

	static CMissileWarningEffect* Create(const D3DXVECTOR3& vecPos, const float fAngle = 0.f);

	virtual int Update					() override;
	virtual void LateUpdate				() override;
	virtual void Render					() override;
	virtual void UpdateRect				() override;
};

#define __MISSILE_WARNING_H__
#endif