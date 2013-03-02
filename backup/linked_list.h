#pragma once
#include "saved_session_class.h"

class linked_list: public saved_session_class{
public:
	linked_list();			// �������� ������
	
	virtual void add(unsigned int _ip_srcaddr, unsigned int _ip_destaddr, char *_session_filename); // ���������� ������ � ������
	virtual char* findSaved(unsigned int _ip_srcaddr, unsigned int _ip_destaddr);	// ����� ������������ ������
	void deleteRecord(SAVED_SESSION *pDelete);			// �������� ������
	virtual void deleteByIp(unsigned int ip_srcaddr, unsigned int ip_destaddr); // �������� ������ �� �������
	virtual void deleteByFilename(char *filename);		// �������� ������ �� ����� �����
    virtual void delAllList(void);						// �������� ���� �������

	virtual ~linked_list();

private:
	SAVED_SESSION *pHead;						// ��������� �� ������ ������� ������
    SAVED_SESSION *pPrev;						// ��������� �� ��������� ������� ������
};

