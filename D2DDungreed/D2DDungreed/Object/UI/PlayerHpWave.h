#ifndef __PLAYER_HP_WAVE_H__

#include "../GameObject.h"

class CPlayerHpWave : public CGameObject
{
private:
	class CPlayer*	m_pPlayer;

private:
	CPlayerHpWave();

public:
	virtual ~CPlayerHpWave();

	static CPlayerHpWave* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __PLAYER_HP_WAVE_H__
#endif