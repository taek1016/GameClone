#ifndef __PLAYER_UI_H__

#include "../GameObject.h"

class CPlayerHP;
class CPlayerDash;

class CPlayerUI
{
	DECLARE_SINGLETON(CPlayerUI)
private:
	CPlayerUI();
	~CPlayerUI();

private:
	CPlayerHP*		m_pPlayerHP;
	CPlayerDash*	m_pPlayerDash;

public:
	void Update();
	void LateUpdate();
	void Render();
};

#define __PLAYER_UI_H__
#endif