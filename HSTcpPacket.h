#pragma once
#include "HSstructs.h"
#include "HSStrList.h"	


class HSTcpPacket{
public:
	HSTcpPacket(const u_char *packet_, int packet_size_, HSStrList *strList_);
	void initPacketData(int packet_size);		// ��������� ������ 

	BOOL findInHTTPheader(void);				// ����� ������ � HTTP-header
	BOOL findInHTTPdata(void);					// ����� ������ � HTTP-data
	BOOL findInHTTP(void);						// ����� �� ���� HTTP

	void printTcpPacket(FILE *_fstream);		// ����� TCP-������
	void printEthernetHeader(FILE *_fstream);	// ����� Enternet-���������	
	void printTcpHeader(FILE *_fstream);		// ����� TCP-���������
	void printIpHeader (FILE *_fstream);		// ����� IP-���������

	virtual ~HSTcpPacket(void);

private:
	TCP_HDR *_tcpheader;						// TCP-���������
	IPV4_HDR *_iphdr;							// IP-���������
	
	FILE *_fstream;								// �������� ����
	const u_char *_packet;						// ������� �����
												// �������� ����� ��� ������ ������������
	WCHAR *_data;								// ������ ������
	HSStrList _listStr;							// ������ ���� ��� ������ 

};

