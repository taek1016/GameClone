#ifndef __PLAYER_HP_H__

#include "../GameObject.h"

class CPlayerHP : public CGameObject
{
private:
	class CPlayer*			m_pPlayer;
	class CPlayerHpBar*		m_pBar;
	class CPlayerHpWave*	m_pWave;

	CPlayerHP();

public:
	virtual ~CPlayerHP		();

	static CPlayerHP* Create(const D3DXVECTOR3& vecPos);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __PLAYER_HP_H__
#endif