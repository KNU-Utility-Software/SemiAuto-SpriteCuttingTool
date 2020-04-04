
// SpriteToolDoc.cpp : CSpriteToolDoc 클래스의 구현
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


// CSpriteToolDoc 생성/소멸

CSpriteToolDoc::CSpriteToolDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSpriteToolDoc::~CSpriteToolDoc()
{
}

BOOL CSpriteToolDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSpriteToolDoc serialization

void CSpriteToolDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CSpriteToolDoc 진단

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


// CSpriteToolDoc 명령
