#ifndef __MY_LAYER_H__

#include "../NonMoveObject.h"

class CMyLayer : public CNonMoveObject
{
private:
	CMyLayer();

public:
	virtual ~CMyLayer();

	static	CMyLayer*	Create(
		const	std::wstring&	wStrObjectKey,
		const	std::wstring&	wStrObjectStatus,
		const	D3DXVECTOR3&	vecPos,
		const	D3DXVECTOR3&	vecSize);

public:
	virtual int Update		() override;
	virtual void LateUpdate	() override;

	void SetSpeed			(float fSpeed) {	m_fSpeed = fSpeed; }


private:
	void			SetMatrix
	(
		const	D3DXVECTOR3&	vecPos, 
		const	D3DXVECTOR3&	vecSize
	);

	virtual void	UpdateRect() override;
	
	void			AssertMember();

private:
	float			m_fSpeed;
};
#define __MY_LAYER_H__
#endif // !__MY_LAYER_H__