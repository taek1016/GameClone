#include "stdafx.h"
#include "Terrain.h"

const int CTerrain::g_TileCountX = static_cast<INT>(MAX_MAPSIZE_X / TILE_SIZE);
const int CTerrain::g_TileCountY = static_cast<INT>(MAX_MAPSIZE_Y / TILE_SIZE);

CTerrain::CTerrain()
	: m_vecTile()

	, m_matScale()
	, m_matMove()
{
}

CTerrain::~CTerrain()
{
	std::for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
	m_vecTile.clear();
}

CTerrain * CTerrain::Create()
{
	CTerrain*	pInstance = new CTerrain;

	pInstance->SetObjectKey(L"Terrain");
	pInstance->SetObjectStatus(L"Ice");
	pInstance->MakeTile();

	return pInstance;
}

CTerrain * CTerrain::Create(const std::wstring& wstrPath)
{
	CTerrain*	pInstance = new CTerrain;

	pInstance->LoadTile(wstrPath.c_str());

	return pInstance;
}

int CTerrain::Update()
{
	return 0;
}

void CTerrain::LateUpdate()
{
}

void CTerrain::Render()
{
	const D3DXVECTOR3& vecPos = CSINGLETON::pCameraMgr->GetPos();

	static const int iMargin = 5;

	int fStartX = static_cast<int>(vecPos.x / TILE_SIZE) - iMargin;
	int fStartY = static_cast<int>(vecPos.y / TILE_SIZE) - iMargin;

	int windowSizeX = static_cast<int>(CSINGLETON::GetWidth() / TILE_SIZE) + iMargin;
	int windowSizeY = static_cast<int>(CSINGLETON::GetHeight() / TILE_SIZE) + iMargin;

	int iIndex = 0;

	for (int i = fStartY; i < windowSizeY + fStartY + iMargin; ++i)
	{
		for (int j = fStartX; j < windowSizeX + fStartX + iMargin; ++j)
		{
			iIndex = j + i * g_TileCountX;

			if (0 > iIndex || iIndex >= static_cast<int>(m_vecTile.size()))
			{
				continue;
			}
			const TEX_INFO* pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo
			(
				m_wStrObjectKey,
				m_wStrObjectStatus,
				m_vecTile[iIndex]->byDrawID
			);
			NULL_CHECK_CONTINUE(pTexInfo);

			CSINGLETON::pMathMgr->CalculateMove
			(
				m_vecTile[iIndex]->matWorld,
				m_vecTile[iIndex]->vPos,
				m_vecTile[iIndex]->vSize,
				0
			);
			int iColor = RENDER_ALL_COLOR;

			CSINGLETON::pDirectMgr->RenderImage(
				pTexInfo,
				m_vecTile[iIndex]->matWorld,
				iColor
			);
		}
	}
}

void CTerrain::MiniRender()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matTrans);

	float scaleX = 1 / 7.f;
	float scaleY = 1 / 10.f;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	D3DXVECTOR3 vecCenter;
	D3DXMATRIX matWorld;
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(m_wStrObjectKey, m_wStrObjectStatus, m_vecTile[i]->byDrawID);
		assert(nullptr != pTexInfo);
		NULL_CHECK_CONTINUE(pTexInfo);

		D3DXMatrixScaling
		(
			&matScale,
			m_vecTile[i]->vSize.x * scaleX,
			m_vecTile[i]->vSize.y * scaleY,
			m_vecTile[i]->vSize.z
		);

		D3DXMatrixTranslation
		(
			&matTrans,
			m_vecTile[i]->vPos.x * scaleX,
			m_vecTile[i]->vPos.y * scaleY,
			m_vecTile[i]->vPos.z
		);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		vecCenter = D3DXVECTOR3(fCenterX, fCenterY, 0.f);
		matWorld = (matScale * matTrans);
		CSINGLETON::pDirectMgr->GetSprite()->SetTransform(&matWorld);
		CSINGLETON::pDirectMgr->GetSprite()->Draw
		(
			pTexInfo->pTexture, 
			nullptr,
			&vecCenter, 
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void CTerrain::RenderMapTool()
{
	const TEX_INFO*	pTexInfo = nullptr;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = CSINGLETON::pTextureMgr->GetTexInfo(
			m_wStrObjectKey,
			m_wStrObjectStatus,
			m_vecTile[i]->byDrawID
		);
		NULL_CHECK_CONTINUE(pTexInfo);

		CSINGLETON::pMathMgr->CalculateMove(
			m_vecTile[i]->matWorld,
			m_vecTile[i]->vPos,
			m_vecTile[i]->vSize,
			0);
		int iColor = D3DCOLOR_ARGB(255, 255, 255, 255);

		CSINGLETON::pDirectMgr->RenderImage(
			pTexInfo,
			m_vecTile[i]->matWorld,
			iColor
		);

		CSINGLETON::pDirectMgr->RenderRect(
			m_vecTile[i]->tRect,
			D3DCOLOR_ARGB(255, 255, 0, 0));
	}
}

void CTerrain::RenderTileOption()
{
	size_t tileSize = m_vecTile.size();
	TCHAR render[MID_STR]{};

	int iColor = 0;

	for (size_t i = 0; i < tileSize; ++i)
	{
		switch (m_vecTile[i]->byOption)
		{
		case NO_COLLIDE:
			swprintf_s(render, L"NO");
			iColor = D3DCOLOR_ARGB(255, 0, 255, 255);
			break;

		case SQUARE_COLLIDE:
			swprintf_s(render, L"SQ");
			iColor = D3DCOLOR_ARGB(255, 255, 255, 0);
			break;

		case UP_TO_DOWN:
			swprintf_s(render, L"UD");
			iColor = D3DCOLOR_ARGB(255, 255, 0, 255);
			break;

		case LEFT_TO_RIGHT_DIAGONAL:
			swprintf_s(render, L"LR");
			iColor = D3DCOLOR_ARGB(255, 130, 130, 0);
			break;

		case RIGHT_TO_LEFT_DIAGONAL:
			swprintf_s(render, L"RL");
			iColor = D3DCOLOR_ARGB(255, 0, 130, 130);
			break;
		}

		D3DXVECTOR3 pos = m_vecTile[i]->vPos;
		pos.x -= 20;
		CSINGLETON::pDirectMgr->RenderFont
		(
			pos - CSINGLETON::pCameraMgr->GetPos(),
			render,
			iColor
		);
	}
}

void CTerrain::TileChange(
	const D3DXVECTOR3&	vPos,
	const BYTE&			byDrawID)
{
	const float fTileSize = TILE_SIZE;

	int i = static_cast<int>(vPos.y / fTileSize);
	int j = static_cast<int>(vPos.x / fTileSize);
	int iIndex = i * g_TileCountX + j;

	if (0 > iIndex || iIndex >= static_cast<int>(m_vecTile.size()))
	{
		return;
	}

	m_vecTile[iIndex]->SetID(byDrawID);
}

void CTerrain::TileOptionChange(const D3DXVECTOR3 & vPos)
{
	const float fTileSize = TILE_SIZE;

	int i = static_cast<int>(vPos.y / fTileSize);
	int j = static_cast<int>(vPos.x / fTileSize);
	int iIndex = i * g_TileCountX + j;

	if (0 > iIndex || iIndex >= static_cast<int>(m_vecTile.size()))
	{
		return;
	}

	switch (m_vecTile[iIndex]->byOption)
	{
	case NO_COLLIDE:
		m_vecTile[iIndex]->SetOption(SQUARE_COLLIDE);
		break;
	case SQUARE_COLLIDE:
		m_vecTile[iIndex]->SetOption(UP_TO_DOWN);
		break;
	case UP_TO_DOWN:
		m_vecTile[iIndex]->SetOption(LEFT_TO_RIGHT_DIAGONAL);
		break;
	case LEFT_TO_RIGHT_DIAGONAL:
		m_vecTile[iIndex]->SetOption(RIGHT_TO_LEFT_DIAGONAL);
		break;
	case RIGHT_TO_LEFT_DIAGONAL:
		m_vecTile[iIndex]->SetOption(NO_COLLIDE);
		break;
	}
}

void CTerrain::MakeTile()
{
	CGameObject::SetObjectKey(L"Terrain");
	CGameObject::SetObjectStatus(L"Ice");

	m_vecTile.reserve(g_TileCountX * g_TileCountY);

	TILE_INFO* pTile = nullptr;
	float fX = 0.f, fY = 0.f;

	// 사이즈만큼 크기를 키워서 넣을 예정.
	const float fSizeX = 1.f;
	const float fSizeY = 1.f;

	for (int i = 0; i < g_TileCountY; ++i)
	{
		for (int j = 0; j < g_TileCountX; ++j)
		{
			fX = j * TILE_SIZE + TILE_SIZE TO_HALF;
			fY = i * TILE_SIZE + TILE_SIZE TO_HALF;

			pTile = new TILE_INFO;
			pTile->SetPos(D3DXVECTOR3(fX, fY, 0.f));
			pTile->SetSize(D3DXVECTOR3(fSizeX, fSizeY, 0.5f));
			pTile->SetID(0);
			pTile->SetOption(TILE_OPTION::NO_COLLIDE);

			m_vecTile.push_back(pTile);
		}
	}

	UpdateRect();
#ifdef _DEBUG
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			assert(0 == m_matMove.m[i][j]);
			assert(0 == m_matScale.m[i][j]);
		}
	}
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		assert(0 == m_vecTile[i]->byDrawID);
	}
#endif // _DEBUG
}

void CTerrain::SaveTile(const TCHAR * pFilePath)
{
	HANDLE	hFile = ::CreateFile(
		pFilePath,
		GENERIC_WRITE,
		0,
		nullptr,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		return;
	}

	DWORD dwBytes = 0;
	size_t iLen = 0;

	// 키 입력
	iLen = m_wStrObjectKey.length() + 1;
	WriteFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);
	WriteFile(hFile, m_wStrObjectKey.c_str(), sizeof(wchar_t) * iLen, &dwBytes, nullptr);

	// 상태 입력
	iLen = m_wStrObjectStatus.length() + 1;
	WriteFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);
	WriteFile(hFile, m_wStrObjectStatus.c_str(), sizeof(wchar_t) * iLen, &dwBytes, nullptr);

	// 타일 입력
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		WriteFile(hFile, m_vecTile[i], sizeof(TILE_INFO), &dwBytes, nullptr);
	}

	CloseHandle(hFile);
}

void CTerrain::LoadTile(const TCHAR * pFilePath)
{
	HANDLE hFile = ::CreateFile(pFilePath, GENERIC_READ, 0, nullptr,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return;

	if (!m_vecTile.empty())
	{
		for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
		m_vecTile.clear();
	}

	DWORD dwBytes = 0;
	size_t iLen = 0;
	wchar_t* pString = nullptr;
	TILE_INFO tTile = {};

	// 키 길이 입력받기
	ReadFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);

	// 키 입력받기
	pString = new wchar_t[iLen];
	ReadFile(hFile, pString, sizeof(wchar_t) * iLen, &dwBytes, nullptr);
	CGameObject::SetObjectKey(pString);
	SafeDelete_Array(pString);

	// 상태 길이 입력받기
	ReadFile(hFile, &iLen, sizeof(size_t), &dwBytes, nullptr);

	// 상태 입력받기
	pString = new wchar_t[iLen];
	ReadFile(hFile, pString, sizeof(wchar_t) * iLen, &dwBytes, nullptr);
	CGameObject::SetObjectStatus(pString);
	SafeDelete_Array(pString);

	while (true)
	{
		ReadFile(hFile, &tTile, sizeof(TILE_INFO), &dwBytes, nullptr);

		if (0 == dwBytes)
			break;

		m_vecTile.push_back(new TILE_INFO(tTile));
	}

	UpdateRect();

	CloseHandle(hFile);
}

int CTerrain::FindTile(const D3DXVECTOR3 & vecPos)
{
	const float fTileSize = TILE_SIZE;

	int i = static_cast<int>(vecPos.y / fTileSize);
	int j = static_cast<int>(vecPos.x / fTileSize);
	int iIndex = i * g_TileCountX + j;

	if (0 > iIndex || iIndex >= static_cast<int>(m_vecTile.size()))
	{
		return -1;
	}

	return iIndex;
}

void CTerrain::UpdateRect()
{
	size_t tileCount = m_vecTile.size();

	for (size_t i = 0; i < tileCount; ++i)
	{
		m_vecTile[i]->tRect.left	= static_cast<LONG>(m_vecTile[i]->vPos.x - TILE_SIZE TO_HALF);
		m_vecTile[i]->tRect.top		= static_cast<LONG>(m_vecTile[i]->vPos.y - TILE_SIZE TO_HALF);
									  
		m_vecTile[i]->tRect.right	= static_cast<LONG>(m_vecTile[i]->tRect.left + TILE_SIZE);
		m_vecTile[i]->tRect.bottom	= static_cast<LONG>(m_vecTile[i]->tRect.top + TILE_SIZE);
	}
}