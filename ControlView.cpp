// ControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "ControlView.h"
#include "MainFrm.h"
#include "ImageView.h"
#include "SpriteManager.h"
#include "SpriteInfo.h"
#include "FrameInfo.h"
#include "FrameView.h"
#include "AnimView.h"
#include "RectProcessing.h"
// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(CControlView::IDD)
{

}

CControlView::~CControlView()
{
}

void CControlView::SetSelectInfo(CPoint start, CPoint end)
{
	SetDlgItemInt(IDC_EDIT_SELECT_LEFT, start.x);
	SetDlgItemInt(IDC_EDIT_SELECT_TOP, start.y);
	SetDlgItemInt(IDC_EDIT_SELECT_RIGHT, end.x);
	SetDlgItemInt(IDC_EDIT_SELECT_BOTTOM, end.y);
	SetDlgItemInt(IDC_EDIT_TILE_X, 1);
	SetDlgItemInt(IDC_EDIT_TILE_Y, 1);
}

void CControlView::ChangeSelectInfo()
{
	CPoint start, end;
	
	start.x = GetDlgItemInt(IDC_EDIT_SELECT_LEFT);
	start.y = GetDlgItemInt(IDC_EDIT_SELECT_TOP);
	end.x = GetDlgItemInt(IDC_EDIT_SELECT_RIGHT);
	end.y = GetDlgItemInt(IDC_EDIT_SELECT_BOTTOM);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->SetSelectInfo(start, end);
}

void CControlView::UpdateImageList()
{
	m_ImageList.DeleteAllItems();

	MAP_IMAGE& mapImage = CSpriteManager::GetInstance()->GetImageMap();
	MAP_IMAGE_ITER iter = mapImage.begin();
	WCHAR strTemp[20];
	for (int idx = 0; iter != mapImage.end(); ++iter, ++idx)
	{
		_itow_s(idx, strTemp, 20, 10);
		m_ImageList.InsertItem(idx, strTemp);	// 순번

		m_ImageList.SetItemText(idx, 1, iter->first.c_str());	// 파일명

		_itow_s(iter->second->GetWidth(), strTemp, 20, 10);
		m_ImageList.SetItemText(idx, 2, strTemp);	// 가로

		_itow_s(iter->second->GetHeight(), strTemp, 20, 10);
		m_ImageList.SetItemText(idx, 3, strTemp);	// 세로
	}
}

void CControlView::UpdateSpriteList()
{
	m_SpriteList.DeleteAllItems();

	VEC_SPRITEINFO& vecSprite = CSpriteManager::GetInstance()->GetSpriteList();
	VEC_SPRITEINFO_ITER iter = vecSprite.begin();
	WCHAR strTemp[20];
	for ( int idx = 0; iter != vecSprite.end(); ++iter, ++idx)
	{
		CSpriteInfo* pSpriteInfo = *iter;

		_itow_s(idx, strTemp, 20, 10);
		m_SpriteList.InsertItem(idx, strTemp);	// 순번

		m_SpriteList.SetItemText(idx, 1, pSpriteInfo->GetImageName().c_str());	// 파일명

		_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
		m_SpriteList.SetItemText(idx, 2, strTemp);	// 프레임수
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetFrameView()->SetSpritInfo(NULL);
	pMainFrame->GetImageView()->SetSelectImage(NULL);
}

void CControlView::UpdateSelectSprite()
{
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;
	
	WCHAR strName[MAX_PATH];
	m_SpriteList.GetItemText(nSelected, 1, strName, MAX_PATH);

	// 이미지뷰 이미지 변경
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->SetSelectImage(strName);

	// 프레임뷰 변경
	pMainFrame->GetFrameView()->SetSpritInfo(CSpriteManager::GetInstance()->GetSpriteInfo(nSelected));
	//pMainFrame->GetAnimView()->SetSpritInfo(CSpriteManager::GetInstance()->GetSpriteInfo(nSelected));
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_ImageList);
	DDX_Control(pDX, IDC_LIST_SPRITE, m_SpriteList);
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	ON_EN_CHANGE(IDC_EDIT_SELECT_LEFT, &CControlView::OnEnChangeEditSelectLeft)
	ON_EN_CHANGE(IDC_EDIT_SELECT_TOP, &CControlView::OnEnChangeEditSelectTop)
	ON_EN_CHANGE(IDC_EDIT_SELECT_RIGHT, &CControlView::OnEnChangeEditSelectRight)
	ON_EN_CHANGE(IDC_EDIT_SELECT_BOTTOM, &CControlView::OnEnChangeEditSelectBottom)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IMAGE, &CControlView::OnNMClickListImage)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SPRITE, &CControlView::OnBnClickedButtonAddSprite)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_ADD, &CControlView::OnBnClickedButtonSelectAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPRITE, &CControlView::OnNMClickListSprite)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SPRITE, &CControlView::OnBnClickedButtonDeleteSprite)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_IMAGE, &CControlView::OnBnClickedButtonDeleteImage)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_SPRITE, &CControlView::OnBnClickedButtonSaveSprite)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_SPRITE, &CControlView::OnBnClickedButtonLoadSprite)
	ON_BN_CLICKED(IDC_ZOOM_IN, &CControlView::OnBnClickedZoomIn)
	ON_BN_CLICKED(IDC_ZOOM_OUT2, &CControlView::OnBnClickedZoomOut2)
	ON_EN_CHANGE(IDC_EDIT_TILE_X, &CControlView::OnEnChangeEditTileX)
	ON_EN_CHANGE(IDC_EDIT_TILE_Y, &CControlView::OnEnChangeEditTileY)
	ON_BN_CLICKED(IDC_BUTTON4, &CControlView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CControlView::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT_FRAME, &CControlView::OnEnChangeEditFrame)
END_MESSAGE_MAP()


// CControlView 진단입니다.

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView 메시지 처리기입니다.

void CControlView::OnEnChangeEditSelectLeft()
{
	ChangeSelectInfo();
}

void CControlView::OnEnChangeEditSelectTop()
{
	ChangeSelectInfo();
}

void CControlView::OnEnChangeEditSelectRight()
{
	ChangeSelectInfo();
}

void CControlView::OnEnChangeEditSelectBottom()
{
	ChangeSelectInfo();
}

void CControlView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_ImageList.SetExtendedStyle(m_ImageList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_ImageList.InsertColumn(0, L"순번", LVCFMT_LEFT, 40);
	m_ImageList.InsertColumn(1, L"파일명", LVCFMT_LEFT, 110);
	m_ImageList.InsertColumn(2, L"가로", LVCFMT_LEFT, 50);
	m_ImageList.InsertColumn(3, L"세로", LVCFMT_LEFT, 50);

	m_SpriteList.SetExtendedStyle(m_ImageList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_SpriteList.InsertColumn(0, L"순번", LVCFMT_LEFT, 40);
	m_SpriteList.InsertColumn(1, L"파일명", LVCFMT_LEFT, 130);
	m_SpriteList.InsertColumn(2, L"프레임수", LVCFMT_LEFT, 60);
}

void CControlView::OnNMClickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pList = (NM_LISTVIEW*)pNMHDR;

	// 이미지 리스트의 아이템을 선택했다면 이미지뷰에 출력
	if (pList->iItem != -1)
	{
		WCHAR strName[MAX_PATH];
		m_ImageList.GetItemText(pList->iItem, 1, strName, MAX_PATH);

		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		pMainFrame->GetImageView()->SetSelectImage(strName);
	}

	*pResult = 0;
}

void CControlView::OnBnClickedButtonAddSprite()
{
	// 이미지가 선택이 되었는지 확인
	int nSelected = m_ImageList.GetNextItem(-1, LVNI_SELECTED);
	
	if (nSelected == -1)
	{
		MessageBox(L"이미지가 선택되지 않았습니다.", L"경고");
		return;
	}

	// 스프라이트 정보 추가
	WCHAR strName[MAX_PATH];
	m_ImageList.GetItemText(nSelected, 1, strName, MAX_PATH);

	CSpriteInfo* pSpriteInfo = new CSpriteInfo;
	if (!pSpriteInfo->SetImage(strName))
	{
		delete pSpriteInfo;
		MessageBox(L"이미지가 잘못되었습니다.", L"경고");
		return;
	}

	CSpriteManager::GetInstance()->AddSpriteInfo(pSpriteInfo);

	// 스프라이트 리스트 갱신
	UpdateSpriteList();

	// 마지막에 추가한 스프라이트 선택
	nSelected = CSpriteManager::GetInstance()->GetSpriteList().size()-1;
	m_SpriteList.SetItemState(nSelected, 
							  LVIS_FOCUSED|LVIS_SELECTED, 
							  LVIS_FOCUSED|LVIS_SELECTED);

	UpdateSelectSprite();
}

void CControlView::OnBnClickedButtonSelectAdd()
{
	// 선택된 스프라이트 정보가 없다면 리턴
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(L"선택된 스프라이트 정보가 없습니다.", L"경고");
		return;
	}
	
	CSpriteInfo* pSpriteInfo = CSpriteManager::GetInstance()->GetSpriteInfo(nSelected);
	if (!pSpriteInfo)
	{
		MessageBox(L"스프라이트 정보를 찾을수 없습니다.", L"경고");
		return;
	}

	// 프레임 정보 추가
	FRAME_INFO* pFrameInfo = new FRAME_INFO;
	pFrameInfo->rect.left = GetDlgItemInt(IDC_EDIT_SELECT_LEFT);
	pFrameInfo->rect.top = GetDlgItemInt(IDC_EDIT_SELECT_TOP);
	pFrameInfo->rect.right = GetDlgItemInt(IDC_EDIT_SELECT_RIGHT);
	pFrameInfo->rect.bottom = GetDlgItemInt(IDC_EDIT_SELECT_BOTTOM);
	pFrameInfo->center = pFrameInfo->rect.CenterPoint();
	pFrameInfo->aniTime = 0.1f;
	pSpriteInfo->AddFrameInfo(pFrameInfo);

	// 스프라이트 정보 리스트 갱신
	WCHAR strTemp[20];
	_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
	m_SpriteList.SetItemText(nSelected, 2, strTemp);	// 프레임수

	//// 프레임뷰 갱신
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetFrameView()->Invalidate(TRUE);
}

void CControlView::OnNMClickListSprite(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateSelectSprite();
}

void CControlView::OnBnClickedButtonDeleteSprite()
{
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;

	CSpriteManager::GetInstance()->DeleteSpriteInfo(nSelected);

	UpdateSpriteList();	
}

void CControlView::OnBnClickedButtonDeleteImage()
{
	int nSelected = m_ImageList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(L"선택된 이미지가 없습니다.", L"경고");
		return;
	}
	
	if (IDYES == MessageBox(L"선택한 이미지를 사용하는 스프라이트 정보가 삭제 됩니다. \n삭제 하시겠습니까?", L"경고", MB_YESNO))
	{
		WCHAR strName[MAX_PATH];
		m_ImageList.GetItemText(nSelected, 1, strName, MAX_PATH);
		CSpriteManager::GetInstance()->DeleteImage(strName);

		UpdateImageList();
		UpdateSpriteList();
	}
}


void CControlView::OnBnClickedButtonSaveSprite()
{
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
		return;

	if (IDYES == MessageBox(L"선택한 스프라이트 정보를 저장합니다.", L"경고", MB_YESNO))
	{
		wchar_t file_name[MAX_PATH];
		m_ImageList.GetItemText(nSelected, 1, file_name, MAX_PATH);
		CSpriteManager::GetInstance()->SaveSpriteInfo(file_name);
	}
}


void CControlView::OnBnClickedButtonLoadSprite()
{
	wchar_t szFilter[] = L"Sprite File(*.spr)|*.spr|";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == dlg.DoModal())
	{
		CString strPathName = dlg.GetPathName();
		CSpriteManager::GetInstance()->LoadSpriteInfo(strPathName.GetBuffer(0));
	}
}


void CControlView::OnBnClickedZoomIn()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->ZoomIn();
}

void CControlView::OnBnClickedZoomOut2()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->ZoomOut();
}


void CControlView::OnEnChangeEditTileX()
{
	m_iTileWidth = GetDlgItemInt(IDC_EDIT_TILE_X);
}


void CControlView::OnEnChangeEditTileY()
{
	m_iTileHeight = GetDlgItemInt(IDC_EDIT_TILE_Y);
}

void CControlView::SetRectInfo(int w, int h)
{
	SetDlgItemInt(IDC_STATIC_X,w,TRUE);
	SetDlgItemInt(IDC_STATIC_Y,h,TRUE);
}

void CControlView::SetFrameIndex(int idx)
{
	SetDlgItemInt(IDC_STATIC_FRAME,idx,TRUE);
}

void CControlView::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(L"선택된 스프라이트 정보가 없습니다.", L"경고");
		return;
	}
	
	CSpriteInfo* pSpriteInfo = CSpriteManager::GetInstance()->GetSpriteInfo(nSelected);
	if (!pSpriteInfo)
	{
		MessageBox(L"스프라이트 정보를 찾을수 없습니다.", L"경고");
		return;
	}

	for(int tile_y = 0; tile_y < m_iTileHeight; tile_y++)
	{
		for(int tile_x = 0; tile_x < m_iTileWidth; tile_x++)
		{
			// 프레임 정보 추가
			FRAME_INFO* pFrameInfo = new FRAME_INFO;
			pFrameInfo->rect.left = GetDlgItemInt(IDC_EDIT_SELECT_LEFT);
			pFrameInfo->rect.top = GetDlgItemInt(IDC_EDIT_SELECT_TOP);
			pFrameInfo->rect.right = GetDlgItemInt(IDC_EDIT_SELECT_RIGHT);
			pFrameInfo->rect.bottom = GetDlgItemInt(IDC_EDIT_SELECT_BOTTOM);

			int frame_width = pFrameInfo->rect.right - pFrameInfo->rect.left;
			int frame_height = pFrameInfo->rect.bottom - pFrameInfo->rect.top;
			pFrameInfo->rect.left += frame_width*tile_x;
			pFrameInfo->rect.right += frame_width*tile_x;
			pFrameInfo->rect.top += frame_height*tile_y;
			pFrameInfo->rect.bottom += frame_height*tile_y;

			pFrameInfo->center = pFrameInfo->rect.CenterPoint();
			pFrameInfo->center.x += frame_width*tile_x;
			pFrameInfo->center.y += frame_height*tile_y;

			pFrameInfo->aniTime = 0.1f;
			
			pSpriteInfo->AddFrameInfo(pFrameInfo);

			// 스프라이트 정보 리스트 갱신
			WCHAR strTemp[20];
			_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
			m_SpriteList.SetItemText(nSelected, 2, strTemp);	// 프레임수
		}
	}
	//// 프레임뷰 갱신
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetFrameView()->Invalidate(TRUE);

}


void CControlView::OnBnClickedButton5()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	RectProcessing dlg(this);
	dlg.DoModal();
}


void CControlView::OnEnChangeEditFrame()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	wchar_t str_frame_name[20];	
	GetDlgItemText(IDC_EDIT_FRAME,str_frame_name,20);
	pMainFrame->GetFrameView()->SetFrameName(str_frame_name);
}

void CControlView::SetEditFrame(wchar_t* str_frame_name)
{
	SetDlgItemText(IDC_EDIT_FRAME,str_frame_name);
}

void CControlView::GetEditFrame(wchar_t* str_frame_name)
{
	GetDlgItemText(IDC_EDIT_FRAME,str_frame_name,20);
}
