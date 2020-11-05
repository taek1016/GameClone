#ifndef __BOSS_HP_H__

#include "../GameObject.h"
#include "../Monster/Boss.h"

class CBossHP : public CGameObject
{
private:
	float				m_fPercent;
	CBoss*				m_pTarget;
	class CBossHPBar*	m_pBar;

private:
	CBossHP();

	void SetTarget		(CBoss* pObj)
	{
		m_pTarget = pObj;
	}

public:
	virtual ~CBossHP();

	static CBossHP* Create(const D3DXVECTOR3& vecPos, CBoss* pTarget);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __BOSS_HP_H__
#endif