#include "stdafx.h"
#include "Util.h"

std::wstring UTIL::GetFileName(LPCWSTR strPath)
{
	std::wstring strName = strPath;

	size_t pos = strName.find_last_of(L"\\");
	if (pos != std::wstring::npos)
		strName = strName.substr(pos+1);

	return strName;
}

wchar_t* UTIL::MultiToUni(char* multi_str)
{
	wchar_t* strUnicode = new wchar_t[256];
	int nLen = MultiByteToWideChar(CP_ACP, 0, multi_str, strlen(multi_str), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, multi_str, strlen(multi_str), strUnicode, nLen);

	return strUnicode;
}

char* UTIL::UniToMulti(wchar_t* uni_str)
{
	char* strMultibyte = new char[256];
	int len = WideCharToMultiByte( CP_ACP, 0, uni_str, -1, NULL, 0, NULL, NULL );	
	WideCharToMultiByte( CP_ACP, 0, uni_str, -1, strMultibyte, len, NULL, NULL );

	return strMultibyte;
}
