#ifndef __UNSEEN_OBJECT_H__

#include "../MoveObject.h"

class CUnseenObject : public CMoveObject
{
private:
	CUnseenObject();

public:
	virtual ~CUnseenObject();

	static CUnseenObject*	Create();

	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render() override;
};

#define __UNSEEN_OBJECT_H__
#endif