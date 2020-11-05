#ifndef __ICICLE_SUMMON_H__

#include "../GameObject.h"

class CIcicleSummon : public CGameObject
{
private:
	CIcicleSummon();

public:
	virtual ~CIcicleSummon();

	static CIcicleSummon* Create(const D3DXVECTOR3& vecPos);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __ICICLE_SUMMON_H__
#endif