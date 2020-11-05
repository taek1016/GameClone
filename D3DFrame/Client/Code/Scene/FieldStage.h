#ifndef FieldStage_h__
#define FieldStage_h__

#include "Scene.h"

class CFieldStage : public Engine::CScene
{
	enum BGM_ENUM			{ BGM_BOAR, BGM_KODOBEAST, BGM_NEFARIAN ,BGM_END };
private:
	explicit				CFieldStage(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual					~CFieldStage(void);

public:
	virtual HRESULT			Initialize_Scene(void);
	virtual Engine::_int	Update_Scene(const Engine::_float& fTimeDelta);
	virtual void			Render_Scene(void);

private:
	void					play_BGM(const Engine::_float& fTimeDelta);

	void					setUp_Camera(void);
	void					initialize_UI(void);
	HRESULT					initialize_StageLight(void);

	class CLoading*			m_pLoading;

	const Engine::_tchar*	m_pBGMStr;
	Engine::_float			m_fBGMVolume;
	BGM_ENUM				m_eCurBGM;

public:
	static CFieldStage*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void			Free(void) override;
};

#endif // FieldStage_h__
