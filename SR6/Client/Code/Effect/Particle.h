#ifndef Effect_h__
#define Effect_h__

#include "InGameObject.h"

class CParticle : public CInGameObject
{
protected:
	explicit CParticle();
	explicit CParticle(const CParticle& rhs);

	virtual ~CParticle();
protected:
	Engine::_vec3					m_vEmitPoint;

	Engine::_float					m_fEmitRate;
	Engine::_float					m_fSize;
	
	Engine::_int					m_iMaxParticle;

	LPDIRECT3DTEXTURE9				m_pTexture = nullptr;
	LPDIRECT3DVERTEXBUFFER9			m_pVB = nullptr;
	list<Engine::PARTICLEATTRIBUTE> m_ltParticles;

	bool							m_bIsRunning = false;

	DWORD							m_dwVBSize;
	DWORD							m_dwVBOffset;
	DWORD							m_dwVBBatchSize;
public:
	virtual HRESULT					Initialize_GameObject()override;
	virtual void					Reset_Particle(Engine::PARTICLEATTRIBUTE* pAtt);
	virtual void					Reset_AllParticles();
	virtual void					Add_Particle();

	virtual void					Render_GameObject()override;

	virtual void					Pre_Render();
	virtual void					Post_Render();

	void							Clear_DeadParticles();

	bool							IsRunning() { return m_bIsRunning; }

	void							SetEmitPoint(_vec3 ep) { m_vEmitPoint = ep; }

	DWORD							FtoW(float f) { return *((DWORD*)&f); }

	Engine::_float					Get_RandomFloat(Engine::_float fRandMin, Engine::_float fRandMax);
	Engine::_vec3					Get_RandomVec3(Engine::_vec3 vMin, Engine::_vec3 vMax);
};

#endif