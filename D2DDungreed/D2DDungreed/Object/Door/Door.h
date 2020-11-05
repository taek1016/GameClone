#ifndef __DOOR_H__
#include "../GameObject.h"
class CDoor : public CGameObject
{
private:
	bool			m_bClosed;
	bool			m_bAlreadyIn;

private:
	CDoor();

	void SetIn					(bool bIn)
	{
		m_bAlreadyIn = bIn;
	}

public:
	virtual ~CDoor			();

	static CDoor* Create		(const D3DXVECTOR3& vecPos, const bool bAlreadyIn);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __DOOR_H__
#endif