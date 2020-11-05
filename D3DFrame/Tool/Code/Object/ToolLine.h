#ifndef Line_h__
#define Line_h__

#include "Engine_Defines.h"
#include "Base.h"

class CToolLine
{
public:
	enum LINE_POS		{ LINE_START, LINE_DEST, LINE_END };


private:
	explicit			CToolLine(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine);

public:
	virtual				~CToolLine(void);

public:
	void				Update(const Engine::_float& fTimeDelta);
	void				Render(void);

	const Engine::_vec3	Get_Line(void);

private:
	void				set_Vec2ToVec3(const LINE_POS ePos, const Engine::_vec2* pPos);

	HRESULT				initialize_Line(const Engine::_vec2* pStart, const Engine::_vec2* pEnd);
	Engine::_vec3		m_vPos[LINE_END];
	D3DXCOLOR			m_tColor;

	LPD3DXLINE			m_pLine;
	LPDIRECT3DDEVICE9	m_pGraphicDev;

public:
	static CToolLine*	Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, const Engine::_vec2* pStart, const Engine::_vec2* pEnd);
};

#endif // Line_h__
