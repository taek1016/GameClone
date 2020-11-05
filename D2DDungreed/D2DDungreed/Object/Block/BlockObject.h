#ifndef __BLOCK_OBJECT_H__

#include "../GameObject.h"

class CBlockObject : public CGameObject
{
private:
	bool		m_bDelete;
	float		m_fAngle;

private:
	CBlockObject				();

	void SetAngle				(float fAngle)
	{
		m_fAngle = fAngle;
	}
	void SetDelete				()
	{
		m_bDelete = true;
	}
	void CollideWithObj			(const OBJECT_LIST& pTo);
public:
	virtual ~CBlockObject		();

	static CBlockObject* Create	(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, float fAngle);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __BLOCK_OBJECT_H__
#endif