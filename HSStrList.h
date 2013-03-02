#pragma once
#include <Windows.h>
#include <list>


class HSStrList{
public:
	HSStrList(void);
	HSStrList(const HSStrList& ts);
	HSStrList(std::string str, HANDLE hLog);			// �������� ������
	
	void addStr(std::wstring str);						// ���������� ������ 
	BOOL  getByFile(void);								// �������� �� �����
	WCHAR* getStr(void);
	BOOL regComp(std::wstring regExp, WCHAR* data);
	void parse(WCHAR *buf);

	void writeError(LPCTSTR text);
	virtual ~HSStrList(void);
private:
	std::list<std::wstring> _slist;						
	int _countElem;
	int _curStr;
	HANDLE _hLog;
	std::string _filename;
};