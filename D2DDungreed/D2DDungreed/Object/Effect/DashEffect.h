#ifndef __DASH_EFFECT_H__

#include "../GameObject.h"

class CDashEffect : public CGameObject
{
private:
	int			m_iColor;

private:
	CDashEffect				();

public:
	virtual ~CDashEffect	();

	static CDashEffect*	Create	
	(
		const D3DXVECTOR3&	vecPos, 
		const D3DXVECTOR3&	vecSize, 
		const std::wstring& wStrKey, 
		const std::wstring& wStrStatus, 
		const WORD&			wIndex
	);

	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;
	virtual void UpdateRect	() override;
};

#define __DASH_EFFECT_H__
#endif