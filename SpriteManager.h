#pragma once

#include <map>
#include <vector>

class CSpriteInfo;

typedef std::map<std::wstring, CImage*> MAP_IMAGE;
typedef MAP_IMAGE::iterator				MAP_IMAGE_ITER;

typedef std::vector<CSpriteInfo*>	VEC_SPRITEINFO;
typedef VEC_SPRITEINFO::iterator	VEC_SPRITEINFO_ITER;

class CSpriteManager
{
private:
	MAP_IMAGE m_mapImage;		// 로드된 이미지
	VEC_SPRITEINFO m_vecSprite;	// 스프라이트 정보
	wchar_t m_strPath[MAX_PATH];
private:
	CSpriteManager(void);
	~CSpriteManager(void);

	static CSpriteManager* m_Instance;

public:
	static CSpriteManager* GetInstance();
	static void ReleaseInstance();
	wchar_t* GetFilePath() { return m_strPath; }
public:
	bool LoadImageFile(LPCWSTR strPath);
	void Release();
	CImage* GetImage(LPWSTR strName);

	void AddSpriteInfo(CSpriteInfo* pSpriteInfo);
	CSpriteInfo* GetSpriteInfo(int idx);
	void DeleteSpriteInfo(int idx);
	void DeleteImage(LPWSTR strName);
	void SaveSpriteInfo(LPWSTR strName);
	void LoadSpriteInfo(LPWSTR strName);
public:
	MAP_IMAGE& GetImageMap() { return m_mapImage; }
	VEC_SPRITEINFO& GetSpriteList() { return m_vecSprite; }
};
