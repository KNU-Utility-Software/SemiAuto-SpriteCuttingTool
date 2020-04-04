
// SpriteToolView.cpp : CSpriteToolView 클래스의 구현
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "SpriteToolDoc.h"
#include "SpriteToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpriteToolView

IMPLEMENT_DYNCREATE(CSpriteToolView, CView)

BEGIN_MESSAGE_MAP(CSpriteToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSpriteToolView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSpriteToolView 생성/소멸

CSpriteToolView::CSpriteToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSpriteToolView::~CSpriteToolView()
{
}

BOOL CSpriteToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSpriteToolView 그리기

void CSpriteToolView::OnDraw(CDC* /*pDC*/)
{
	CSpriteToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CSpriteToolView 인쇄


void CSpriteToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSpriteToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSpriteToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSpriteToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSpriteToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSpriteToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSpriteToolView 진단

#ifdef _DEBUG
void CSpriteToolView::AssertValid() const
{
	CView::AssertValid();
}

void CSpriteToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpriteToolDoc* CSpriteToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpriteToolDoc)));
	return (CSpriteToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CSpriteToolView 메시지 처리기
