#ifndef __FAIRY_H__

#include "../GameObject.h"
class CFairy : public CGameObject
{
private:
	LONG					m_longWidthHalf;
	LONG					m_longHeightHalf;

	int						m_iHealPoint;

	bool					m_bTouched;

protected:
	CFairy					();

	void SetWidth			(LONG longHalf)
	{
		m_longWidthHalf = longHalf;
	}
	void SetHeight			(LONG longHalf)
	{
		m_longHeightHalf = longHalf;
	}
	void SetHealPoint		(int iHealPoint)
	{
		m_iHealPoint = iHealPoint;
	}

public:
	virtual ~CFairy			();

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __FAIRY_H__
#endif