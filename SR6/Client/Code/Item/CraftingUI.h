#ifndef CraftingUI_h__
#define CraftingUI_h__

class CCraftingUI : public Engine::CGameObject
{
private:
	explicit				CCraftingUI(void);
	virtual					~CCraftingUI(void);

public:
	Engine::_int			Update_GameObject(const _float& fTimeDelta) override;
	void					Render_GameObject() override;
	void					Set_Init();

	HRESULT					Initialize_GameObject();

	Engine::_bool			Get_Finish(void) { return m_bFinished; }

private:
	Engine::CTexture*		m_pTexture = nullptr;

	Engine::_bool			m_bFinished = false;
	Engine::_bool			m_bActivate = false;
	Engine::_float			m_fCurPercent = 0.f;
	_vec3					m_vScale;
	_vec3					m_vPos;

	_matrix					m_matBase;
	_matrix					m_matBar;

public:
	static CCraftingUI*		Create(void);
	virtual CGameObject*	Clone(const _vec3* pPos = nullptr);

private:
	virtual void				LoadData(HANDLE hFile) { ; }
};
#endif // CraftingUI_h__
