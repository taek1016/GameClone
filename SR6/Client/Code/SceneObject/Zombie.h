#ifndef Zombie_h__
#define Zombie_h__

#include "MonsterBase.h"

class CZombie : public CMonster
{
private:
	explicit	CZombie(void);
	explicit	CZombie(const CZombie& rhs);
	virtual		~CZombie(void);

public:
	virtual HRESULT			Initialize_GameObject(void);
	virtual void			Render_GameObject(void);

	virtual void			LoadData(HANDLE hFile) { ; }

public:
	static CZombie*			Create(void);
	virtual CGameObject*	Clone(const Engine::_vec3* pPos = nullptr);
};

#endif // Zombie_h__
