#ifndef InGameObject_h__
#define InGameObject_h__

#include "GameObject.h"

class CInGameObject : public Engine::CGameObject
{
protected:
	CInGameObject();
	CInGameObject(const CInGameObject& rhs);
public:
	virtual void LoadData(HANDLE hFile)override;

	// CGameObject을(를) 통해 상속됨
	virtual Engine::CGameObject * Clone(const Engine::_vec3 * pPos = nullptr) override;

	virtual Engine::_int		Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void				Render_GameObject(void);
	static CInGameObject* Create();

	virtual void				freeMem()override;
};

#endif