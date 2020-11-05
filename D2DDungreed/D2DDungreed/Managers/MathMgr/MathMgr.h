#ifndef __MATH_MGR_H__

class CMathMgr
{
	DECLARE_SINGLETON(CMathMgr)

private:
	CMathMgr();
	~CMathMgr();

public:
	HRESULT	CalculateMove
	(
		D3DXMATRIX&			matWorld,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const	float		fAngle,
		const	bool		bScroll = true
	);
	
	HRESULT CalculateMove
	(
		D3DXMATRIX&			matWorld,
		const D3DXVECTOR3&	vecPos,
		const D3DXVECTOR3&	vecSize,
		const	float		fSelfRotAngle,
		const	float		fRevAngle,
		const D3DXMATRIX&	matParent
	);
	float		ConvertGravity(const GRAVITY_INFO* pInfo);

private:
	void		MakeIdentity();
	void		AssertMember()		const;
	void		InitializeMat();

private:
	D3DXMATRIX		m_matScale;
	D3DXMATRIX		m_matRotate;
	D3DXMATRIX		m_matMove;
	D3DXMATRIX		m_matRevolve;

	const	float	m_fGravity;
};

#define __MATH_MGR_H__
#endif