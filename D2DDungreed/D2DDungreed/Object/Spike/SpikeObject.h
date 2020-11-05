#ifndef __SPIKE_OBJECT_H__

#include "../GameObject.h"
class CSpikeObject : public CGameObject
{
private:
	bool				m_bActivate;
	float				m_fDamage;

private:
	CSpikeObject();

public:
	virtual ~CSpikeObject();

	static CSpikeObject* Create(const D3DXVECTOR3& vecPos);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;

};

#define __SPIKE_OBJECT_H__
#endif