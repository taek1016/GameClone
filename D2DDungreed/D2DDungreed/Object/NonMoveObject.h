#ifndef __NON_MOVE_OBJECT_H__

#include "../D2DDungreed/Object/GameObject.h"


class CNonMoveObject : public CGameObject
{
protected:
	CNonMoveObject();
	virtual ~CNonMoveObject();

public:
	// CGameObject��(��) ���� ��ӵ�
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