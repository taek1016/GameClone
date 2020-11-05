#ifndef Terrain_h__
#define Terrain_h__

#include "GameObject.h"

BEGIN(Engine)

class CTerrainTex;
class CTexture;
class CTransform;
class CRenderer;

END

class CTerrain : public Engine::CGameObject
{
private:
	explicit CTerrain(void);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain(void);

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

private:


public:
	static CTerrain*				Create();
	virtual Engine::CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;
	virtual void					LoadData(HANDLE hFile) override;

private:
	virtual void			freeMem(void) override;
};

#endif // Terrain_h__
