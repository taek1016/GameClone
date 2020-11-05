#ifndef __STAGE_H__
#define __STAGE_H__

#include "Scene.h"
class CStage : public CScene
{
public:
	// CScene을(를) 통해 상속됨
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render() override;
	static	CStage*	Create();

private:
	CStage();

public:
	virtual ~CStage();

private:
	virtual HRESULT Initialize() override;
	virtual void	Release() override;
};

#endif // !__STAGE_H__