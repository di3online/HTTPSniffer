#include "StdAfx.h"
#include "HSLinkedList.h"

// �������� ������
HSLinkedList::HSLinkedList(void) : HSSavedSessionClass(){
	_pHead = NULL;
	_pPrev = NULL;
    _countElem = 0;
}



// ���������� ������ � ������
void HSLinkedList::add(unsigned int _ip_srcaddr, unsigned int _ip_destaddr, char *_session_filename){
	SAVED_SESSION *temp = NULL;
	
	temp = new SAVED_SESSION;
	temp->ip_destaddr = _ip_destaddr;
	temp->ip_srcaddr = _ip_srcaddr;   
	temp->session_filename = _session_filename;	
	temp->next = NULL;
	
	if (_pHead == NULL){
        _pHead = temp;
		_pPrev = _pHead;
		_pHead->next = NULL;
	}
    else
        _pPrev->next = temp;

   // _pPrev = temp;
    _countElem++;
	if (temp != NULL){ delete temp; }
}



// ����� ����������� ������
char* HSLinkedList::findSaved(unsigned int _ip_srcaddr, unsigned int _ip_destaddr){
	SAVED_SESSION *pTemp = _pHead;
 //   while(pTemp){
	for (int i = 0; i < _countElem; i++){
		if (    
				(pTemp->ip_destaddr == _ip_destaddr) 
					&& (pTemp->ip_srcaddr == _ip_srcaddr) ||
				(pTemp->ip_destaddr == _ip_srcaddr) 
					&& (pTemp->ip_srcaddr == _ip_destaddr)
			)
			return pTemp->session_filename;
		pTemp = pTemp->next;
	}
	return NULL;
}
 


// �������� ������
void HSLinkedList::deleteRecord(SAVED_SESSION *pDelete){
	SAVED_SESSION *pTemp = NULL;
	pTemp = _pHead;
	SAVED_SESSION *_pPrev = NULL;
	_pPrev = _pHead;
	while(_pPrev != NULL){
		// ���� ��������� ������� ������
		if (_pPrev == pDelete){
			_pHead = _pPrev->next;
			if (_pPrev != NULL) delete _pPrev;
			return;
		}

		// ���� ��������� ������� �� ������
		if (_pPrev->next == pDelete){
			pTemp = _pPrev->next;
			_pPrev->next = _pPrev->next->next;
		
			if (pTemp != NULL) delete pTemp;
			return;
		}
		_pPrev = _pPrev->next;
	}
}



// �������� ������ �� ����� �����
void HSLinkedList::deleteByFilename(char *filename){
	SAVED_SESSION *pTemp = NULL;
	pTemp = _pHead;
	while(pTemp != NULL){
		if (pTemp->session_filename == filename){	
					deleteRecord(pTemp);
					--_countElem;
					if (pTemp != NULL) delete pTemp;
					return;
		}
		pTemp = pTemp->next;
    } 
}



// �������� ������ �� IP
void HSLinkedList::deleteByIp(unsigned int ip_srcaddr, unsigned int ip_destaddr){
	SAVED_SESSION *pTemp = NULL;
	pTemp = _pHead;
	while(pTemp != NULL){
		if (    (pTemp->ip_destaddr == ip_destaddr) && (pTemp->ip_srcaddr == ip_srcaddr) ||
				(pTemp->ip_destaddr == ip_srcaddr) && (pTemp->ip_srcaddr == ip_destaddr)
				){	
					deleteRecord(pTemp);
					--_countElem;
					if (pTemp != NULL) delete pTemp;
					return;
		}
		pTemp = pTemp->next;
    }
}



// �������� ���� �������
void HSLinkedList::delAllList(void){
    while(_pHead != NULL){
        SAVED_SESSION *pTemp = NULL;
		pTemp = _pHead;
        _pHead = _pHead->next;
        if (pTemp != NULL) delete pTemp;
    }
	_countElem = 0;
}



HSLinkedList::~HSLinkedList(void){
	delAllList();
}
