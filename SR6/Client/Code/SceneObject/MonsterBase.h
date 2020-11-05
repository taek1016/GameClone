#ifndef MonsterBase_h__
#define MonsterBase_h__

#include "PickableObject.h"

class CMonster : public CPickableObject
{
protected:
	explicit				CMonster(void);
	explicit				CMonster(const CMonster& rhs);
	virtual					~CMonster(void);

public:
	virtual HRESULT			Late_Initialize(void);
	virtual HRESULT			Initialize_GameObject(void);
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void			Render_GameObject(void) {};
	virtual void			Take_Damage(const _float& fDamage);
	
	virtual void			LoadData(HANDLE hFile) PURE;

	void					SetCurStatus(const OBJECT_STATUS& eStatus);
	void					SetPreStatus(void);

protected:
	void					ChangeStatus();
	void					SetStatus();
	void					SetFrame();
	void					Initialize_Texture(const _tchar* pKey);
	Engine::_int			m_iStatusAction[OBJECT_STATUS::STATUS_END]{};

	Engine::CTexture*		m_pTexture[OBJECT_STATUS::STATUS_END]{};
	Engine::CTexture*		m_pCurTexture = nullptr;

	Engine::_int			m_iHP;
	Engine::_int			m_iMaxHP;

	Engine::_float			m_fAttLength;
	Engine::_float			m_fMoveLength;

	Engine::_float			m_fCurFrame = 0.f;
	Engine::_float			m_fMaxFrame = 0.f;

	class CPlayer*			m_pPlayer = nullptr;

	wstring					m_wstrRenderKey;

	OBJECT_STATUS			m_eCurStatus = OBJECT_STATUS::STATUS_END;
	OBJECT_STATUS			m_ePreStatus = OBJECT_STATUS::STATUS_END;

private:
	virtual void			freeMem();
};
#endif // MonsterBase_h__
