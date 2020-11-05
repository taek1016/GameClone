#ifndef PickMgr_h__
#define PickMgr_h__

#include "Base.h"

class CTerrain;

class CPickMgr : public CBase
{
	DECLARE_SINGLETON(CPickMgr)

private:
	explicit			CPickMgr(void);
	virtual				~CPickMgr(void);

public:
	void				Update_Debug(void);

	Engine::_vec3		SetUp_OnTerrain(Engine::_ulong& dwIndex, const Engine::_vec3* pPos, const Engine::_vec3* pDir);

	Engine::_float		Get_CertainTerrainHeight(const Engine::_ulong dwIdx, const Engine::_vec3* pPos);
	Engine::_float		Get_TerrainHeight(const Engine::_vec3* pPos);
	Engine::_float		Get_ReverseTerrainHeight(const Engine::_vec3* pPos);
	Engine::_ulong		Get_Index(const Engine::_vec3* pPos);
	Engine::_bool		Select_Mouse(const Engine::_vec3* pMouseWorldPos, const Engine::CSphereCollider* pSphere);
	
private:
	//inline void			

private:
	inline virtual void	Free(void) override;
};

#endif // PickMgr_h__
