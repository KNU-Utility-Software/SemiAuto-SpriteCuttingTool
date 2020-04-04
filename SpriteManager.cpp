#include "StdAfx.h"
#include "SpriteManager.h"
#include "Util.h"
#include "ImageView.h"
#include "SpriteInfo.h"
#include "FrameInfo.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

CSpriteManager* CSpriteManager::m_Instance = NULL;

CSpriteManager::CSpriteManager(void)
{
}

CSpriteManager::~CSpriteManager(void)
{
}

CSpriteManager* CSpriteManager::GetInstance()
{
	if (m_Instance == NULL)
		m_Instance = new CSpriteManager;

	return m_Instance;
}

void CSpriteManager::ReleaseInstance()
{
	SAFE_DELETE(m_Instance);
}

bool CSpriteManager::LoadImageFile(LPCWSTR strPath)
{
	wcscpy_s(m_strPath,strPath);
	std::wstring strFileName = UTIL::GetFileName(strPath);

	// 이미 해당이름의 이미지가 존재 한다면 로드하지 않는다.
	MAP_IMAGE_ITER iter = m_mapImage.find(strFileName);
	if (iter != m_mapImage.end())
		return false;

	// 이미지 로드
	CImage* pImage = new CImage;
	HRESULT hr = pImage->Load(strPath);
	if (hr == S_FALSE)
	{
		delete pImage;
		return false;
	}
	
	// 맵에 추가
	m_mapImage.insert(std::make_pair(strFileName, pImage));
	
	return true;
}

void CSpriteManager::Release()
{
	MAP_IMAGE_ITER iter = m_mapImage.begin();
	for ( ; iter != m_mapImage.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapImage.clear();
}

CImage* CSpriteManager::GetImage(LPWSTR strName)
{
	MAP_IMAGE_ITER iter = m_mapImage.find(strName);

	if (iter == m_mapImage.end())
		return NULL;

	return iter->second;
}

void CSpriteManager::AddSpriteInfo(CSpriteInfo* pSpriteInfo)
{
	if (!pSpriteInfo)
		return;

	m_vecSprite.push_back(pSpriteInfo);
}

CSpriteInfo* CSpriteManager::GetSpriteInfo(int idx)
{
	if (idx < 0 || idx >= (int)m_vecSprite.size())
		return NULL;

	return m_vecSprite[idx];
}

void CSpriteManager::DeleteSpriteInfo(int idx)
{
	VEC_SPRITEINFO_ITER iter = m_vecSprite.begin() + idx;
	SAFE_DELETE(*iter);
	m_vecSprite.erase(iter);
}

void CSpriteManager::DeleteImage(LPWSTR strName)
{
	MAP_IMAGE_ITER iter = m_mapImage.find(strName);
	if (iter == m_mapImage.end())
		return;

	SAFE_DELETE(iter->second);
	m_mapImage.erase(iter);

	// 해당 이미지를 사용하는 스프라이트정보를 모두 삭제
	VEC_SPRITEINFO_ITER iter_sprite = m_vecSprite.begin();
	while (iter_sprite != m_vecSprite.end())
	{
		CSpriteInfo* pSpriteInfo = *iter_sprite;
		if (pSpriteInfo->GetImageName() == strName)
		{
			iter_sprite = m_vecSprite.erase(iter_sprite);
		}
		else
		{
			++iter_sprite;
		}
	}
}

void CSpriteManager::SaveSpriteInfo(LPWSTR strName)
{
	ofstream myfile;
	WCHAR file_name[MAX_PATH];
	swprintf_s(file_name,L"%s.txt",strName);
	
	wchar_t path[MAX_PATH];
	wcscpy_s(path,CSpriteManager::GetInstance()->GetFilePath());
	wcscat_s(path,file_name);
	myfile.open (path);
	
	VEC_SPRITEINFO_ITER iter_sprite = m_vecSprite.begin();
	while (iter_sprite != m_vecSprite.end())
	{
		CSpriteInfo* pSpriteInfo = *iter_sprite;
		
		myfile << "BAXXXX01" << endl;

		myfile <<
		"#-----------------------------------------------------------------" << endl <<
		"# Bitmap Animation version 0.1 - XXXX" << endl <<
		"#-----------------------------------------------------------------" << endl << endl <<
		"#---------------------------------------------------------------" << endl <<
		"#작성일 : 2010 04 16" << endl <<
		"#작성자 : Kim HoGeun" << endl <<
		"#----------------------------------------------------------------" << endl << endl <<
		"#-----------------------------------------------------------------" << endl <<
		"# 등장인물 - _STMAIN_BGALL.spr.txt" << endl <<
		"#-----------------------------------------------------------------" << endl << endl;


		myfile << "$INFO" << endl <<
		"type=" << endl <<
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;

		myfile << "$HEAD" << endl << 
		"ani_type= 1" << endl << 
		"tile_direction= -1 #이값은 영향을 받지 않음. ani_type = 1때문에." << endl << endl;

		DWORD frame_count = pSpriteInfo->GetFrameCount();

		myfile << "frame_count=" << pSpriteInfo->GetFrameCount() << endl <<
		"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;

		wchar_t* uni_image_name = new wchar_t[256];
		wcscpy_s(uni_image_name, 256, pSpriteInfo->GetImageName().c_str());
		char* multi_image_name = UTIL::UniToMulti(uni_image_name);

		myfile << "$IMG" << endl << 
		multi_image_name << "," <<  multi_image_name << ", 0"<<endl << endl;

		delete multi_image_name;
		multi_image_name = NULL;

		delete uni_image_name;
		uni_image_name = NULL;
		

		myfile << "$DATA" << endl << endl <<
		"#BITMAP TILE DATA" << endl <<
		"#TILE DATA" << endl << endl <<
		"%ANI" << endl << endl <<
		">0" << endl;

		VEC_FRAMEINFO& vecFrameInfo = pSpriteInfo->GetFrameInfoList();

		VEC_FRAMEINFO_ITER itr;
		int i;
		for(i = 0, itr = vecFrameInfo.begin();itr != vecFrameInfo.end();itr++, i++)
		{
			FRAME_INFO* pFrame = *itr;
			myfile << 
				"#" << UTIL::UniToMulti(pFrame->name) << endl << 
				"S, 0, " << 
				pFrame->rect.left << ", " << pFrame->rect.top << ", " <<
				pFrame->rect.right - pFrame->rect.left<< ", " << 
				pFrame->rect.bottom - pFrame->rect.top<< ", 0, " << 
				pFrame->center.x << ":" <<  pFrame->center.y << ", spr-" << i<< endl << endl;
		}

		myfile << 
			"%FRAME_DELAY" << endl <<
			">0" << endl <<
			"#3" << endl <<
			"10" << endl;

		//pFrame->aniTime << endl << endl;

		myfile << endl;
		iter_sprite++;
	}

	myfile.close();
}

void CSpriteManager::LoadSpriteInfo(LPWSTR strName)
{
	ifstream myfile;
	WCHAR file_name[128];
	swprintf_s(file_name,L"%s.spr",strName);
	myfile.open (file_name);
	
	VEC_SPRITEINFO_ITER iter_sprite = m_vecSprite.begin();
	while (iter_sprite != m_vecSprite.end())
	{
		char image_name[128];
		char str_frame_count[8];
		int frame_count;

		myfile.read(image_name,strlen(image_name)+1);
		myfile.read("\n",sizeof("\n"));
		myfile.read(str_frame_count,sizeof(str_frame_count));
		myfile.read("\n",sizeof("\n"));

		frame_count = atoi(str_frame_count);

		CSpriteInfo* pSpriteInfo = *iter_sprite;

		wchar_t* uni_image_name = new wchar_t[256];
		wcscpy_s(uni_image_name,wcslen(UTIL::MultiToUni(image_name))+1,UTIL::MultiToUni(image_name));
		pSpriteInfo->SetImage(uni_image_name);
		
		VEC_FRAMEINFO& vecFrameInfo = pSpriteInfo->GetFrameInfoList();

		VEC_FRAMEINFO_ITER itr;
		for(itr = vecFrameInfo.begin();itr != vecFrameInfo.end();itr++)
		{
			FRAME_INFO* pFrame = *itr;

			char buffer[8];
			myfile.read(buffer,sizeof(pFrame->rect.left));
			pFrame->rect.left = atoi(buffer);
			myfile.read("\n",sizeof("\n"));

			myfile.read(buffer,sizeof(pFrame->rect.top));
			pFrame->rect.top = atoi(buffer);
			
			myfile.read(buffer,sizeof(pFrame->rect.right));
			pFrame->rect.right = atoi(buffer);

			myfile.read(buffer,sizeof(pFrame->rect.bottom));
			pFrame->rect.bottom = atoi(buffer);

			myfile.read(buffer,sizeof(pFrame->center.x));
			pFrame->center.x = atoi(buffer);

			myfile.read(buffer,sizeof(pFrame->center.y));
			pFrame->center.y = atoi(buffer);

			myfile.read(buffer,sizeof(pFrame->aniTime));
			pFrame->aniTime = (float)atof(buffer);
		}
		iter_sprite++;
	}

	myfile.close();
}
