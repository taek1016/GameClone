#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagGravityInfo
{
	float	fPower;
	float	fAcc;

	inline void	SetPower(const float& fValue)	{ fPower = fValue; }
	inline void	SetAcc	(const float& fValue)	{ fAcc = fValue; }
	inline void	SetInitial()					{ fPower = 0.f; fAcc = 0.f; }
}GRAVITY_INFO;

typedef struct tagObjectInfo
{
	D3DXVECTOR3		vPos;		// 위치벡터
	D3DXVECTOR3		vSize;		// 스케일 행렬에 사용할 수 있음.
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vDir;
	D3DXMATRIX		matWorld ;	// 월드행렬

	int				iColorValue;

	inline void	SetPos(const D3DXVECTOR3& vecPos)	{ vPos = vecPos; }
	inline void	SetSize(const D3DXVECTOR3& vecSize)	{ vSize = vecSize; }
	inline void	SetLook(const D3DXVECTOR3& vecLook)	{ vLook = vecLook; }
	inline void	SetDir(const D3DXVECTOR3& vecDir)	{ vDir = vecDir; }
	inline void	SetColor(const int iColor)			{ iColorValue = iColor; }
	inline void SetWorldMatrix(const D3DXMATRIX& mat)
	{
		matWorld = mat;
	}
	inline void	SetInitial()
	{
		SetPos(D3DXVECTOR3(0.f, 0.f, 0.f));
		SetSize(D3DXVECTOR3(0.f, 0.f, 0.f));
		SetLook(D3DXVECTOR3(0.f, 0.f, 0.f));
		SetDir(D3DXVECTOR3(0.f, 0.f, 0.f));
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				matWorld.m[i][j] = 0;
			}
		}
		SetColor(0);
	}

}OBJECT_INFO;

typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9	pTexture;
	D3DXIMAGE_INFO		tImgInfo;
}TEX_INFO;

typedef struct tagTileInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vSize;
	D3DXMATRIX		matWorld;
	BYTE			byDrawID;
	TILE_OPTION		byOption;
	RECT			tRect;

	void SetPos		(const D3DXVECTOR3& vecPos)	 { vPos = vecPos; }
	void SetSize	(const D3DXVECTOR3& vecSize) { vSize = vecSize; }
	void SetID		(const BYTE& byID)			 { byDrawID = byID; }
	void SetOption	(const TILE_OPTION& byValue) { byOption = byValue; }
	void SetRect	(const RECT& rcValue)		 { ::SetRect(&tRect, rcValue.left, rcValue.top, rcValue.right, rcValue.bottom); }
	void SetWorld	(const D3DXMATRIX& mat)		 { matWorld = mat; }
	void SetInitial	()
	{
		vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		vSize = D3DXVECTOR3(0.f, 0.f, 0.f);
		byDrawID = 0;
		byOption = TILE_OPTION::TILE_OPTION_END;
		::SetRect(&tRect, 0, 0, 0, 0);
	}
}TILE_INFO;

typedef	struct tagFrame
{
	float	fCurFrame;
	float	fMaxFrame;

	void	SetCurFrame(float fCur) { fCurFrame = fCur; }
	void	SetMaxFrame(float fMax) { fMaxFrame = fMax; }
	void	SetInitial()			{ fMaxFrame = 0.f; fCurFrame = 0.f; }
}FRAME;

typedef struct tagCount
{
	int		iCurCount;
	int		iMaxCount;
	bool	bIsAction;

	void	SetCurCount(int iCur)	{ iCurCount = iCur;	}
	void	SetMaxCount(int iMax)	{ iMaxCount = iMax; }
	void	SetAction(bool bAction) { bIsAction = bAction; }
	void	SetInitial()			{ iCurCount = 0; iMaxCount = 0; bIsAction = false; }
}COUNT;

typedef struct tagPathInfo
{
	std::wstring	wstrObjectKey;
	std::wstring	wstrStateKey;
	std::wstring	wstrRelative;
	int				iImgCount;
}PATH_INFO;

#endif // !__STRUCT_H__