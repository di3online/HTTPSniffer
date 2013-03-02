#pragma once
#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include <cstdlib>


class str_list{
public:
	str_list(char *filename_);							// �������� ������
	
	void addStr(const WCHAR* str);						// ���������� ������ 
	int  getByFile(void);								// �������� �� �����
	WCHAR* getStr(void);
//	void deleteStr(WCHAR* str);							// �������� ������
	void parse(WCHAR *buf, DWORD bufSize);

	virtual ~str_list(void);
private:
	std::list<WCHAR*> slist;							// std::list<std::wstring> slist; std::list<WCHAR*> slist;
	int countElem;
	int curStr;
	char *filename;
	
};