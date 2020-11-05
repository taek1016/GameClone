// MiniView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MiniView.h"
#include "ToolView.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
	: m_pTerrain(nullptr)
{
}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	// TODO: 여기에 그리기 코드를 추가합니다.
	CSINGLETON::pDirectMgr->Render_Begin();

	m_pTerrain->MiniRender();
	
	CSINGLETON::pDirectMgr->Render_End(m_hWnd);
}


// CMiniView 진단입니다.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView 메시지 처리기입니다.


void CMiniView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CSplitterWnd* pSplitterWnd = dynamic_cast<CSplitterWnd*>(GetParentSplitter(this, FALSE)->GetParent());
	m_pTerrain = dynamic_cast<CToolView*>(pSplitterWnd->GetPane(0, 1))->GetTerrain();
	m_vecTile = m_pTerrain->GetTerrain();
}