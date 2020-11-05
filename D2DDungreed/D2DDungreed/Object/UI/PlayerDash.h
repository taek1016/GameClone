#ifndef __PLAYER_DASH_H__

#include "../GameObject.h"

class CPlayerDashImage;
class CPlayerDash : public CGameObject
{
private:
	const int			m_iRealMaxDashCount;
	int					m_iMaxDashCount;
	int					m_iCurDashCount;
	CPlayerDashImage**	m_pDashImage;

private:
	CPlayerDash();

public:
	virtual ~CPlayerDash();

	static CPlayerDash* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __PLAYER_DASH_H__
#endif