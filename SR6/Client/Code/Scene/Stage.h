#ifndef Stage_h__
#define Stage_h__

class CInGameObject;
class CStage : public Engine::CScene
{
private:
	explicit				CStage(void);
	virtual					~CStage(void);

	//CInGameObject*			obj = nullptr;
public:
	virtual HRESULT			Initialize_Scene(void) override;
	virtual Engine::_int	Update_Scene(const Engine::_float & fTimeDelta) override;
	virtual void			Render_Scene(void) override;

private:
	class CHpBar*			m_pBar = nullptr;
	_ulong					m_dwRenderCnt = 0;
	_tchar					m_szFPS[256];
	_float					m_fTime = 0.f;

public:
	static CStage*			Create(void);

private:
	virtual void			freeMem(void) override;
};

#endif // Stage_h__
