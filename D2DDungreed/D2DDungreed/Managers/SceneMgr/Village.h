#ifndef __VILLAGE_H__
#include "Scene.h"
class CVillage : public CScene
{
private:
	CVillage();

public:
	virtual ~CVillage();

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	static	CVillage*	Create();

private:
	virtual void Release() override;
	virtual HRESULT Initialize() override;
};

#define __VILLAGE_H__
#endif