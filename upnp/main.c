
#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "miniupnpc.h"

void redirect(uint16_t privateport, uint16_t publicport)
{
  int r;
  natpmp_t natpmp;
  natpmpresp_t response;
  initnatpmp(&natpmp);
  sendnewportmappingrequest(&natpmp, NATPMP_PROTOCOL_TCP, privateport, publicport, 3600);
  do {
    fd_set fds;
    struct timeval timeout;
    FD_ZERO(&fds);
    FD_SET(natpmp.s, &fds);
    getnatpmprequesttimeout(&natpmp, &timeout);
    select(FD_SETSIZE, &fds, NULL, NULL, &timeout);
    r = readnatpmpresponseorretry(&natpmp, &response);
  } while(r==NATPMP_TRYAGAIN);
  printf("mapped public port %hu to localport %hu liftime %u\n",
         response.newportmapping.mappedpublicport,
         response.newportmapping.privateport,
         response.newportmapping.lifetime);
  closenatpmp(&natpmp);
}

int main(){
	
	/*
	const char* multicastif = 0;
	const char* minissdpdpath = 0;
	int error; // gets the error value.
	upnpDiscover(2500, multicastif, minissdpdpath, 0, 0, &error);
	*/
	
	
	return 0;
}
