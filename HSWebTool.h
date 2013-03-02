#pragma once
#define HAVE_REMOTE
#include "pcap.h"								// ������ ��������
#include "winsock2.h"							// ����� ��� ������ � ��������
#include "HSTcpPacket.h"						// ����� ��� ������ � TCP-��������
#include "HSSavedSessionClass.h"				// ����� ��� ������ � ������������ ��������
#include <boost/property_tree/ini_parser.hpp>	// ����� ��� ��������
#include <IPHlpApi.h>							// ����� ��� ������ � �������� ������������

typedef void (*ParserType)(const std::string&, boost::property_tree::ptree&);

class HSWebTool{
public:
	HSWebTool(void);							// ������������� ����������
	BOOL start(int isService);					// ������ ������

	BOOL getDeviceList(void);					// �������� ������ ���������
	int printDeviceList(PIP_ADAPTER_INFO ptr_adapter_info);	// ������ ������ ���������
	BOOL setCurrentDevice(int deviceCnt);		// ����� �������� ����������
	
	BOOL initDevice(void);						// ������������� �������� ����������
	BOOL setFilter(void);						// ��������� �������
	BOOL setOutput(void);						// ��������� ��������� �����
	void setOutputName(void);					// ��������� ����� ������

	void ParseConfig (const boost::property_tree::ptree& config);	// ������� �������
	int ParseFile(const std::string& name, ParserType parser);		// ������� ������-�����
	BOOL initLogEvent(void);										// ������ � LogEvent
	void writeError(LPCTSTR text);


	BOOL runSniffing(void);						// ������ ���������
	BOOL workWithPacket(void);					// ��������� �������
	BOOL getTcpPacket(int onlyPrintPacket);		// ��������� ����������� TCP-������

	void stop(void);							// ��������� ������
	virtual ~HSWebTool(void);					// ������������ ��������

private:
	char *_dev;									// ���������� ��� ��������
	std::string _filter_exp;					// ��������� �������
	std::string _outFilename;					// ��� ��������� �����
	std::string _outPathForSession;				// ��� ��������� ��������
	char _errbuf[PCAP_ERRBUF_SIZE];				// Error string
	const u_char *_packet;						// ������� �����
	int _maxSizePacket;							// ������������ ������ ������
	int _numPackets;							// ���-�� ����������� �������
	int _timeout;								// ������� �������� ������
	int _findDataIn;							// ������ � ������ ��� ������
	int _defualtDevice;							// ���������� �� ���������
	int _isExit;								// ���� ��������� ���������
	int _isService;								// ���� ������ ��� �������
	int _isSaveSession;							// �������� ������ ��� ������
	int tcp,others,good,total;					// ���������� ������
	struct bpf_program _fp;						// ���������������� ������
	struct pcap_pkthdr *_header;				// ����� ������	
	HANDLE _hLog;
	
	FILE *_fstream;								// �������� ����
	bpf_u_int32 _mask;							// ������� ����� ����������
	bpf_u_int32 _net;							// IP-����� ����������
	pcap_if_t *_alldevs;						// ������ ���������						
	pcap_t *_handle;							// Handle ������
	IPV4_HDR *_iphdr;							// IP-���������
	HSSavedSessionClass *_sessionList;			// ������ ����������� ������
	HSStrList *_strList;						// ������ ����
	std::string _inFilename;					// ��� �������� �����
};