#ifndef ToolGuideAxis_h__
#define ToolGuideAxis_h__

#include "Engine_Defines.h"
#include "Base.h"

class CToolGuideAxis : public CBase
{
public:
	enum ACTIVATED_AXIS		{ AXIS_UP, AXIS_RIGHT, AXIS_LOOK, AXIS_END };
	enum POINT				{ START_LINE, END_LINE, POINT_END};
private:
	explicit				CToolGuideAxis(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine);
	virtual					~CToolGuideAxis(void);

public:
	void					KeyInput(void);
	void					Render_Axis(void);

	Engine::_bool			Get_Activated(const ACTIVATED_AXIS& eAxis);
	Engine::_bool			Is_Same(const Engine::_vec3* pPos);
	Engine::_vec3*			Get_CenterPos(void);

	void					Move_Pos(const Engine::_vec3* pDir);

private:
	void					initialize_Pos(Engine::_vec3* pPos);

	LPDIRECT3DDEVICE9		m_pGraphicDev;
	LPD3DXLINE				m_pLine;

	Engine::_vec3*			m_pOriPos;
	Engine::_vec3			m_vAxis[AXIS_END][POINT_END];
	Engine::_bool			m_bActivateAxis[AXIS_END];

	D3DXCOLOR				m_tColor[AXIS_END];

public:
	static CToolGuideAxis*	Create(LPDIRECT3DDEVICE9 pGraphicDev, LPD3DXLINE pLine, Engine::_vec3* pPos);

private:
	inline virtual void		Free(void);
};

#endif // ToolGuideAxis_h__
