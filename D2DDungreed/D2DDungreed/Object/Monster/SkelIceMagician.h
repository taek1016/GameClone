#ifndef __SKEL_ICE_MAGICIAN_H__

#include "RangeMonster.h"
class CSkelIceMagician : public CRangeMonster
{
private:
	float	m_fCurTime;
private:
	CSkelIceMagician();

public:
	virtual ~CSkelIceMagician();

	static CSkelIceMagician* Create(const D3DXVECTOR3& vecPos);

	virtual void Attack		() override;
	virtual void Act		() override;

	virtual void UpdateRect	() override;
};

#define __SKEL_ICE_MAGICIAN_H__
#endif