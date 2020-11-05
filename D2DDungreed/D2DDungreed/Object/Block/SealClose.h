#ifndef __SEAL_CLOSE_H__

#include "../GameObject.h"

class CSealClose : public CGameObject
{
private:
	float			m_fAngle;
private:
	CSealClose();

public:
	virtual ~CSealClose();

	static CSealClose* Create(const D3DXVECTOR3& vecPos, const D3DXVECTOR3& vecSize, const float fAngle);

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateRect() override;
};

#define __SEAL_CLOSE_H__
#endif