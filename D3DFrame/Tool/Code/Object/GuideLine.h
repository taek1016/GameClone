#ifndef GuideLine_h__
#define GuideLine_h__

#include "Engine_Defines.h"
#include "ToolGameObject.h"

class CGuideLine : public CToolGameObject
{
private:
	explicit				CGuideLine(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine,const Engine::_float& fLineLength);
	virtual					~CGuideLine(void);

public:
	virtual HRESULT			Initialize_GameObject(void);
	virtual HRESULT			Late_Initialize(void);

	virtual Engine::_int	Update_GameObject(const Engine::_float& fTimeDelta);
	virtual void			Render_GameObject(void);

private:
	Engine::_vec3			m_vLine[3][2];
	D3DXCOLOR				m_tColor[3];
	LPD3DXLINE				m_pLine;

public:
	static CGuideLine*		Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, const Engine::_float fLength = 1.f);
	virtual CGameObject*	Clone(void);
	virtual void			SaveData(HANDLE hFile);
	virtual void			LoadData(HANDLE hFile);

private:
	inline virtual void		Free(void) override;
};

#endif // GuideLine_h__
