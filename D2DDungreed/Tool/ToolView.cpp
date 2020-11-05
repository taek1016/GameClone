
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "MainFrm.h"
#include "ToolDoc.h"
#include "ToolView.h"
#include "MiniView.h"
#include "MyForm.h"

#include "../D2DDungreed/Object/UnseenObject/UnseenObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	: m_pTerrain(nullptr)
	, m_pUnseenObject(nullptr)
{
}

CToolView::~CToolView()
{
	CSINGLETON::DestroyManagers();
	SafeDelete(m_pTerrain);
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	D3DXVECTOR3 vPoint =
	{
		static_cast<FLOAT>(CScrollView::GetScrollPos(0)),
		static_cast<FLOAT>(CScrollView::GetScrollPos(1)),
		0.f
	};

	CSINGLETON::pCameraMgr->SetPos(vPoint);

	CSINGLETON::pDirectMgr->Render_Begin();

	m_pTerrain->RenderMapTool();

	m_pTerrain->RenderTileOption();

	CSINGLETON::pDirectMgr->Render_End();

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pFrameWnd->m_SecondSplitter.GetPane(0, 0));
	NULL_CHECK(pMiniView);

	pMiniView->Invalidate(FALSE); // 미니뷰 갱신
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CScrollView::SetScrollSizes(MM_TEXT, CSize(MAX_MAPSIZE_X, MAX_MAPSIZE_Y));

	CMainFrame*	pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	assert(nullptr != pMainFrame);
	NULL_CHECK(pMainFrame);

	RECT rcFrame{};
	pMainFrame->GetWindowRect(&rcFrame);
	::SetRect(&rcFrame, 0, 0, rcFrame.right - rcFrame.left, rcFrame.bottom - rcFrame.top);

	RECT rCScrollView{};

	GetClientRect(&rCScrollView);

	int iGapX = rcFrame.right - rCScrollView.right;
	int iGapY = rcFrame.bottom - rCScrollView.bottom;

	CSINGLETON::SetHWND(m_hWnd);
	CSINGLETON::SetWidth(WINCX);
	CSINGLETON::SetHeight(WINCY);

	CSINGLETON::InitializeManagers();

	CSINGLETON::pCameraMgr->SetClientRS(D3DXVECTOR3(static_cast<FLOAT>(WINCX), static_cast<FLOAT>(WINCY), 0.f));
	CSINGLETON::pCameraMgr->SetWorldRS(D3DXVECTOR3(static_cast<FLOAT>(MAX_MAPSIZE_X), static_cast<FLOAT>(MAX_MAPSIZE_Y), 0.f));
	CSINGLETON::pCameraMgr->SetPivot(D3DXVECTOR3(0.5f, 0.5f, 0.f));

	pMainFrame->SetWindowPos(nullptr, 0, 0, CSINGLETON::GetWidth() + iGapX, CSINGLETON::GetHeight() + iGapY, SWP_NOZORDER | SWP_NOMOVE);

	HRESULT hr = CSINGLETON::pTextureMgr->LoadTexture(
		CSINGLETON::pDirectMgr->GetDevice(),
		TEXTURE_MULTI,
		L"../Texture/Map/Terrain/Ice/%d.png",
		L"Terrain",
		L"Ice",
		47
	);
	assert(NO_ERROR == hr);
	FAILED_CHECK(hr);

	hr = CSINGLETON::pTextureMgr->LoadTexture(
		CSINGLETON::pDirectMgr->GetDevice(),
		TEXTURE_MULTI,
		L"../Texture/Map/Terrain/Town/%d.png",
		L"Terrain",
		L"Town",
		15
	);
	assert(NO_ERROR == hr);
	FAILED_CHECK(hr);

	m_pTerrain = CTerrain::Create();
	assert(nullptr != m_pTerrain);
	NULL_CHECK(m_pTerrain);

	::ShowCursor(true);
}

CTerrain * CToolView::GetTerrain()
{
	return m_pTerrain;
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CSINGLETON::pTimeMgr->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		D3DXVECTOR3 vPoint =
		{
			static_cast<FLOAT>(point.x) + CScrollView::GetScrollPos(0),
			static_cast<FLOAT>(point.y) + CScrollView::GetScrollPos(1),
			0.f
		};
		CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
		NULL_CHECK(pFrameWnd);

		CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
		NULL_CHECK(pFormView);

		m_pTerrain->TileChange(vPoint, pFormView->m_MapTool.m_iDrawID);

		Invalidate(FALSE);
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	D3DXVECTOR3 vPoint =
	{
		static_cast<FLOAT>(point.x) + CScrollView::GetScrollPos(0),
		static_cast<FLOAT>(point.y) + CScrollView::GetScrollPos(1),
		0.f
	};
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pFormView);

	m_pTerrain->TileChange(vPoint, pFormView->m_MapTool.m_iDrawID);

	Invalidate(FALSE);

	CScrollView::OnLButtonDown(nFlags, point);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	D3DXVECTOR3 vPoint =
	{
		static_cast<FLOAT>(point.x) + CScrollView::GetScrollPos(0),
		static_cast<FLOAT>(point.y) + CScrollView::GetScrollPos(1),
		0.f
	};
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pFormView);

	m_pTerrain->TileOptionChange(vPoint);

	Invalidate(FALSE);

	CScrollView::OnRButtonDown(nFlags, point);
}
