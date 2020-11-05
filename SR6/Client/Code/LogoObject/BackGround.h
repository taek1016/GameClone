#ifndef BackGround_h__
#define BackGround_h__

#include "GameObject.h"

class CBackGround : public Engine::CGameObject
{
private:
	explicit				CBackGround(void);
	virtual					~CBackGround(void);

public:
	virtual HRESULT			Initialize_GameObject(void) override;
	virtual _int			Update_GameObject(const _float& fTimeDelta) override;
	virtual void			Render_GameObject(void) override;

private:
	void					SetKey(const wstring& wStrKey);

	Engine::CTransform*		m_pTransformCom = nullptr;

	wstring					m_wStrKey;

public:
	static CBackGround*		Create(const wstring& wstrKey);

private:
	virtual void			freeMem(void) override;
	virtual void			LoadData(HANDLE hFile) override;
	virtual CGameObject*	Clone(const _vec3 * pPos = nullptr) override;
};
#endif // BackGround_h__
