#ifndef __STAGE_2_H__
#include "../Managers/SceneMgr/Scene.h"
class CStage2 : public CScene
{
private:
	bool	m_bAfterSpawn;
	bool	m_bSpawned;
private:
	CStage2();

	void SpawnMonster();
	void SpawnResult();
public:
	virtual ~CStage2();

	static CStage2* Create();

	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

#define __STAGE_2_H__
#endif