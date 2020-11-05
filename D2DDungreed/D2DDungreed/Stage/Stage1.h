#ifndef __STAGE_1_H__
#include "../Managers/SceneMgr/Scene.h"
class CStage1 : public CScene
{
private:
	bool		m_bAllKilled;
	bool		m_bAfterSpawn;
	bool		m_bSpawned;

private:
	CStage1();

public:
	virtual ~CStage1();

	static CStage1* Create();

	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

	void SpawnMonster();
	void SpawnResult();
};

#define __STAGE_1_H__
#endif