#pragma once


// RectProcessing 대화 상자입니다.

class RectProcessing : public CDialogEx
{
	DECLARE_DYNAMIC(RectProcessing)

public:
	RectProcessing(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~RectProcessing();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALC_RECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
