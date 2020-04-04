#include "StdAfx.h"
#include "SpriteInfo.h"
#include "SpriteManager.h"

CSpriteInfo::CSpriteInfo(void)
	: m_pImage(NULL)
{

}

CSpriteInfo::~CSpriteInfo(void)
{
	for(int i = 0; i < (int)m_vecFrameInfo.size(); i++)
	{
		delete m_vecFrameInfo[i];
		m_vecFrameInfo[i] = NULL;
	}

	m_vecFrameInfo.clear();
}

void CSpriteInfo::AddFrameInfo(FRAME_INFO* pFrameInfo)
{
	if (!pFrameInfo)
		return;

	m_vecFrameInfo.push_back(pFrameInfo);
}

bool CSpriteInfo::SetImage(LPWSTR strImageName)
{
	CImage* pImage = CSpriteManager::GetInstance()->GetImage(strImageName);

	if (!pImage)
		return false;

	m_pImage = pImage;
	m_strImageName = strImageName;

	return true;
}