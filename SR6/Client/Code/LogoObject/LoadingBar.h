#ifndef LoadingBar_h__
#define LoadingBar_h__

#include "GameObject.h"
#include "UI/UIBase.h"

class CLoading;
class CLoadBar : public CUIBase
{
private:
	explicit						CLoadBar();
	virtual							~CLoadBar();

public:
	virtual HRESULT					Late_Initialize();
	virtual Engine::_int			Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void					Render_GameObject();

private:
	_matrix							m_matBaseWorld;

	_matrix							m_matBarTranslate;
	_matrix							m_matBarScale;

	_vec3							m_vScale;
	_vec3							m_vPos;

	CLoading*						m_pLoading = nullptr;
	Engine::CTexture*				m_pTexture = nullptr;

public:
	static	CLoadBar*				Create(CLoading* pLoading);
	virtual void					LoadData(HANDLE hFile) override;
	virtual Engine::CGameObject*	Clone(const Engine::_vec3 * pPos = nullptr) override;
};

#endif // LoadingBar_h__
