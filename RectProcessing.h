#pragma once


// RectProcessing ��ȭ �����Դϴ�.

class RectProcessing : public CDialogEx
{
	DECLARE_DYNAMIC(RectProcessing)

public:
	RectProcessing(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~RectProcessing();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CALC_RECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
