#ifndef __MENU_LOGO_H__
#define __MENU_LOGO_H__

#include "Scene.h"

class CMyButton;
class CMyLayer;
class CMoveBackgroundObject;

class CMenu : public CScene
{
private:
	CMenu();

public:
	virtual ~CMenu();

	// CScene을(를) 통해 상속됨
public:
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render() override;

	static	CMenu*	Create();

private:
	virtual HRESULT Initialize() override;
	virtual void	Release() override;

	void			UpdateButton();
	void			UpdateLayer();

	void			MoveLayerTo(
		CGameObject* pObj,
		const D3DXVECTOR3& vecPos,
		const bool bLeft = true);

private:
	CMyButton*				m_cExitButton;
	CMyButton*				m_cPlayButton;

	CMyLayer*				m_cFrontLayerFront;
	CMyLayer*				m_cFrontLayerBack;

	CMyLayer*				m_cMiddleCloud;

	CMyLayer*				m_cBackLayerFront;
	CMyLayer*				m_cBackLayerBack;

	CMoveBackgroundObject*	m_cBird;
	CMoveBackgroundObject**	m_cGroupBird;
};

#endif // !__MENU_LOGO_H__
