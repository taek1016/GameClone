#ifndef __BULLET_MAKE_EFFECT_H__

#include "../GameObject.h"

class CBulletMakeEffect : public CGameObject
{
private:
	CBulletMakeEffect();

	void SummonBullet
	(
		const D3DXVECTOR3&	vecPos, 
		const float			fWayAngle, 
		const float			fRotationAngle
	);
public:
	virtual ~CBulletMakeEffect();
	static CBulletMakeEffect* Create
	(
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const std::wstring& wstrKey,
		const std::wstring& wstrStatus, 
		const WORD&			wMaxIndex
	);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __BULLET_MAKE_EFFECT_H__
#endif