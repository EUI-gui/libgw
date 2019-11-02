#pragma once

#include <string>
#include <iostream>

#ifndef _WCHAR_T_DEFINED
using wchar_t = unsigned short;
#endif // !_WCHAR_T_DEFINED


class GWString
{
public:
	static std::wstring utf_8_to_unicode(std::string utf_8str, int size = -1);
	static std::string unicode_to_utf_8(std::wstring unicode, int size = -1);
	
public:
	bool isNull();
	void release();
	void clear();
	inline wchar_t* c_str()const;

	inline size_t size ()const;
	inline size_t charlenght ()const;
public:
	GWString();
	GWString(char c);
	GWString(wchar_t c);
	GWString(const char* string, int size = -1);
	GWString(const wchar_t* string, int size = -1);
	GWString(std::string string, int size = -1);
	GWString(std::wstring string, int size = -1);
	GWString(const GWString& string);
	virtual ~GWString();
public:
	GWString& operator=(const GWString& string);
	GWString& operator= (char c);
	GWString& operator= (wchar_t c);
	wchar_t& operator[] (unsigned int count);
	GWString operator+ (const GWString& string);
	GWString& operator+=(const GWString& string);
	bool operator== (const GWString& string);
	friend std::ostream& operator<< (std::ostream& out, const GWString& string);
private:
	wchar_t* d;
	size_t _size;
};

