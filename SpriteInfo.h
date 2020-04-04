#pragma once

#include <vector>

struct FRAME_INFO;

typedef std::vector<FRAME_INFO*>	VEC_FRAMEINFO;
typedef VEC_FRAMEINFO::iterator		VEC_FRAMEINFO_ITER;

class CSpriteInfo
{
private:
	VEC_FRAMEINFO m_vecFrameInfo;
	std::wstring m_strImageName;
	CImage* m_pImage;

public:
	CSpriteInfo(void);
	~CSpriteInfo(void);

	void AddFrameInfo(FRAME_INFO* pFrameInfo);
	bool SetImage(LPWSTR strImageName);

public:
	const std::wstring& GetImageName() const { return m_strImageName; }
	DWORD GetFrameCount() { return m_vecFrameInfo.size(); }
	CImage* GetImage() { return m_pImage; }
	VEC_FRAMEINFO& GetFrameInfoList() {return m_vecFrameInfo; }
};
