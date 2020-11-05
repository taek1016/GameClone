#ifndef Portion_h__
#define Portion_h__

#include "UsableBase.h"

class CPortion : public Engine::CUsableBase
{
private:
	explicit						CPortion(void);
	explicit						CPortion(const CPortion& rhs);
	virtual							~CPortion(void);

public:
	virtual HRESULT					Late_Initialize();
	virtual HRESULT					Initialize_GameObject();
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta);

	virtual void					Use_Item(void);

private:


public:
	virtual Engine::CGameObject*	Clone(const Engine::_vec3* pPos) PURE;
	virtual void					Set_Obj(Engine::CGameObject* pObj) PURE;

	virtual void					LoadData(HANDLE hFile) PURE;

protected:
	virtual void					freeMem(void);

};
#endif // Portion_h__
