#ifndef __BASIC_SWORD_H__

#include "Sword.h"

class CBasicSword : public CSword
{
private:
	CBasicSword();

	virtual void CreateEffect() override;

public:
	virtual ~CBasicSword();

	static CBasicSword*	Create
	(
		const float			fAttackCool,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize
	);

	static CBasicSword*	Create
	(
		const float			fAttackCool,
		const D3DXVECTOR3&	vecSize
	);
};

#define __BASIC_SWORD_H__
#endif