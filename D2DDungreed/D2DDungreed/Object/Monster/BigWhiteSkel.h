#ifndef __BIG_WHITE_SKEL

#include "MeleeMonster.h"

class CBigWhiteSkel : public CMeleeMonster
{
private:
	CBigWhiteSkel				();

	void CreateEffect			();

public:
	virtual ~CBigWhiteSkel		();

	static CBigWhiteSkel* Create(const D3DXVECTOR3& vecPos);

	virtual void Attack			() override;
	virtual void Act			() override;
	
	virtual void UpdateRect		() override;
};

#define __BIG_WHITE_SKEL
#endif