// RectProcessing.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "RectProcessing.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ImageView.h"

// RectProcessing 대화 상자입니다.

IMPLEMENT_DYNAMIC(RectProcessing, CDialogEx)

RectProcessing::RectProcessing(CWnd* pParent /*=NULL*/)
	: CDialogEx(RectProcessing::IDD, pParent)
{

}

RectProcessing::~RectProcessing()
{
}

void RectProcessing::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RectProcessing, CDialogEx)
	ON_BN_CLICKED(IDOK, &RectProcessing::OnBnClickedOk)
END_MESSAGE_MAP()


// RectProcessing 메시지 처리기입니다.


void RectProcessing::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgItemText(IDC_STATIC_MESSAGE,L"사각형역역 픽셀계산을 처리 중입니다.");
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->CalcFrameRect();

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}
