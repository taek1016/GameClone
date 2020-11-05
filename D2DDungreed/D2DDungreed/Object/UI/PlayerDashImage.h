#ifndef __PLAYER_DASH_IMAGE_H__
#include "../GameObject.h"
class CPlayerDashImage : public CGameObject
{
private:
	CPlayerDashImage();

public:
	virtual ~CPlayerDashImage();

	static CPlayerDashImage* Create(const D3DXVECTOR3& vecPos);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __PLAYER_DASH_IMAGE_H__
#endif