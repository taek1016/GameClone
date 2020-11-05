#ifndef __MONSTER_HP_UI_H__
#include "../GameObject.h"

#include "../MoveObject.h"

class CMonsterHPUI : public CGameObject
{
private:
	const CMoveObject*	m_pTarget;

	float				m_fPercent;
	
private:
	CMonsterHPUI				();

	void SetObject				(const CMoveObject* pObj)
	{
		m_pTarget = pObj;
	}

public:
	virtual ~CMonsterHPUI();

	static CMonsterHPUI* Create	(const CMoveObject* pObj);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __MONSTER_HP_UI_H__
#endif