#ifndef __MY_BUTTON_H__

#include "..\NonMoveObject.h"

class CMyButton : public CNonMoveObject
{
private:
	CMyButton();

public:
	virtual ~CMyButton();

	static	CMyButton*	Create(
		const	std::wstring&	wStrObjectKey,
		const	std::wstring&	wStrObjectStatus,
		const	D3DXVECTOR3&	vecPos,
		const	D3DXVECTOR3&	vecSize);

public:
	virtual int Update			() override;
	virtual void LateUpdate		() override;
	
	bool GetClicked				()
	{
		return m_bClicked;
	}
	void SetButtonNonClicked	()
	{
		m_bClicked = false;
	}
private:
	void SetMatrix	
	(
		const D3DXVECTOR3& vecPos, 
		const D3DXVECTOR3& vecSize
	);

	virtual void	UpdateRect()	override;

	void			Assertmember();

private:
	bool		m_bClicked;
};
#define __MY_BUTTON_H__
#endif // !__MY_BUTTON_H__
