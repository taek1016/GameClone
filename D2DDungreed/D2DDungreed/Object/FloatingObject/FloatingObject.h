#ifndef __FLOATING_OBJECT_H__

#include "../GameObject.h"

class CFloatingObject : public CGameObject
{
private:
	bool				m_bCollide;

	float				m_fCurTime;

private:
	CFloatingObject					();

public:
	virtual ~CFloatingObject		();

	static CFloatingObject* Create	(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize);

	virtual int Update				() override;
	virtual void LateUpdate			() override;
	virtual void Render				() override;
	virtual void UpdateRect			() override;
};

#define __FLOATING_OBJECT_H__
#endif