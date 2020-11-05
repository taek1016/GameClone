#ifndef __HIT_SCREEN_H__

#include "../../Object/GameObject.h"

class CHitScreen : public CGameObject
{
private:
	bool			m_bActivate;
	float			m_fDelta;

public:
	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
	void SetHit					()
	{
		m_fDelta = 0.f;
		m_bActivate = true;
	}

	DECLARE_SINGLETON(CHitScreen)
private:
	CHitScreen();
	virtual ~CHitScreen();

};

#define __HIT_SCREEN_H__
#endif