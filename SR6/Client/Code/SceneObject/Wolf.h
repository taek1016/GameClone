#ifndef Wolf_h__
#define Wolf_h__

#include "MonsterBase.h"

class CWolf : public CMonster
{
private:
	explicit	CWolf(void);
	explicit	CWolf(const CWolf& rhs);
	virtual		~CWolf(void);

public:
	virtual HRESULT			Late_Initialize(void);
	virtual HRESULT			Initialize_GameObject(void);
	virtual void			Render_GameObject(void);

	virtual void			LoadData(HANDLE hFile);

public:
	static CWolf*			Create(void);
	virtual CGameObject*	Clone(const Engine::_vec3* pPos = nullptr);
};

#endif // Wolf_h__
