#ifndef __NON_MOVE_OBJECT_H__

#include "../D2DDungreed/Object/GameObject.h"


class CNonMoveObject : public CGameObject
{
protected:
	CNonMoveObject();
	virtual ~CNonMoveObject();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int		Update()		override	PURE;
	virtual void	LateUpdate()	override	PURE;
	virtual void	Render()		override;

private:
	void			AssertMember();

protected:
	FRAME				m_tFrame;
};

#define __NON_MOVE_OBJECT_H__
#endif