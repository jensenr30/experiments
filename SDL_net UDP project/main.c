#include <stdio.h>
#include "SDL.h"
#include "SDL_net.h"





int main(int argc, char *argv[]){
	
	
	
	
	if(SDL_Init(0)==-1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	freopen( "CON", "w", stdout );
	freopen( "CON", "w", stderr );
	
	
	if(SDLNet_Init()==-1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
	
	
	SDL_version compile_version;
	const SDL_version *link_version=SDLNet_Linked_Version();
	SDL_NET_VERSION(&compile_version);
	printf("compiled with SDL_net version: %d.%d.%d\n", 
			compile_version.major,
			compile_version.minor,
			compile_version.patch);
	printf("running with SDL_net version: %d.%d.%d\n", 
			link_version->major,
			link_version->minor,
			link_version->patch);
	
	
	
	
	
	
	// create a UDPsocket on any available port (client)
	UDPsocket udpsock;
	
	udpsock=SDLNet_UDP_Open(0);
	if(!udpsock) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	
	// send a packet using a UDPsocket, using the packet's channel as the channel
	//UDPsocket udpsock;
	UDPpacket *packet;
	packet=SDLNet_AllocPacket(1024);
	if(!packet){
		printf("packet making failed\n");
	}
	else {
		packet->
	}
	int numsent;

	numsent=SDLNet_UDP_Send(udpsock, packet->channel, packet);
	if(!numsent) {
		printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
		// do something because we failed to send
		// this may just be because no addresses are bound to the channel...
	}
	
	
	
	
	
	SDLNet_Quit();
	return 0;
}
