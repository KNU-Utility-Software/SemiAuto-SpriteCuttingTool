// ImageView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "ImageView.h"
#include "SpriteManager.h"
#include "MainFrm.h"
#include "ControlView.h"

// CImageView

IMPLEMENT_DYNCREATE(CImageView, CScrollView)

CImageView::CImageView()
	: m_startPoint(0, 0)
	, m_endPoint(0, 0)
	, m_bMouseDown(false)
	, m_ColorKey(RGB(255,255,255))
	, m_bDrawSelect(false)
	, m_pSelectedImage(NULL)
	, m_iZoomRate(1)
	, m_ChangeCursor(FALSE)
{

}

CImageView::~CImageView()
{
}

void CImageView::SetSelectInfo(CPoint start, CPoint end)
{
	m_startPoint = start;
	m_endPoint = end;
	Invalidate(FALSE);
}

void CImageView::SetSelectImage(LPWSTR strName)
{
	if (!strName)
		m_pSelectedImage = NULL;
	else
		m_pSelectedImage = CSpriteManager::GetInstance()->GetImage(strName);

	if (m_pSelectedImage)
	{
		CSize sizeTotal;
		sizeTotal.cx = m_pSelectedImage->GetWidth()*m_iZoomRate;
		sizeTotal.cy = m_pSelectedImage->GetHeight()*m_iZoomRate;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

	Invalidate(TRUE);
	m_bDrawSelect = false;
}

BEGIN_MESSAGE_MAP(CImageView, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CImageView 그리기입니다.

void CImageView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
}

void CImageView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType,cx,cy);
}

void CImageView::ZoomIn()
{
	if (!m_pSelectedImage)
		return;

	m_iZoomRate += 1;

	Invalidate(TRUE);
}

void CImageView::ZoomOut()
{
	if (!m_pSelectedImage)
		return;

	if(m_iZoomRate > 1)
	{
		m_iZoomRate -= 1;
	}

	Invalidate(TRUE);
}

void CImageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	
	if (!m_pSelectedImage)
		return;

	if (m_pSelectedImage->IsNull())
		return;

	//m_pSelectedImage->BitBlt(pDC->m_hDC, 0, 0);

	int dest_w = m_pSelectedImage->GetWidth()*m_iZoomRate;
	int dest_h = m_pSelectedImage->GetHeight()*m_iZoomRate;
	CRect rtDest(0,0,dest_w, dest_h);

	int w = m_pSelectedImage->GetWidth();
	int h = m_pSelectedImage->GetHeight();
	CRect rtSrc(0,0,w, h);

	 m_pSelectedImage->AlphaBlend(pDC->m_hDC,rtDest,rtSrc);
	//m_pSelectedImage->TransparentBlt(pDC->m_hDC,rtDest,rtSrc,RGB(0,0,0));

	if (m_bDrawSelect)
	{
		//pDC->SetROP2(R2_NOT);
		HBRUSH oldBrush = (HBRUSH)pDC->SelectObject(GetStockObject(NULL_BRUSH));

		int scale_start_x = m_startPoint.x * m_iZoomRate;
		int scale_start_y = m_startPoint.y * m_iZoomRate;
		int scale_end_x = m_endPoint.x * m_iZoomRate;
		int scale_end_y = m_endPoint.y * m_iZoomRate;

		pDC->Rectangle(scale_start_x, scale_start_y, scale_end_x, scale_end_y);
		pDC->SelectObject(oldBrush);
	}

	CSize sizeTotal;
	sizeTotal.cx = m_pSelectedImage->GetWidth()*m_iZoomRate;
	sizeTotal.cy = m_pSelectedImage->GetHeight()*m_iZoomRate;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageView 진단입니다.

#ifdef _DEBUG
void CImageView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CImageView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CImageView 메시지 처리기입니다.

void CImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPoint newPoint = point + GetScrollPosition();
	
	m_bMouseDown = true;
	m_startPoint = newPoint;
	m_endPoint = newPoint;

	Invalidate(TRUE);

	// 컬러키 선택
	//if (m_pSelectedImage && !m_pSelectedImage->IsNull())
	//{
	//	if (newPoint.x <= m_pSelectedImage->GetWidth() &&
	//		newPoint.y <= m_pSelectedImage->GetHeight())
	//	{
	//		m_ColorKey = m_pSelectedImage->GetPixel(newPoint.x, newPoint.y);
	//	}
	//}

	CScrollView::OnLButtonDown(nFlags, point);
}

void CImageView::CalcFrameRect()
{
	if(m_pSelectedImage == NULL)
		return;

	m_vecPixel.clear();

	while(true)
	{
		PIXEL_INFO start_pixel = SetupStartPoint();
		if(start_pixel.color == RGB(0,0,0))
			break;

		int width = MoveWidth(start_pixel);
		int height = MoveHeight(start_pixel);
		start_pixel.size.x = width;
		start_pixel.size.y = height;
		m_vecPixel.push_back(start_pixel);

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CPoint start(start_pixel.pt.x,start_pixel.pt.y);
		CPoint end(start_pixel.pt.x+width,start_pixel.pt.y+height);

		pMainFrame->GetControlView()->SetSelectInfo(start,end);
		pMainFrame->GetControlView()->OnBnClickedButtonSelectAdd();
	}
}

PIXEL_INFO CImageView::SetupStartPoint()
{
	PIXEL_INFO pixel_info;
	for(int h = 0; h < m_pSelectedImage->GetHeight(); h++)
	{
		for(int w = 0; w < m_pSelectedImage->GetWidth(); w++)
		{
			COLORREF spot_color = m_pSelectedImage->GetPixel(w, h);

			if(spot_color == RGB(0,0,0) || spot_color == RGB(255,255,255))
				continue;

			//if(IgnorSelectedColor(spot_color) == true)
			//{
			//	pixel_info.pt = CPoint(w,h);
			//	CPoint size = GetColorRect(pixel_info.color);
			//	pixel_info.pt.x += size.x;
			//	w += size.x;
			//}

			if(IgnorSelectedColor(spot_color) == false)
			{
				pixel_info.pt = CPoint(w,h);
				pixel_info.color = spot_color;
				return pixel_info;
			}
		}
	}

	pixel_info.color = RGB(0,0,0);
	return pixel_info;
}

CPoint CImageView::GetColorRect(COLORREF _color)
{
	for(int i = 0; i < (int)m_vecPixel.size(); i++)
	{
		if(m_vecPixel[i].color == _color)
		{
			return m_vecPixel[i].size;
		}
	}

	return 0;
}

bool CImageView::IgnorSelectedColor(COLORREF _color)
{
	for(int i = 0; i < (int)m_vecPixel.size(); i++)
	{
		if(m_vecPixel[i].color == _color)
			return true;
	}

	return false;
}

int CImageView::MoveWidth(PIXEL_INFO start_pixel)
{
	for(int w = start_pixel.pt.x; w < m_pSelectedImage->GetWidth(); w++)
	{
		COLORREF spot_color = m_pSelectedImage->GetPixel(w, start_pixel.pt.y);
		if(start_pixel.color != spot_color)
		{
			return (w- start_pixel.pt.x);
		}
	}

	return 0;
}

int CImageView::MoveHeight(PIXEL_INFO start_pixel)
{
	for(int h = start_pixel.pt.y; h < m_pSelectedImage->GetHeight(); h++)
	{
		COLORREF spot_color = m_pSelectedImage->GetPixel(start_pixel.pt.x,h);
		if(start_pixel.color != spot_color)
		{
			return (h - start_pixel.pt.y);
		}
	}

	return 0;
}

void CImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	 //TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_bMouseDown)
		{
			static CPoint start_pt; 

			if(m_ChangeCursor == FALSE)
			{
				start_pt = point;
			}
			m_ChangeCursor = TRUE;

			SetScrollPos(SB_HORZ,(int)((point.x-start_pt.x)*m_iZoomRate*0.3f + (int)GetScrollPosition().x));
			SetScrollPos(SB_VERT,(int)((point.y-start_pt.y)*m_iZoomRate*0.3f + (int)GetScrollPosition().y));

			Invalidate(false);
			return;
		}
	}
	m_ChangeCursor = FALSE;


	if (m_bMouseDown)
	{

		CPoint start = m_startPoint - GetScrollPosition();
		CPoint end = m_endPoint - GetScrollPosition();
		
		CDC* pDc = GetDC();
		if(pDc == NULL)
			return;

		pDc->SetROP2(R2_NOT);
		HBRUSH oldBrush = (HBRUSH)pDc->SelectObject(GetStockObject(NULL_BRUSH));
		pDc->Rectangle(start.x, start.y, end.x, end.y);

		pDc->Rectangle(start.x, start.y, point.x, point.y);
		m_endPoint = point + GetScrollPosition();

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		if(pMainFrame == NULL)
			return;

		pMainFrame->GetControlView()->SetRectInfo((int)abs(end.x - start.x), (int)abs(end.y - start.y));

		pDc->SelectObject(oldBrush);
		ReleaseDC(pDc);
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_bMouseDown = false;

	//if (CalcRect())
	{
		m_bDrawSelect = true;

		// 컨트롤뷰에 선택영역 정보 갱신
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

		POINT scale_start = m_startPoint;
		scale_start.x = m_startPoint.x / m_iZoomRate;
		scale_start.y = m_startPoint.y / m_iZoomRate;
		POINT scale_end = m_endPoint;
		scale_end.x = m_endPoint.x / m_iZoomRate;
		scale_end.y = m_endPoint.y / m_iZoomRate;

		if(scale_start.x > scale_end.x)
		{
			int temp = scale_start.x;
			scale_start.x = scale_end.x;
			scale_end.x = temp;
		}

		if(scale_start.y > scale_end.y)
		{
			int temp = scale_start.y;
			scale_start.y = scale_end.y;
			scale_end.y = temp;
		}

		pMainFrame->GetControlView()->SetSelectInfo(scale_start, scale_end);

		Invalidate(true);
	}

	CScrollView::OnLButtonUp(nFlags, point);
}

bool CImageView::CalcRect()
{
	if (!m_pSelectedImage)
		return false;

	if (m_pSelectedImage->IsNull())
		return false;

	if (m_startPoint == m_endPoint)
		return false;

	m_startPoint.x = min(m_startPoint.x, m_pSelectedImage->GetWidth()-1);
	m_endPoint.x = min(m_endPoint.x, m_pSelectedImage->GetWidth()-1);
	m_startPoint.y = min(m_startPoint.y, m_pSelectedImage->GetHeight()-1);
	m_endPoint.y = min(m_endPoint.y, m_pSelectedImage->GetHeight()-1);

	int left, right, top, bottom;
	left = min(m_startPoint.x, m_endPoint.x);
	right = max(m_startPoint.x, m_endPoint.x);
	top = min(m_startPoint.y, m_endPoint.y);
	bottom = max(m_startPoint.y, m_endPoint.y);

	// 좌
	bool bCheck = false;
	for (int x = left; x <= right; x++)
	{
		for (int y = top; y <= bottom; y++)
		{
			if (m_ColorKey != m_pSelectedImage->GetPixel(x, y))
			{
				left = x;
				bCheck = true;
				break;
			}
		}

		if (bCheck)
			break;
	}

	// 우
	bCheck = false;
	for (int x = right; x >= left; x--)
	{
		for (int y = top; y <= bottom; y++)
		{
			if (m_ColorKey != m_pSelectedImage->GetPixel(x, y))
			{
				right = x;
				bCheck = true;
				break;
			}
		}

		if (bCheck)
			break;
	}

	// 상
	bCheck = false;
	for (int y = top; y <= bottom; y++)
	{
		for (int x = left; x <= right; x++)
		{
			if (m_ColorKey != m_pSelectedImage->GetPixel(x, y))
			{
				top = y;
				bCheck = true;
				break;
			}
		}

		if (bCheck)
			break;
	}

	// 하
	bCheck = false;
	for (int y = bottom; y >= top; y--)
	{
		for (int x = left; x <= right; x++)
		{
			if (m_ColorKey != m_pSelectedImage->GetPixel(x, y))
			{
				bottom = y;
				bCheck = true;
				break;
			}
		}

		if (bCheck)
			break;
	}

	// 선택 박스를 새로 그린다.
	m_startPoint.x = left;
	m_startPoint.y = top;
	m_endPoint.x = right+1;
	m_endPoint.y = bottom+1;

	Invalidate(FALSE);

	return true;
}

int CImageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CSize sizeTotal;
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	return 0;
}


BOOL CImageView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ( m_ChangeCursor )
    {
        ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_HAND));
        return TRUE;
    }

	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}


void CImageView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(nChar)
	{
	case VK_UP:
		SetScrollPos(SB_VERT,( -1 + (int)GetScrollPosition().y)*m_iZoomRate);
		break;
	case VK_DOWN:
		SetScrollPos(SB_VERT,( 1 + (int)GetScrollPosition().y)*m_iZoomRate);
		break;
	case VK_LEFT:
		SetScrollPos(SB_HORZ,( -1 + (int)GetScrollPosition().x)*m_iZoomRate);
		break;
	case VK_RIGHT:
		SetScrollPos(SB_HORZ,( 1 + (int)GetScrollPosition().x)*m_iZoomRate);
		break;
	}

	Invalidate(FALSE);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
