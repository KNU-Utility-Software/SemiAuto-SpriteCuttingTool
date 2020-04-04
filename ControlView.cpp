// ControlView.cpp : ���� �����Դϴ�.
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
		m_ImageList.InsertItem(idx, strTemp);	// ����

		m_ImageList.SetItemText(idx, 1, iter->first.c_str());	// ���ϸ�

		_itow_s(iter->second->GetWidth(), strTemp, 20, 10);
		m_ImageList.SetItemText(idx, 2, strTemp);	// ����

		_itow_s(iter->second->GetHeight(), strTemp, 20, 10);
		m_ImageList.SetItemText(idx, 3, strTemp);	// ����
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
		m_SpriteList.InsertItem(idx, strTemp);	// ����

		m_SpriteList.SetItemText(idx, 1, pSpriteInfo->GetImageName().c_str());	// ���ϸ�

		_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
		m_SpriteList.SetItemText(idx, 2, strTemp);	// �����Ӽ�
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

	// �̹����� �̹��� ����
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->SetSelectImage(strName);

	// �����Ӻ� ����
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


// CControlView �����Դϴ�.

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


// CControlView �޽��� ó�����Դϴ�.

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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_ImageList.SetExtendedStyle(m_ImageList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_ImageList.InsertColumn(0, L"����", LVCFMT_LEFT, 40);
	m_ImageList.InsertColumn(1, L"���ϸ�", LVCFMT_LEFT, 110);
	m_ImageList.InsertColumn(2, L"����", LVCFMT_LEFT, 50);
	m_ImageList.InsertColumn(3, L"����", LVCFMT_LEFT, 50);

	m_SpriteList.SetExtendedStyle(m_ImageList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	m_SpriteList.InsertColumn(0, L"����", LVCFMT_LEFT, 40);
	m_SpriteList.InsertColumn(1, L"���ϸ�", LVCFMT_LEFT, 130);
	m_SpriteList.InsertColumn(2, L"�����Ӽ�", LVCFMT_LEFT, 60);
}

void CControlView::OnNMClickListImage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	NM_LISTVIEW* pList = (NM_LISTVIEW*)pNMHDR;

	// �̹��� ����Ʈ�� �������� �����ߴٸ� �̹����信 ���
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
	// �̹����� ������ �Ǿ����� Ȯ��
	int nSelected = m_ImageList.GetNextItem(-1, LVNI_SELECTED);
	
	if (nSelected == -1)
	{
		MessageBox(L"�̹����� ���õ��� �ʾҽ��ϴ�.", L"���");
		return;
	}

	// ��������Ʈ ���� �߰�
	WCHAR strName[MAX_PATH];
	m_ImageList.GetItemText(nSelected, 1, strName, MAX_PATH);

	CSpriteInfo* pSpriteInfo = new CSpriteInfo;
	if (!pSpriteInfo->SetImage(strName))
	{
		delete pSpriteInfo;
		MessageBox(L"�̹����� �߸��Ǿ����ϴ�.", L"���");
		return;
	}

	CSpriteManager::GetInstance()->AddSpriteInfo(pSpriteInfo);

	// ��������Ʈ ����Ʈ ����
	UpdateSpriteList();

	// �������� �߰��� ��������Ʈ ����
	nSelected = CSpriteManager::GetInstance()->GetSpriteList().size()-1;
	m_SpriteList.SetItemState(nSelected, 
							  LVIS_FOCUSED|LVIS_SELECTED, 
							  LVIS_FOCUSED|LVIS_SELECTED);

	UpdateSelectSprite();
}

void CControlView::OnBnClickedButtonSelectAdd()
{
	// ���õ� ��������Ʈ ������ ���ٸ� ����
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(L"���õ� ��������Ʈ ������ �����ϴ�.", L"���");
		return;
	}
	
	CSpriteInfo* pSpriteInfo = CSpriteManager::GetInstance()->GetSpriteInfo(nSelected);
	if (!pSpriteInfo)
	{
		MessageBox(L"��������Ʈ ������ ã���� �����ϴ�.", L"���");
		return;
	}

	// ������ ���� �߰�
	FRAME_INFO* pFrameInfo = new FRAME_INFO;
	pFrameInfo->rect.left = GetDlgItemInt(IDC_EDIT_SELECT_LEFT);
	pFrameInfo->rect.top = GetDlgItemInt(IDC_EDIT_SELECT_TOP);
	pFrameInfo->rect.right = GetDlgItemInt(IDC_EDIT_SELECT_RIGHT);
	pFrameInfo->rect.bottom = GetDlgItemInt(IDC_EDIT_SELECT_BOTTOM);
	pFrameInfo->center = pFrameInfo->rect.CenterPoint();
	pFrameInfo->aniTime = 0.1f;
	pSpriteInfo->AddFrameInfo(pFrameInfo);

	// ��������Ʈ ���� ����Ʈ ����
	WCHAR strTemp[20];
	_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
	m_SpriteList.SetItemText(nSelected, 2, strTemp);	// �����Ӽ�

	//// �����Ӻ� ����
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetFrameView()->Invalidate(TRUE);
}

void CControlView::OnNMClickListSprite(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(L"���õ� �̹����� �����ϴ�.", L"���");
		return;
	}
	
	if (IDYES == MessageBox(L"������ �̹����� ����ϴ� ��������Ʈ ������ ���� �˴ϴ�. \n���� �Ͻðڽ��ϱ�?", L"���", MB_YESNO))
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

	if (IDYES == MessageBox(L"������ ��������Ʈ ������ �����մϴ�.", L"���", MB_YESNO))
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nSelected = m_SpriteList.GetNextItem(-1, LVNI_SELECTED);
	if (nSelected == -1)
	{
		MessageBox(L"���õ� ��������Ʈ ������ �����ϴ�.", L"���");
		return;
	}
	
	CSpriteInfo* pSpriteInfo = CSpriteManager::GetInstance()->GetSpriteInfo(nSelected);
	if (!pSpriteInfo)
	{
		MessageBox(L"��������Ʈ ������ ã���� �����ϴ�.", L"���");
		return;
	}

	for(int tile_y = 0; tile_y < m_iTileHeight; tile_y++)
	{
		for(int tile_x = 0; tile_x < m_iTileWidth; tile_x++)
		{
			// ������ ���� �߰�
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

			// ��������Ʈ ���� ����Ʈ ����
			WCHAR strTemp[20];
			_itow_s(pSpriteInfo->GetFrameCount(), strTemp, 20, 10);
			m_SpriteList.SetItemText(nSelected, 2, strTemp);	// �����Ӽ�
		}
	}
	//// �����Ӻ� ����
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
