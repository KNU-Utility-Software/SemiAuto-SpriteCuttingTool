#pragma once

struct FRAME_INFO
{
	FRAME_INFO();
	~FRAME_INFO();

	CRect rect;
	CPoint center;
	float aniTime;
	wchar_t name[20];	
};