#ifndef __SUMMON_EFFECT_H__

#include "../GameObject.h"

class CSummonEffect : public CGameObject
{
private:
	MONSTER_TYPE	m_eMonsterType;

private:
	CSummonEffect();

	void SetMonster			(MONSTER_TYPE eType)
	{
		m_eMonsterType = eType;
	}
	void SpawnMonster		();

public:
	virtual ~CSummonEffect	();

	static CSummonEffect*	Create
	(
		const D3DXVECTOR3&	vecPos,
		MONSTER_TYPE		eMonsterType
	);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __SUMMON_EFFECT_H__
#endif