#pragma once
#include "HSSavedSessionClass.h"

class HSLinkedList: public HSSavedSessionClass{
public:
	HSLinkedList(void);			// �������� ������
	
	virtual void add(unsigned int _ip_srcaddr, unsigned int _ip_destaddr, char *_session_filename); // ���������� ������ � ������
	virtual char* findSaved(unsigned int _ip_srcaddr, unsigned int _ip_destaddr);	// ����� ������������ ������
	void deleteRecord(SAVED_SESSION *pDelete);			// �������� ������
	virtual void deleteByIp(unsigned int ip_srcaddr, unsigned int ip_destaddr); // �������� ������ �� �������
	virtual void deleteByFilename(char *filename);		// �������� ������ �� ����� �����
    virtual void delAllList(void);						// �������� ���� �������

	virtual ~HSLinkedList();

private:
	SAVED_SESSION *_pHead;						// ��������� �� ������ ������� ������
    SAVED_SESSION *_pPrev;						// ��������� �� ��������� ������� ������
};

