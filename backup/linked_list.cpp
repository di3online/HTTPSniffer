#include "StdAfx.h"
#include "linked_list.h"

// �������� ������
linked_list::linked_list(void) : saved_session_class(){
	pHead = NULL;
    countElem = 0;
}



// ���������� ������ � ������
void linked_list::add(unsigned int _ip_srcaddr, unsigned int _ip_destaddr, char *_session_filename){
	SAVED_SESSION *temp = new SAVED_SESSION;
    if (pHead == NULL)
        pHead = temp;
    else
        pPrev->next = temp;
	temp->ip_destaddr = _ip_destaddr;
	temp->ip_srcaddr = _ip_srcaddr;   
	temp->session_filename = _session_filename;
	
	temp->next = NULL;
    pPrev = temp;
    countElem++;
}



// ����� ����������� ������
char* linked_list::findSaved(unsigned int _ip_srcaddr, unsigned int _ip_destaddr){
	SAVED_SESSION *pTemp = pHead;
    while(pTemp != NULL){
		if (    (pTemp->ip_destaddr == _ip_destaddr) && (pTemp->ip_srcaddr == _ip_srcaddr) ||
				(pTemp->ip_destaddr == _ip_srcaddr) && (pTemp->ip_srcaddr == _ip_destaddr)
			)
			return pTemp->session_filename;
        pTemp = pTemp->next;
    }
	return NULL;
}
 


// �������� ������
void linked_list::deleteRecord(SAVED_SESSION *pDelete){
	SAVED_SESSION *pTemp = pHead;
	SAVED_SESSION *pPrev = pHead;
	while(pPrev != NULL){
		// ���� ��������� ������� ������
		if (pPrev == pDelete){
			pHead = pPrev->next;
			delete pPrev;
			return;
		}

		// ���� ��������� ������� �� ������
		if (pPrev->next == pDelete){
			pTemp = pPrev->next;
			pPrev->next = pPrev->next->next;
		
			delete pTemp;
			return;
		}
		pPrev = pPrev->next;
	}
}



// �������� ������ �� ����� �����
void linked_list::deleteByFilename(char *filename){
	SAVED_SESSION *pTemp = pHead;
	while(pTemp != NULL){
		if (pTemp->session_filename == filename){	
					deleteRecord(pTemp);
					--countElem;
					return;
		}
		pTemp = pTemp->next;
    } 
}



// �������� ������ �� IP
void linked_list::deleteByIp(unsigned int ip_srcaddr, unsigned int ip_destaddr){
	SAVED_SESSION *pTemp = pHead;
	while(pTemp != NULL){
		if (    (pTemp->ip_destaddr == ip_destaddr) && (pTemp->ip_srcaddr == ip_srcaddr) ||
				(pTemp->ip_destaddr == ip_srcaddr) && (pTemp->ip_srcaddr == ip_destaddr)
				){	
					deleteRecord(pTemp);
					--countElem;
					return;
		}
		pTemp = pTemp->next;
    }
}



// �������� ���� �������
void linked_list::delAllList(void){
    while(pHead != NULL){
        SAVED_SESSION *pTemp = pHead;
        pHead = pHead->next;
        if (pTemp) delete pTemp;
    }
	countElem = 0;
}



linked_list::~linked_list(void){
	delAllList();
}
