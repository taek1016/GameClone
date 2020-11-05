#ifndef NPCBase_h__
#define NPCBase_h__

#include "Character/Character.h"

class CUIBase;

class CNPCBase : public CCharacterBase
{
protected:
	explicit				CNPCBase(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit				CNPCBase(const CNPCBase& rhs);
	virtual					~CNPCBase(void) = default;

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual HRESULT			Late_Initialize(void) override;

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta) override;

protected:
	virtual void			act(void) { ; }
	virtual void			read_Data(void) override;
	virtual Engine::_float	get_ReadData(const Engine::_tchar* pKey) override;

	void					mouse_Click(const Engine::_float& fTimeDelta);

	virtual void			initialize_NPCUI(void) PURE;

	Engine::_bool			m_bUIActivate;
	CUIBase*				m_pUI;

protected:
	inline virtual void		Free(void) override;
};

#endif // NPCBase_h__
