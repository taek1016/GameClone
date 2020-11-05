#ifndef Iron_h__
#define Iron_h__

#include "GameObject.h"

class CIron : public Engine::CGameObject
{
private:
	explicit	CIron(void);
	explicit	CIron(const CIron& rhs);
	virtual		~CIron(void);

public:
	virtual HRESULT			Late_Initialize();
	virtual HRESULT			Initialize_GameObject();
	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void			Render_GameObject(void);

private:
	Engine::_int			m_iIndex;
	Engine::_float			m_fGatherTime = 0.f;
	Engine::_float			m_fDieTime = 2.f;

	Engine::CCollider*		m_pPlayerCol = nullptr;
	Engine::CCollider*		m_pMyCol = nullptr;
	Engine::CVIBuffer*		m_pBuffer = nullptr;
	Engine::CTexture*		m_pTexture = nullptr;

public:
	static CIron*			Create();

	virtual CGameObject *	Clone(const Engine::_vec3 * pPos = nullptr) override;

private:
	virtual void			LoadData(HANDLE hFile) override;
};

#endif // Iron_h__
