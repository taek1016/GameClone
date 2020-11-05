#ifndef __NO_RENDER_EFFECT_H__
#include "../GameObject.h"
class CNoRenderEffect : public CGameObject
{
private:
	float	m_fWidth;
	float	m_fHeight;
	float	m_fDamage;

	float	m_fDelta;

private:
	CNoRenderEffect();
	
	void SetWidth				(float fWidth)
	{
		m_fWidth = fWidth;
	}
	void SetHeight				(float fHeight)
	{
		m_fHeight = fHeight;
	}
	void SetDamage				(float fDamage)
	{
		m_fDamage = fDamage;
	}

public:
	virtual ~CNoRenderEffect	();

	static CNoRenderEffect* Create(const D3DXVECTOR3& vecPos, float fWidth, float fHeight, float fDamage);

	virtual int Update			() override;
	virtual void LateUpdate		() override;
	virtual void Render			() override;
	virtual void UpdateRect		() override;
};

#define __NO_RENDER_EFFECT_H__
#endif