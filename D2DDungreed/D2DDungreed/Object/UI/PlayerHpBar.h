#ifndef __PLAYER_HP_BAR_H__

#include "../GameObject.h"

class CPlayerHpBar : public CGameObject
{
private:
	class CPlayer*	m_pPlayer;
	float			m_fPercent;

private:
	CPlayerHpBar();

public:
	virtual ~CPlayerHpBar();

	static CPlayerHpBar* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __PLAYER_HP_BAR_H__
#endif