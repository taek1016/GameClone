#ifndef __LARGE_LAYER_H__

#include "../NonMoveObject.h"

class CLargeLayer : public CNonMoveObject
{
private:
	CLargeLayer();

public:
	virtual ~CLargeLayer();

	static CLargeLayer* Create
	(
		const std::wstring&	wstrObjectKey,
		const std::wstring&	wstrObjectStatus,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize
	);

	virtual void UpdateRect	() override;
	virtual int Update		() override;
	virtual void LateUpdate	() override;
	virtual void Render		() override;

private:
	void SetMatrix
	(
		const	D3DXVECTOR3&	vecPos,
		const	D3DXVECTOR3&	vecSize
	);


private:	
	float			m_fSpeed;
};

#define __LARGE_LAYER_H__
#endif