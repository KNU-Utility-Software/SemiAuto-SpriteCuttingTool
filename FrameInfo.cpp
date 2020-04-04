#include "stdafx.h"
#include "FrameInfo.h"

FRAME_INFO::FRAME_INFO()
	: rect(0, 0, 0, 0)
	, center(0, 0)
	, aniTime(0.f)
{
	name[0] = '\0';
}

FRAME_INFO::~FRAME_INFO()
{

}