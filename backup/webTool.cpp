#include "StdAfx.h"
#include "webTool.h"
#include <sys\timeb.h>
#include <sys\types.h>
#include <sys\timeb.h>
#include <time.h>
#include "linked_list.h"
#include "linked_list_cont.h"


using namespace std;


// ������������� ����������
webTool::webTool(void){
	char input[] = "C:\\input1.txt";
	strList = new str_list(input);
	strList->getByFile();

	numPackets = 0;							// ���-�� ����������� �������, 0 - �� ������������
	maxSizePacket = 1048576;				// ������������ ������ ������������ ������
	inOneFile = 0;							// �������� ������ � ���� ���� ��� � ���������
	
	if (inOneFile){
		// ��� ��������� �����
		outFilename = "C:/output.txt";
	}
	else{
		// ��� ��������� ��������
		outPath = "C:/output/";
	}

	findStringIn = 1;						// 0 - ������ ������ � HTTP-���������
											// 1 - ������ ������ � HTTP-data
											// 2 - ������ �� ���� HTTP-������
	str = L"";					
	tcp = 0, others = 0, good = 0, total = 0;
	timeout = 1000;
	filter_exp ="port 80 or port 8080";
	
	dev = pcap_lookupdev(errbuf);
	if (!dev){
		fprintf(stderr, "%s", errbuf);
		exit(1);
	}
}



// ������ ������
void webTool::start(void){
	isExit = 0;								// ��������� ����� ������
	setCurrentDevice();						// ��������� �������� ����������
	setFilter();							// ��������� �������
	runSniffing();							// ������ ���������
	int s = 4;
}



// ����� �������� ����������
void webTool::setCurrentDevice(void){
	// ��������� ������ ���������
    if (pcap_findalldevs(&alldevs, errbuf) == -1){
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        exit (1);
    }
   
    // ������ ������
    int deviceCnt=0;		
	pcap_if_t *d;
	fprintf(stdout,"LIST OF DEVICE\n");
	fprintf(stdout,"****************************************\n\n");
	for(d = alldevs; d; d=d->next){
        fprintf(stdout,"%d. %s", ++deviceCnt, d->name);
        if (d->description)
			fprintf(stdout," (%s)\n", d->description);
		else printf(" (No description available)\n");
	}
	fprintf(stdout,"\n****************************************\n\n");
	
	// ����� ����������
	int devId = 1;
	do{
		fprintf(stdout, "Choice device (0<x<%d): ", deviceCnt+1);
		fscanf(stdin, "%d", &devId);
	}while ((devId>deviceCnt) || (devId<=0));
	
	d = alldevs;
	for (int i=1; d && i!=devId; ++i){
		d = d->next;
	}

	dev = d->name;
	fprintf(stdout, "\nCurrent device: %s\n\n", dev);
	initDevice();
}



// ������������� ���������� ����������
void webTool::initDevice(void){
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1){
		fprintf(stderr, "Can't get netmask for device %s\n", dev);
		net = 0;
		mask = 0;
	}

	handle = pcap_open_live(dev, maxSizePacket, 1, timeout, errbuf);
	if (!handle){
		fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		exit (1);
	}
}



// ��������� �������
void webTool::setFilter(void){
	if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1){
		fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		exit (2);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		exit (2);
	}
}



// ������������� ��������� �����
void webTool::setOutput(void){ 
	fstream = fopen(outFilename, "a, ccs=UNICODE");
	if(!fstream){
		fprintf(stdout, "\nUnable to create file.");
		exit (3);
	} 
} 



// ��������� ����������� TCP-������
int webTool::getTcpPacket(int onlyPrintPacket){
	int size = header->caplen;
	TCP_packet tcp_curr(packet,fstream,str,size,strList);

	if (onlyPrintPacket){
		setOutput();
		if (fstream != NULL) {
			tcp_curr.printTcpPacket(fstream);
			fclose(fstream);
		}
		return 0;	
	}

	if ((findStringIn == 0) && (tcp_curr.findInHTTPheader())){			// ����� ������ � HTTP-Header
		setOutput();
		if (fstream != NULL) {
			tcp_curr.printTcpPacket(fstream);
			fclose(fstream);
		}
		return 1;
	};

	if ((findStringIn == 1) && (tcp_curr.findInHTTPdata())){			// ����� ������ � HTTP-data
		setOutput();
		if (fstream != NULL) {
			tcp_curr.printTcpPacket(fstream);
			fclose(fstream);
		}
		return 1;
	};
	
	if ((findStringIn == 2) && (tcp_curr.findInHTTP())){				// ����� �� ���� HTTP
		setOutput();
		if (fstream != NULL) {
			tcp_curr.printTcpPacket(fstream);
			fclose(fstream);
		}
		return 1;
	}
	
	return 0;
}



// ��������� �������
int webTool::workWithPacket(){
	ETHER_HDR *ethhdr;
	int size = header->caplen;
	ethhdr = (ETHER_HDR *)packet; 
	++total; 
	

	//Ip packets
	if(ntohs(ethhdr->type) == 0x0800){
		iphdr = (IPV4_HDR *)(packet + sizeof(ETHER_HDR));
		// ����������� ���������
		switch (iphdr->ip_protocol){						
		case IPPROTO_TCP:												
			tcp++;	
			
			// ��������� ������ ������ (� ������ �������) � ��������� ����
			if (!inOneFile){
				// ������� ��������� �� ������ ���������/���������, ���� ��, �� ��������� ����� � ������ ����
				if (sessionList->findSaved(iphdr->ip_srcaddr,iphdr->ip_destaddr)){	
					outFilename = sessionList->findSaved(iphdr->ip_srcaddr,iphdr->ip_destaddr);
					getTcpPacket(1);
					break;
				}
							
				// ������ ���������/��������� �� ���� �������, ������� ���� ���������, 
				// ���� ����, �� ��������� ���� � ���������/���������
				if (getTcpPacket(0)){
					good++;
					sessionList->add(iphdr->ip_srcaddr,iphdr->ip_destaddr,outFilename);
					break;
				}
				break;
			}
			// ��� ������ � ���� ����
			if (getTcpPacket(0))
				good++;
			break;

		default:							// ������ ���������
			others++; 
			break; 
		} 
	}
	fprintf(stdout,"Statistics package: TCP:%d  Others:%d  Good:%d  Total:%d\r" , tcp , others , good , total);
	return 0;
}



// ��������� ������� ����� �����
void webTool::setOutputName(void){
	char date[100];
	char filename[100];
	char fullName[100];
	struct tm tbreak;

	time_t timer;
    struct tm *tblock;
    struct _timeb timebuffer;
    _ftime( &timebuffer );
    tblock = localtime(&timebuffer.time);
    strftime (date, 80, "%Y-%m-%d_%H-%M-%S.", tblock);
    _itoa(timebuffer.millitm, filename, 10);	
	strcat(date,filename);
	strcat(date,".txt");

	fullName[0]='\0';
	strcat(fullName,outPath);
	strcat(fullName,date);
	outFilename = new char[strlen(fullName)];
	outFilename[0] = '\0';
	strcpy(outFilename,fullName);
}



// ������ ���������
int webTool::runSniffing(){
	u_int res;	
	fprintf(stdout,"Sniffing is runnig...\n(For stop sniffing press ctrl+c)\n\n");
	
	sessionList = new linked_list();

	while((!isExit) && ((res = pcap_next_ex(handle, &header, &packet)) >= 0)){        
		if(res == 0){											// ��������� ��������
			continue;								
		} 
		if (!inOneFile){ 
			setOutputName();
		} 
		workWithPacket(); 
	}   
	if(res == -1){
		return -1; 
	}
	return 0;
}



// ��������� ������
void webTool::stop(void){
	isExit = 1;
}



// ������������ ��������
webTool::~webTool(void){
	if (alldevs != NULL){
		pcap_freealldevs(alldevs);
	}
	if (strList != NULL){
		delete strList;
	}
	if (sessionList){
		delete(sessionList);
	}
	if (handle != NULL){
		pcap_close(handle);
	}
	if (fstream != NULL){
		fclose(fstream);
	}
}
