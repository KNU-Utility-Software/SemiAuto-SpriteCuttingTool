
// SpriteToolDoc.cpp : CSpriteToolDoc Ŭ������ ����
//

#include "stdafx.h"
#include "SpriteTool.h"

#include "SpriteToolDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpriteToolDoc

IMPLEMENT_DYNCREATE(CSpriteToolDoc, CDocument)

BEGIN_MESSAGE_MAP(CSpriteToolDoc, CDocument)
END_MESSAGE_MAP()


// CSpriteToolDoc ����/�Ҹ�

CSpriteToolDoc::CSpriteToolDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CSpriteToolDoc::~CSpriteToolDoc()
{
}

BOOL CSpriteToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CSpriteToolDoc serialization

void CSpriteToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CSpriteToolDoc ����

#ifdef _DEBUG
void CSpriteToolDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSpriteToolDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSpriteToolDoc ���
