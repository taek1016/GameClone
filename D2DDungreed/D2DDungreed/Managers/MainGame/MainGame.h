#ifndef __MAIN_GAME_H__
#define __MAIN_GAME_H__

class CMainGame
{
	DECLARE_SINGLETON(CMainGame);

private:
	CMainGame();
	virtual ~CMainGame();

public:
	void	Update();
	void	LateUpdate();
	void	Render();

private:
	HRESULT	Initialize();

private:
	int			m_iEvent;
};
#endif // !__MAIN_GAME_H__

