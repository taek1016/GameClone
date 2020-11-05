#ifndef SkyBox_h__
#define SkyBox_h__

#include "Engine_Defines.h"
#include "GameObject.h"

class CSkyBox : public Engine::CGameObject
{
private:
	explicit				CSkyBox(void);
	virtual					~CSkyBox(void);

public:
	virtual HRESULT			Initialize_GameObject() override;
	virtual Engine::_int	Update_GameObject(const _float& fTimeDelta) override;
	virtual void			Render_GameObject() override;

private:
	Engine::CCubeTex*		m_pBufferCom = nullptr;
	Engine::CTexture*		m_pTextureCom = nullptr;
	Engine::CTransform*		m_pTransformCom = nullptr;

	_vec3					m_vDir;
	_float					m_fSpeed = 20.f;

public:
	static CSkyBox*			Create(void);

private:
	virtual void			LoadData(HANDLE hFile) override { }
	virtual CGameObject*	Clone(const _vec3 * pPos = nullptr) override { return nullptr; }

};

#endif // SkyBox_h__
