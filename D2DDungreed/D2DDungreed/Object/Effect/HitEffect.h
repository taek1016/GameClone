#ifndef __HIT_EFFECT_H__

#include "../GameObject.h"

class CHitEffect : public CGameObject
{
private:
	float			m_fCurTime;
	CGameObject*	m_pTarget;

private:
	CHitEffect();

	void SetTarget				(CGameObject* pObj)
	{
		m_pTarget = pObj;
	}

public:
	virtual ~CHitEffect			();

	static CHitEffect* Create	(const D3DXVECTOR3& vecPos, const CGameObject* pObj);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __HIT_EFFECT_H__
#endif