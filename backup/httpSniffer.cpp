/************************************************
TO-DO:
	1) �������� ������
************************************************/


#include "stdafx.h" 
#include "webTool.h"

webTool one;

// ��������� ���������
BOOL WINAPI HandlerRoutine(DWORD dwCtrlType){
	switch(dwCtrlType){ 
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
		one.stop();		
		break;
	} 

	return TRUE;
} 


int _tmain(int argc, _TCHAR* argv[]){
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
	one.start();
	return(0); 
}

