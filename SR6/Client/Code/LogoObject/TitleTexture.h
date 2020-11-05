#ifndef TitleTexture_h__
#define TitleTexture_h__

#include "GameObject.h"

class CTitleText : public Engine::CGameObject
{
private:
	explicit			CTitleText(void);
	virtual				~CTitleText(void);

public:
	HRESULT				Late_Initialize() override;
	HRESULT				Initialize_GameObject() override;
	Engine::_int		Update_GameObject(const _float& fTimeDelta) override;
	void				Render_GameObject() override;

private:
	Engine::CTexture*	m_pTexture = nullptr;
	Engine::CTransform*	m_pTransform = nullptr;

	_vec3				m_vScale;
	_vec3				m_vPos;

	Engine::_float		m_fCurTime = 0.f;
	Engine::_float		m_fChangeTime = 2.f;

	Engine::_bool		m_bPlusScale = false;

public:
	static CTitleText*	Create(void);

private:
	virtual void LoadData(HANDLE hFile) override;
	virtual CGameObject * Clone(const _vec3 * pPos = nullptr) override;

};

#endif // TitleTexture_h__
