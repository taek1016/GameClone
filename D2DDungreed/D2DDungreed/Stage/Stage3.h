#ifndef __STAGE_3_H__

#include "../Managers/SceneMgr/Scene.h"

class CStage3 : public CScene
{
private:
	bool	m_bSpawn;
	bool	m_bAfterSpawn;
private:
	CStage3();

	void SpawnMonster();
	void SpawnResult();

public:
	virtual ~CStage3();

	static CStage3* Create();

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

#define __STAGE_3_H__
#endif