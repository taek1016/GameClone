#ifndef __HECATE_H__

#include "BasicGun.h"

class CHecate : public CBasicGun
{
private:
	CHecate();

public:
	virtual ~CHecate();

	static CHecate* Create		();

	// CBasicGun��(��) ���� ��ӵ�
	virtual void CreateBullet	() override;
	virtual void CreateEffect	() override;
	virtual void Render			() override;
};

#define __HECATE_H__
#endif