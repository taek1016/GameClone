#ifndef __STAGE_0_H__

#include "../Managers/SceneMgr/Scene.h"

class CStage0 : public CScene
{
private:
	CStage0();

public:
	virtual ~CStage0();

	static	CStage0*	Create();

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

#define __STAGE_0_H__
#endif