// RectProcessing.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SpriteTool.h"
#include "RectProcessing.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ImageView.h"

// RectProcessing ��ȭ �����Դϴ�.

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


// RectProcessing �޽��� ó�����Դϴ�.


void RectProcessing::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_STATIC_MESSAGE,L"�簢������ �ȼ������ ó�� ���Դϴ�.");
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->GetImageView()->CalcFrameRect();

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnOK();
}
