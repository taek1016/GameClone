#ifndef __BOSS_HP_BAR_H__

#include "../GameObject.h"
#include "../Monster/Boss.h"

class CBossHPBar : public CGameObject
{
private:
	float	m_fPercent;
	CBoss*	m_pTarget;

private:
	CBossHPBar();

	void SetTarget(CBoss* pTarget)
	{
		m_pTarget = pTarget;
	}

public:
	virtual ~CBossHPBar();

	static CBossHPBar* Create	(const D3DXVECTOR3& vecPos, CBoss* pTarget);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __BOSS_HP_BAR_H__
#endif