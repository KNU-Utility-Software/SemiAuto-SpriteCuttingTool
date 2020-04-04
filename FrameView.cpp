// FrameView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "FrameView.h"
#include "SpriteInfo.h"
#include "FrameInfo.h"
#include "MainFrm.h"
#include "ControlView.h"

// CFrameView

IMPLEMENT_DYNCREATE(CFrameView, CScrollView)

CFrameView::CFrameView()
	: m_pSeletedSprite(NULL),
	m_frame_index(-1)
{

}

CFrameView::~CFrameView()
{
}

void CFrameView::SetSpritInfo(CSpriteInfo* pSpriteInfo)
{
	m_pSeletedSprite = pSpriteInfo;

	Invalidate(TRUE);
}


BEGIN_MESSAGE_MAP(CFrameView, CScrollView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFrameView 그리기입니다.

void CFrameView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CFrameView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	if (!m_pSeletedSprite)
		return;

	// 프레임 정보 출력
	CImage* pImage = m_pSeletedSprite->GetImage();

	if (!pImage)
		return;

	VEC_FRAMEINFO& vecFrameInfo = m_pSeletedSprite->GetFrameInfoList();
	int width = 0;
	int height = 0;
	VEC_FRAMEINFO_ITER iter = vecFrameInfo.begin();
	for ( int i = 0; iter != vecFrameInfo.end(); ++iter, i++)
	{
		FRAME_INFO* pFrame = *iter;
		pImage->BitBlt(pDC->m_hDC, 
			LEFT_MARGIN + width, 
			TOP_MARGIN, 
			pFrame->rect.Width(), 
			pFrame->rect.Height(), 
			pFrame->rect.left, 
			pFrame->rect.top, 
			SRCCOPY);

		WCHAR strTmp[20];
		_itow_s(i, strTmp, 10);
		pDC->TextOut(LEFT_MARGIN + width, TOP_MARGIN + pFrame->rect.Height() + 2, strTmp);

		width += pFrame->rect.Width() + LEFT_MARGIN;
		height = max(height, pFrame->rect.Height()); 
	}

	// 스크롤바
	CSize size(LEFT_MARGIN + width, TOP_MARGIN + height + TOP_MARGIN);
	SetScrollSizes(MM_TEXT, size);
}


// CFrameView 진단입니다.

#ifdef _DEBUG
void CFrameView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CFrameView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFrameView 메시지 처리기입니다.

int CFrameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return 0;
}

int CFrameView::GetFrameIndex(CPoint point)
{
	if (!m_pSeletedSprite)
		return -1;

	VEC_FRAMEINFO& vecFrameInfo = m_pSeletedSprite->GetFrameInfoList();

	int width = 0;
	int height = 0;
	VEC_FRAMEINFO_ITER iter = vecFrameInfo.begin();
	for ( int i = 0; iter != vecFrameInfo.end(); ++iter, i++)
	{
		FRAME_INFO* pFrame = *iter;
		if(
			(LEFT_MARGIN + width < point.x)&&
			(TOP_MARGIN < point.y)&&
			(point.x < (LEFT_MARGIN + width+ pFrame->rect.Width()))&&
			(point.y < ( TOP_MARGIN + pFrame->rect.Height() )))
		{
			return i;
		}

		width += pFrame->rect.Width() + LEFT_MARGIN;
		height = max(height, pFrame->rect.Height()); 
	}

	return -1;
}

void CFrameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pt;
	pt.x = point.x + GetScrollPos(SB_HORZ);
	pt.y = point.y + GetScrollPos(SB_VERT);

	m_frame_index = GetFrameIndex(pt);
	if(m_frame_index == -1)
		return;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame == NULL)
		return;

	pMainFrame->GetControlView()->SetFrameIndex(m_frame_index);

	if (!m_pSeletedSprite)
		return;

	VEC_FRAMEINFO& vecFrameInfo = m_pSeletedSprite->GetFrameInfoList();

	pMainFrame->GetControlView()->SetEditFrame(vecFrameInfo[m_frame_index]->name);
}

void CFrameView::SetFrameName(wchar_t* str_frame_name)
{
	if (!m_pSeletedSprite)
		return ;

	VEC_FRAMEINFO& vecFrameInfo = m_pSeletedSprite->GetFrameInfoList();

	wcscpy_s(vecFrameInfo[m_frame_index]->name,str_frame_name);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if(pMainFrame == NULL)
		return;

	pMainFrame->GetControlView()->SetFrameIndex(m_frame_index);
}