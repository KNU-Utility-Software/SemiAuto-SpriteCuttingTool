#pragma once

namespace UTIL
{
	std::wstring GetFileName(LPCWSTR strPath);
	wchar_t* MultiToUni(char* multi_name);
	char* UniToMulti(wchar_t* uni_str);
}
