#pragma once
#include "HSSavedSessionClass.h"
#include <iterator>
#include <list>


class HSLinkedListCont : public HSSavedSessionClass{
public:
	HSLinkedListCont();	// �������� ������
	
	virtual void add(unsigned int _ip_srcaddr, unsigned int _ip_destaddr, char *_session_filename); // ���������� ������
	virtual char* findSaved(unsigned int _ip_srcaddr, unsigned int _ip_destaddr); // ����� ������ �� IP
	
	virtual void deleteByIp(unsigned int ip_srcaddr, unsigned int ip_destaddr); // �������� ������ �� IP
	virtual void deleteByFilename(char *filename);	// �������� ������ �� ����� �����
    virtual void delAllList(void); // �������� ���� �������
	
	virtual ~HSLinkedListCont();
private:
	 std::list<SAVED_SESSION> plist;
}; 

